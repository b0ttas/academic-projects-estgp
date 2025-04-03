import os
from datetime import timedelta

from django.contrib import messages
from django.core.mail import send_mail
from django.http import HttpResponse, Http404, FileResponse
from django.http import JsonResponse
from django.shortcuts import get_object_or_404, redirect
from django.shortcuts import render
from django.urls import reverse
from rest_framework import generics, permissions, status
from rest_framework import viewsets, serializers
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.views import APIView

from pae.models import PAEToken
from .forms import SubscriptionForm
from .handle_pae_response import generate_urls, send_pae_email
from .models import PAEDestination  # Import the Destination model
from .models import PAEEmail, PAEAttachment, PAEUserAccessToken
from .serializers import EmailSerializer  # Assume you have an EmailSerializer

from rest_framework.decorators import api_view
from django.utils import timezone

class SubscriptionListView(generics.ListAPIView):
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request, **kwargs):
        destination = request.user  # The authenticated user is the Destination object
        services = destination.service_set.all()

        response_data = []
        for service in services:
            emails = destination.emails.filter(destination__service=service).values('id', 'subject', 'date_sent')
            response_data.append(
                {'service_name': service.name, 'is_active': destination.is_active, 'emails': list(emails)})

        return Response(response_data)


class UnsubscribeAllView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    @staticmethod
    def post(request):
        destination = request.user
        is_active = request.data.get('is_active', True)
        destination.is_active = is_active
        destination.save()

        return Response({"status": "Subscription updated successfully."})


class DownloadEmailView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    @staticmethod
    def get(request, email_id):
        email = get_object_or_404(PAEEmail, id=email_id, subscription__destination=request.user)
        response = HttpResponse(email.body, content_type='text/plain')
        response['Content-Disposition'] = f'attachment; filename="{email.subject}.txt"'
        return response


class DownloadAttachmentView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    @staticmethod
    def get(request, attachment_id):
        attachment = get_object_or_404(PAEAttachment, id=attachment_id, email__subscription__destination=request.user)
        file_path = attachment.file.path
        with open(file_path, 'rb') as f:
            response = HttpResponse(f.read(), content_type='application/octet-stream')
            response['Content-Disposition'] = f'attachment; filename="{attachment.filename}"'
            return response


class DownloadMultipleEmailsView(APIView):
    @staticmethod
    def get(request, *args, **kwargs):
        # Extract the UUID token from the request (assumed passed as a query parameter)
        token = request.GET.get('token')

        # Validate the token and retrieve the destination
        try:
            destination = PAEDestination.objects.get(token=token)
        except PAEDestination.DoesNotExist:
            return JsonResponse({"error": "Destination not found."}, status=404)

        # Assuming emails are related to the Destination in some way
        emails = destination.get_emails()  # Implement this method based on your logic

        if not emails:
            return JsonResponse({"message": "No emails found for this destination."}, status=204)

        # Serialize the emails
        serialized_emails = EmailSerializer(emails, many=True).data

        # Here, you might want to handle downloading as a file or returning a response
        return JsonResponse(serialized_emails, safe=False)



@api_view(['POST'])
def generate_access_token(request):
    """
    Endpoint to generate a new access token for a given destination email.
    Expects 'email' in the POST data.
    """
    email = request.data.get('email')
    if not email:
        return Response({"error": "Email is required."}, status=status.HTTP_400_BAD_REQUEST)

    try:
        destination = PAEDestination.objects.get(email=email)
    except PAEDestination.DoesNotExist:
        return Response({"error": "Destination not found."}, status=status.HTTP_404_NOT_FOUND)

    # Create a new access token valid for 7 days
    token = PAEUserAccessToken.objects.create(destination=destination, expires_at=timezone.now() + timedelta(days=7))

    return Response({"token": str(token.token)}, status=status.HTTP_201_CREATED)


@api_view(['GET', 'POST'])
def test_endpoints(request, token):  # TODO, token usage
    try:
        if not token: token = {}  # TODO, testing, remove
        unsubscribe_token = get_object_or_404(PAEToken, token=token)
        if request.method == 'POST':
            pass
            unsubscribe_token.delete()
    except ValueError:
        return HttpResponse(status=500)


@api_view(['GET', 'POST'])
def unsubscribe(request, token):
    unsubscribe_token = get_object_or_404(PAEUserAccessToken, token=token)
    if request.method == 'POST':
        unsubscribe_token.destination.is_active = False
        unsubscribe_token.destination.save()
        return render(request, 'pae/unsubscribe_success.html')
    return render(request, 'pae/unsubscribe_confirm.html', {'token': token})


