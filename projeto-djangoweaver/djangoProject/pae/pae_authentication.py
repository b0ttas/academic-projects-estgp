from datetime import datetime, timedelta

import requests

from scheduler.models import Authentication, ServiceAction
from .models import PAEToken
from .tokenManager import TokenManager

from rest_framework.authentication import BaseAuthentication
from rest_framework.exceptions import AuthenticationFailed
from .models import PAEUserAccessToken
from django.utils import timezone

class UUIDTokenAuthentication(BaseAuthentication):
    def authenticate(self, request):
        token = request.query_params.get('token') or request.headers.get('Authorization')
        if not token:
            raise AuthenticationFailed('No token provided.')

        # Handle 'Bearer <token>' format if using Authorization header
        if token.startswith('Bearer '):
            token = token.split(' ')[1]

        try:
            access_token = PAEUserAccessToken.objects.get(token=token, expires_at__gt=timezone.now())
            return access_token.destination, None  # Destination instance represents the user
        except PAEUserAccessToken.DoesNotExist:
            raise AuthenticationFailed('Invalid or expired token.')


class PAEAuthentication:
    def authenticate(self, authentication_instance):
        valid_token = PAEToken.objects.filter(expiration_time__gt=timezone.now()).order_by('-expiration_time').first()
        if valid_token:
            return valid_token
        else:
            auth_data = {"data": {"apikey": authentication_instance.auth_token}}
            auth_response = requests.post(authentication_instance.access_token_url, json=auth_data)

            if auth_response.status_code == 200:
                response_json = auth_response.json()
                pae_token = None
                if 'response' in response_json:
                    pae_token = response_json['response'].get('BACOSESS')
                    if pae_token:
                        # Extract expiration time from response (milliseconds)
                        expires_in = response_json['response'].get('certificateExpire')
                        if not expires_in:
                            raise Exception("Could not determine token expiration time")
                        expiration_time = self.calculate_expiration(expires_in)
                        # Save the token and expiration
                        PAEToken.objects.filter(expiration_time__lte=timezone.now()).delete()
                        PAEToken.objects.get_or_create(token=pae_token, expiration_time=expiration_time)
                return pae_token is not None  # Authentication successful only if pae_token is retrieved
            else:
                return False

    @staticmethod
    def calculate_expiration(expires_in):
        epoch = timezone.make_aware(datetime(1970, 1, 1))
        expiration_date = epoch + timedelta(milliseconds=expires_in)
        return expiration_date

    def get_data(self, authentication_instance:Authentication):
        active_token = (PAEToken.objects.filter(expiration_time__gt=timezone.now())
                        .order_by('-expiration_time').first())

        if not active_token and not self.authenticate(authentication_instance):
            # If no active token and authentication fails, return an empty dictionary
            return {}

        # If we had to authenticate, fetch the active token again
        if not active_token:
            active_token = PAEToken.objects.filter(expiration_time__gt=datetime.now()).first()

        # Get the ServiceAction instance
        try:
            service_action = ServiceAction.objects.get(service=authentication_instance.service)
        except ServiceAction.DoesNotExist:
            return {"error": f"ServiceAction with ID {authentication_instance.service} does not exist"}

        dynamic_data = {}
        # Add the BACOSESS token to the dynamic data
        dynamic_data["BACOSESS"] = active_token.token

        # Fill the request template with dynamic data
        try:
            request_body = service_action.get_filled_request_body(dynamic_data)
        except Exception as e:
            return {"error": f"Error filling request body: {str(e)}"}

        return request_body

class PAELogin:
    def __init__(self, access_token_url, auth_token):
        self.access_token_url = access_token_url
        self.auth_token = auth_token

    def login(self):
        # Check for existing valid token in database
        try:
            current_token = PAEToken.objects.get(expiration_time__gt=timezone.now())
            return current_token.token  # Return existing valid token
        except PAEToken.DoesNotExist:
            pass
            # TokenManager.delete_expired_tokens()
            # No valid token found, proceed with login

        auth_data = {"data": {"apikey": self.auth_token}}
        authenticate = requests.post(self.access_token_url, json=auth_data)

        if authenticate.status_code == 200:
            response_auth = authenticate.json()
            pae_token = None
            if 'response' in response_auth:
                pae_token = response_auth['response'].get('BACOSESS')
            if pae_token:
                # PAEToken retrieved, store it in database with expiration time
                TokenManager.store_token(token=pae_token, expiration_time=self.get_expiration_time(response_auth))
                return pae_token
            else:
                return False  # Login failed
        else:
            return False  # Login failed

    @staticmethod
    def get_expiration_time(response_auth):
        expires_in = response_auth["response"].get('certificateExpire')  # milliseconds
        if not expires_in:
            raise Exception("Could not determine token expiration time")
        return timezone.now() + timezone.timedelta(milliseconds=expires_in)
