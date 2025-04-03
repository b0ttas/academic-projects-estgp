import json
import os
import smtplib
from email.message import EmailMessage
from typing import Iterable

from django.http import HttpResponse
from django.urls import reverse
from django.utils import timezone

from pae.models import PAEDestination, PAEAttachment, PAEEmail
from pae.pae_pdf_build import generate_pae_pdf
from scheduler.models import Service
from .models import PAEUserAccessToken

def handle_pae_response(response: HttpResponse, service: Service):
    """
    PAE-specific response handler for processing incoming data and sending notifications to the appropriate recipients.
    """
    output_type = service.output_type
    #recipients:list = []
    try:
        notifications = json.loads(response.content)['response']['result']['reportNotifications']
    except KeyError:
        return HttpResponse(f"Error processing incoming data", status=500)

    for notification in notifications:
        unique_identifier = notification['uniqueIdentifier']

        # Add recipients based on the notifications
        for person in notification['personstoNotify']:
            PAEDestination.objects.get_or_create(
                email=person['emailToNotify'],
                service=service,
                report_id=unique_identifier
            )

        recipients = list(PAEDestination.objects.filter(
            service=service,
            report_id=unique_identifier,
            is_active=True
        ))

        if not recipients:
            fallback = PAEDestination(email=os.getenv('FALLBACK_EMAIL'), service=service, report_id=unique_identifier, is_active=True)
            recipients.append(fallback)

        #TODO: remove after testing
        fallback, created = PAEDestination.objects.get_or_create(
            email=os.getenv('FALLBACK_EMAIL'),
            service=service,
            report_id=unique_identifier,
            #is_active=True
        )
        recipients = [fallback]

        if output_type == 'EMAIL':
            pass  #TODO: not supported yet

        elif output_type == 'EMAIL_ATTACHMENT':
            pdf_content = generate_pae_pdf(notification, service)
            return handle_email_response_pae(service, pdf_content, recipients)
    return HttpResponse("Unsupported output type", status=400)

def generate_urls(destination:PAEDestination):
    """
    Generate URLs for unsubscribe, email history, and manage subscriptions.
    """

    token_obj = PAEUserAccessToken.objects.create(destination=destination)
    token = token_obj.token
    domain = os.getenv('DOMAIN').rstrip('/')
    unsubscribe_url = f"{domain}{reverse('unsubscribe', args=[token])}"
    email_history_url = f"{domain}{reverse('email_history', args=[token])}"
    manage_subscriptions_url = f"{domain}{reverse('manage_subscriptions', args=[token])}"
    refresh_token_url = f"{domain}{reverse('refresh_token', args=[token])}"
    return unsubscribe_url, email_history_url, manage_subscriptions_url, refresh_token_url

def send_pae_email(service, recipients: Iterable, attachment_paths: Iterable, content: str) -> bool:
    """
    Sends an email with attachments and given content.
    """
    email = EmailMessage()
    email['From'] = os.getenv("SENDER_EMAIL")
    email['Bcc'] = recipients
    email['Subject'] = service.name
    email.set_content(content)

    # Attach files if provided
    for attachment_path in attachment_paths:
        filename = attachment_path.split("/")[-1]
        with open(attachment_path, "rb") as file:
                email.add_attachment(file.read(), maintype='application', subtype='pdf', filename=filename)

    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
            server.ehlo()
            server.login(os.getenv("SENDER_EMAIL"), os.getenv("EMAIL_PASSWORD"))
            server.send_message(email)
            server.close()
        return True
    except Exception as e:
        print(f"Error sending email: {str(e)}")
        return False

def handle_email_response_pae(service, pdf_content, recipients):
    """
    Handles email responses, generates user access tokens for recipients, and sends an email.
    """
    # Generate URLs and email content for each recipient
    email_sent_successfully = True
    for recipient in recipients:
        unsubscribe_url, email_history_url, manage_subscriptions_url, refresh_token_url = generate_urls(recipient)
        content = (
            f'Hello, \n\nPlease find your requested report attached.\n\n'
            f'Click here to unsubscribe: {unsubscribe_url}\n'
            f'View your email history: {email_history_url}\n'
            f'Manage your subscriptions: {manage_subscriptions_url}\n'
            f'If your links have expired, you can use the following link to refresh your tokens: {refresh_token_url}'
        )

        # Save the email entry in the database
        email_entry = PAEEmail.objects.create(
            destination=recipient,
            subject=f"{service.name} Report",
            body=content,
        )

        # Save the PDF content as an attachment
        attachment_filename = f"report_{service.name}_{timezone.now().strftime('%Y%m%d%H%M%S')}.pdf"
        attachment_path = f'data/attachments/{attachment_filename}'
        with open(attachment_path, 'wb') as pdf_file:
            pdf_file.write(pdf_content)

        # Create a PAEAttachment entry
        attachment_entry = PAEAttachment.objects.create(
            email=email_entry,
            file=attachment_path,
            filename=attachment_filename,
        )

        # Send the email with the attachment
        success = send_pae_email(
            service=service,
            recipients=[recipient.email],
            attachment_paths=[attachment_entry.file.path],
            content=email_entry.body
        )

        if not success:
            email_sent_successfully = False

    # Return an appropriate HTTP response based on whether emails were successfully sent
    return HttpResponse("OK", status=200) if email_sent_successfully \
        else HttpResponse("Failed to send some emails",status=500)