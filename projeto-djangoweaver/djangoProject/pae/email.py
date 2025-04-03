from .models import PAEDestination, PAEUserAccessToken
from django.utils import timezone
from datetime import timedelta

def generate_token_for_email(email):
    '''Usage
    email = "user@example.com"
    token = generate_token_for_email(email)
    if token:
        print(f"Access token for {email}: {token}")
    else:
        print(f"Destination with email {email} does not exist.")'''
    try:
        destination = PAEDestination.objects.get(email=email)
        token = PAEUserAccessToken.objects.create(
            destination=destination,
            expires_at=timezone.now() + timedelta(days=7)  # Token valid for 7 days
        )
        return str(token.token)
    except PAEDestination.DoesNotExist:
        return None