@api_view(['GET'])
def email_history(request, token):
    """
    Display email history for a user with a given access token.
    Allow downloading of email attachments if a valid token is provided.
    """
    # Verify the token
    access_token = get_object_or_404(PAEUserAccessToken, token=token)

    # Filter destinations by the email address associated with the current destination
    email_address = access_token.destination.email
    destinations_with_same_email = PAEDestination.objects.filter(email=email_address)

    # Retrieve emails associated with these destinations
    emails = PAEEmail.objects.filter(destination__in=destinations_with_same_email).order_by('-date_sent')

    # Check if a file download is requested using the file ID
    file_id = request.GET.get('file_id')
    if file_id:
        # Retrieve the requested attachment securely
        attachment = get_object_or_404(PAEAttachment, id=file_id, email__in=emails)

        # Serve the file if found
        try:
            return FileResponse(attachment.file.open('rb'), as_attachment=True, filename=attachment.filename)
        except FileNotFoundError:
            raise Http404("File does not exist.")

    return render(request, 'pae/email_history.html', {
        'user_email': access_token.destination.email,
        'emails': emails,
    })

"""    user_token = get_object_or_404(PAEUserAccessToken, token=token)
    user_email = user_token.destination.email

    # Get all emails sent to the user, ordered by date
    emails = PAEEmail.objects.filter(destination__email=user_email).order_by('-date_sent')

    return render(request, 'pae/email_history.html', {'user_email': user_email, 'emails': emails})
"""

@api_view(['GET', 'POST'])
def manage_subscriptions(request, token):
    user_token = get_object_or_404(PAEUserAccessToken, token=token)
    user_email = user_token.destination.email

    # Get all subscriptions, both active and inactive
    subscriptions = PAEDestination.objects.filter(email=user_email)

    if request.method == 'POST':
        form = SubscriptionForm(request.POST)
        action = request.POST.get('action')

        if form.is_valid():
            subscription_id = form.cleaned_data['subscription_id']
            cron_update_interval = form.cleaned_data['cron_update_interval']

            subscription = get_object_or_404(PAEDestination, id=subscription_id, email=user_email)

            if action == 'update':
                # Update the interval
                subscription.cron_update_interval = cron_update_interval
                subscription.last_updated = timezone.now()
                subscription.save()
                messages.success(request, "Subscription updated successfully.")
            elif action == 'reactivate':
                # Reactivate the subscription
                subscription.is_active = True
                subscription.last_updated = timezone.now()
                subscription.save()
                messages.success(request, "Subscription reactivated successfully.")

            return redirect('manage_subscriptions', token=token)

    else:
        form = SubscriptionForm()

    return render(request, 'pae/manage_subscriptions.html',
                  {'user_email': user_email, 'subscriptions': subscriptions, 'form': form})


@api_view(['GET'])
def refresh_token(request, token):
    """
    Refresh the token and send a new email with updated links.
    This view accepts expired tokens.
    """
    # Retrieve the token object, even if expired
    token_obj = get_object_or_404(PAEUserAccessToken, token=token)

    # Invalidate the old token
    token_obj.expires_at = timezone.now()  # Mark it as expired
    token_obj.save()

    # Generate new URLs for the user
    unsubscribe_url, email_history_url, manage_subscriptions_url, refresh_token_url = generate_urls(token_obj.destination)

    email_content=(
        f"Here are your refreshed links:\n\n"
        f"Unsubscribe: {unsubscribe_url}\n"
        f"Email History: {email_history_url}\n"
        f"Manage Subscriptions: {manage_subscriptions_url}\n"
        f"Refresh Tokens: {refresh_token_url}"
    )

    success = send_pae_email(
        service=token_obj.destination.service,
        recipients=[token_obj.destination.email],
        attachment_paths=[],  # No attachments in this case
        content=email_content
    )

    if not success:
        print("Failed to send refreshed token email.")

    return render(request, 'pae/token_refresh_success.html')

class TokenSerializer(serializers.HyperlinkedModelSerializer):
    # specify model and fields
    class Meta:
        model = PAEToken
        fields = ('token', 'expiration_time')


class PaeViewSet(viewsets.ModelViewSet):
    authentication_classes = [SessionAuthentication, BasicAuthentication]
    permission_classes = [IsAuthenticated]
    http_method_names = ['get', 'post']
    queryset = PAEToken.objects.none()
    serializer_class = TokenSerializer

    # Your existing methods (list, retrieve, etc.) go here
    def list(self, request, **kwargs):
        test_cases = {"test": f"{os.getenv('DOMAIN')}api/pae/test/",
                      "unsubscribe": f"{os.getenv('DOMAIN')}api/pae/test-unsubscribe/",
                      "manage_subscriptions": f"{os.getenv('DOMAIN')}api/pae/test-unsubscribe/",
                      "email_history": f"{os.getenv('DOMAIN')}api/pae/test-unsubscribe/",
                      }
        return Response(test_cases)
