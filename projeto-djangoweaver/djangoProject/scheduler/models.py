import base64
import datetime
import json
import os
from abc import ABC, abstractmethod

import requests
from croniter import croniter
from django.contrib.auth.models import AbstractUser
from django.contrib.auth.models import AbstractUser
from django.contrib.auth.models import Group, User
from django.contrib.auth.models import Group, User
from django.core.files.storage import FileSystemStorage
from django.core.validators import FileExtensionValidator
from django.db import models
from django.http import HttpResponse, HttpRequest, HttpResponseBadRequest, JsonResponse
from django.template import Template, Context
from django.utils import timezone
from requests.auth import HTTPDigestAuth
from requests_oauthlib.oauth1_session import OAuth1Session
from requests_oauthlib.oauth2_session import OAuth2Session

from pae.models import PAEToken
from utils.validators import validate_crontab


class OverwriteStorage(FileSystemStorage):
    """ Overwrites user-uploaded files """

    def get_available_name(self, name, max_length=None):
        if self.exists(name):
            os.remove(os.path.join(self.location, name))
        return super(OverwriteStorage, self).get_available_name(name, max_length)


def upload_location(instance, filename):
    file, extension = filename.split('.')
    return './templates/pdf/%s.%s' % (instance.name, extension)


def validate_mapping(mapping):
    """
    Checks if changes to the mapping are valid.
    Reverts to the original mapping if the flag 'reset_mapping' is set to True.
    :param mapping:
    :return updated_mapping:
    """
    default_mapping = get_default_mapping()
    updated_mapping = {}

    # Reset to default mapping if 'reset_mapping' is set to True
    if mapping.get('reset_mapping'):
        return default_mapping

    # Retain only valid keys (those present in default_mapping)
    for key, value in mapping.items():
        if key in default_mapping:
            updated_mapping[key] = value

    return updated_mapping


def get_default_mapping():
    mapping = {"help": "You can replace every value with a matching key from the service using 'reply.'",
               "reset_mapping": False, "pdf_auto_mapping": True, "mail_subject": "reply.title",
               "mail_body": "This is an example", "pdf_title": "body", "pdf_text": "body"}

    return mapping


class Service(models.Model):
    DELIVERY_CHOICES = (('PERIODIC', 'Periodic'), ('REQUEST', 'On Request'),)
    PERIODIC = 'PERIODIC'

    MESSAGE_TYPE_CHOICES = (('JSON', 'JSON'), ('XML', 'XML'), ('CSV', 'CSV'), ('TEXT', 'Text'),)

    OUTPUT_CHOICES = (('JSON', 'JSON'), ('XML', 'XML'), ('HTML', 'HTML'), ('EMAIL', 'Email'), ('PDF', 'PDF'),
                      ('EMAIL_ATTACHMENT', 'Email w/ attachment'),)

    INTERVAL_UNITS = (('m', 'Minutes'), ('H', 'Hours'), ('D', 'Days'), ('W', 'Weeks'), ('M', 'Months'), ('Y', 'Years'),)

    AUTHENTICATIONS = (
        ('NONE', 'No Auth'), ('BASIC', 'Basic Auth'), ('TOKEN', 'Basic Token'), ('DIGEST', 'Digest Auth'),
        ('OAUTH1', 'OAuth 1.0'), ('OAUTH2', 'OAuth 2.0'),)

    name = models.CharField(max_length=200, default="", unique=True)
    date = models.DateField(default=timezone.now, blank=True, null=True, editable=False)
    delivery = models.CharField(max_length=200, choices=DELIVERY_CHOICES)
    email_text = models.CharField(max_length=2000, default="", blank=True, null=True)
    endpoint = models.URLField(max_length=200)
    delivery_endpoint = models.CharField(max_length=40, unique=True, blank=True, null=True,
                                         help_text="Optional: Should be set for 'On Request' delivery type. "
                                                   "Provides a callable internal endpoint. "
                                                   "Ex.: 'https://www.(domain).com/services/api/(delivery_endpoint)/")

    last_updated = models.DateTimeField(default=timezone.now, blank=True, null=True, editable=False)

    input_data_type = models.CharField(max_length=200, choices=MESSAGE_TYPE_CHOICES)
    output_type = models.CharField(max_length=200, choices=OUTPUT_CHOICES)
    pdf_transformer = models.CharField(max_length=10, choices=[('default', 'Default'), ('pae', 'PAE')],
                                       default='default')
    pdf_template = models.FileField(upload_to=upload_location, null=True, blank=True, storage=OverwriteStorage(),
                                    validators=[FileExtensionValidator(['pdf'])],
                                    help_text="Optional: PDF file to serve as template for the data output. "
                                              "'Output Type' must be PDF, should only contain 1 page.")

    ''' update_interval = models.DurationField(default=datetime.timedelta(minutes=20),
                                           help_text="This field specifies the minimum "
                                                     "update frequency. Ex.: '0 "
                                                     "01:30:00' corresponds to one "
                                                     "hour and 30 minutes, following the time "
                                                     "representation D HH:MM:SS.") '''

    cron_update_interval = models.CharField(max_length=100, blank=True, null=True, validators=[validate_crontab],
                                            default="* * * * *",
                                            help_text="Here you can specify an interval for updates, following the "
                                                      "use of Cron expressions, valid examples are '* 12 * * ?', "
                                                      "or '* * L * *'.")

    archive_time = models.DurationField(default=datetime.timedelta(days=30),
                                        help_text="This field specifies for how long data "
                                                  "should be kept. Ex.: "
                                                  "'30 00:00:00' corresponds to 30 "
                                                  "days, following the time "
                                                  "representation D HH:MM:SS.")
    mapping = models.JSONField(default=get_default_mapping, validators=[validate_mapping], blank=True, null=True,
                               help_text="This mapping relates the response from this "
                                         "Service the possible outputs, letting you "
                                         "customize the output.")
    response_mapping = models.TextField(blank=True, null=True, help_text="placeholder")

    def __str__(self):
        return self.name

    @classmethod
    def get_all_periodic(cls):
        return cls.objects.filter(delivery=cls.PERIODIC)

    def get_last_updated(self):
        return self.last_updated

    @classmethod
    def get_all_periodic_expired(cls):
        periodic_instances = cls.objects.filter(delivery=cls.PERIODIC)

        expired_instances = []
        for instance in periodic_instances:
            cron_iterable = croniter(instance.cron_update_interval, instance.get_last_updated())
            current_time = timezone.now()
            # update_deadline = service.get_last_updated() + service.update_interval
            next_update = cron_iterable.get_next(datetime.datetime)

            if current_time >= next_update:
                expired_instances.append(instance)

        return expired_instances

    def send_request(self):
        authentication = self.authentication
        if authentication.authenticate():
            if authentication.authentication_handler == 'DEFAULT':
                headers = authentication.get_headers()
                response = requests.get(self.endpoint, headers=headers)
            else:
                headers = authentication.get_headers()
                data = authentication.get_data()
                response = requests.get(self.endpoint, headers=headers, json=data)
        else:
            response = HttpResponse(status=503)  # Authentication failed

        return HttpResponse(content=response.content, status=response.status_code,
                            content_type=response.headers['Content-Type'])

    def get_request(self):
        authentication, created = Authentication.objects.get_or_create(service=self)

        if authentication.authentication_type == 'NONE':
            response = requests.get(self.endpoint)

        elif authentication.authentication_type == 'BASIC':
            response = requests.get(self.endpoint, auth=(authentication.auth_user, authentication.auth_pass))

        elif authentication.authentication_type == 'TOKEN':
            headers = {'Authorization': authentication.auth_token}
            response = requests.get(self.endpoint, headers=headers)

        elif authentication.authentication_type == 'DIGEST':
            auth = HTTPDigestAuth(authentication.auth_user, authentication.auth_pass)
            response = requests.get(self.endpoint, auth=auth)

        elif authentication.authentication_type == 'OAUTH1':
            oauth_provider = OAuth1Session(client_key=authentication.client_key,
                                           client_secret=authentication.client_secret,
                                           resource_owner_key=authentication.resource_owner_key,
                                           resource_owner_secret=authentication.resource_owner_secret)

            response = oauth_provider.get(self.endpoint)

        elif authentication.authentication_type == 'OAUTH2':
            oauth_provider = OAuth2Session(client_id=authentication.client_id,
                                           redirect_uri=authentication.redirect_uri)

            oauth_provider.fetch_token(authentication.access_token_url, client_secret=authentication.client_secret)
            response = oauth_provider.get(self.endpoint)
        else:
            response = requests.get(self.endpoint)

        return HttpResponse(content=response.content, status=response.status_code,
                            content_type=response.headers['Content-Type'])


class AuthenticationStrategy(ABC):
    @abstractmethod
    def authenticate(self, authentication_instance):
        pass

    @abstractmethod
    def get_headers(self, authentication_instance):
        pass


class NoAuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # No authentication required

    def get_headers(self, authentication_instance):
        return {}


class BasicAuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # Assuming no pre-authentication required

    def get_headers(self, authentication_instance):
        return {
            "Authorization": f"Basic {base64.b64encode(f'{authentication_instance.auth_user}:'
                                                       f'{authentication_instance.auth_pass}'
                                                       .encode()).decode()}"}


class TokenAuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # Assuming no pre-authentication required

    def get_headers(self, authentication_instance):
        return {"Authorization": authentication_instance.auth_token}


class DigestAuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # Assuming no pre-authentication required

    def get_headers(self, authentication_instance):
        auth = HTTPDigestAuth(authentication_instance.auth_user, authentication_instance.auth_pass)
        return auth


class OAuth1AuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # Assuming no pre-authentication required

    def get_headers(self, authentication_instance):
        oauth_provider = OAuth1Session(client_key=authentication_instance.client_key,
                                       client_secret=authentication_instance.client_secret,
                                       resource_owner_key=authentication_instance.resource_owner_key,
                                       resource_owner_secret=authentication_instance.resource_owner_secret)
        return oauth_provider.headers


class OAuth2AuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        return True  # Assuming no pre-authentication required

    def get_headers(self, authentication_instance):
        oauth_provider = OAuth2Session(client_id=authentication_instance.client_id,
                                       redirect_uri=authentication_instance.redirect_uri)

        oauth_provider.fetch_token(authentication_instance.access_token_url,
                                   client_secret=authentication_instance.client_secret)
        return oauth_provider.get(authentication_instance.service.endpoint, headers={}).headers


class PAEAuthStrategy(AuthenticationStrategy):
    def authenticate(self, authentication_instance):
        from pae.pae_authentication import PAEAuthentication
        return PAEAuthentication().authenticate(authentication_instance)

    @staticmethod
    def get_data(authentication_instance):
        from pae.pae_authentication import PAEAuthentication
        return PAEAuthentication().get_data(authentication_instance)

    def get_headers(self, authentication_instance):
        return {"Content-Type": "application/json"}


class Authentication(models.Model):
    service = models.OneToOneField('scheduler.Service', on_delete=models.CASCADE)
    authentication_handler = models.CharField(max_length=10, choices=[('DEFAULT', 'Default'), ('PAE', 'PAE')],
                                              default='default')
    authentication_type = models.CharField(max_length=20, default='NONE',
                                           choices=[('NONE', 'No Auth'), ('BASIC', 'Basic Auth'),
                                                    ('TOKEN', 'Basic PAEToken'), ('DIGEST', 'Digest Auth'),
                                                    ('OAUTH1', 'OAuth 1.0'), ('OAUTH2', 'OAuth 2.0')])

    auth_user = models.CharField(max_length=255, null=True, blank=True, help_text="Basic Auth + Digest Auth")
    auth_pass = models.CharField(max_length=255, null=True, blank=True, help_text="Basic Auth + Digest Auth")
    auth_token = models.CharField(max_length=255, null=True, blank=True, help_text="Basic PAEToken Auth")
    # OAUTH1.0
    client_key = models.CharField(max_length=255, null=True, blank=True, help_text="OAuth 1.0")
    resource_owner_key = models.CharField(max_length=255, null=True, blank=True, help_text="OAuth 1.0")
    resource_owner_secret = models.CharField(max_length=255, null=True, blank=True, help_text="OAuth 1.0")
    # OAUTH2.0
    client_id = models.CharField(max_length=100, null=True, blank=True, help_text="OAuth 2.0")
    client_secret = models.CharField(max_length=100, null=True, blank=True, help_text="OAuth 1.0 + OAuth 2.0")
    access_token_url = models.CharField(max_length=100, null=True, blank=True, help_text="OAuth 2.0")
    redirect_uri = models.CharField(max_length=100, null=True, blank=True, help_text="OAuth 2.0")

    def authenticate(self):
        strategy = self._get_authentication_strategy()
        return strategy.authenticate(self)

    def get_headers(self):
        strategy = self._get_authentication_strategy()
        return strategy.get_headers(self)

    def get_data(self):
        strategy = self._get_authentication_strategy()
        return strategy.get_data(self)

    def _get_authentication_strategy(self):
        strategies = {
            'NONE': NoAuthStrategy(),
            'BASIC': BasicAuthStrategy(),
            'TOKEN': TokenAuthStrategy(),
            'DIGEST': DigestAuthStrategy(),
            'OAUTH1': OAuth1AuthStrategy(),
            'OAUTH2': OAuth2AuthStrategy(),
            'PAE': PAEAuthStrategy(),
        }

        if self.authentication_handler == 'DEFAULT':
            return strategies.get(self.authentication_type)
        else:
            return strategies.get(self.authentication_handler)


class ServiceAction(models.Model):
    service = models.ForeignKey('scheduler.Service', related_name='actions', on_delete=models.CASCADE)
    method_name = models.CharField(max_length=255, help_text="Name of the method (e.g., reportStudentLackPerformance)")
    description = models.TextField(help_text="Description of the service action")
    request_template = models.JSONField(help_text="Template of the request body for this action")

    def __str__(self):
        return f"{self.method_name} ({self.service.name})"

    def get_filled_request_body(self, dynamic_data):
        """
        Fill the request template with dynamic data such as the BACOSESS token
        and any method-specific arguments.

        dynamic_data is a dictionary of values to replace in the template, e.g.,
        {"BACOSESS": "token_value", "importYear": "202021", "failRateThreshold": 70}
        """
        # Convert the request template to a string and use Django's templating engine
        request_template_str = json.dumps(self.request_template)
        template = Template(request_template_str)

        # Use the dynamic_data dictionary to replace the placeholders
        context = Context(dynamic_data)
        filled_request = template.render(context)

        # Convert the result back to JSON
        return json.loads(filled_request)

    def service_dispatcher(self):
        request = HttpRequest()
        if request.method == "POST":
            method_name = None
            try:
                body = json.loads(request.body)
                method_name = body.get('data', {}).get('methodName')
                service_arguments = body.get('data', {}).get('serviceArguments', [])

                if not method_name:
                    return HttpResponseBadRequest("methodName is required")

                # Fetch the Service and corresponding ServiceAction
                service = Service.objects.get(id=self.service)
                action = service.actions.get(method_name=method_name)

                # Fetch the BACOSESS token from the PAEToken model
                paetoken = PAEToken.objects.get(service=service)
                bacosess = paetoken.token

                # Build the dynamic data for the request template
                dynamic_data = {
                    "BACOSESS": bacosess,
                }
                for arg in service_arguments:
                    dynamic_data[arg['name']] = arg['value']

                # Fill the request template
                request_body = action.get_filled_request_body(dynamic_data)

                # Make the external request (e.g., POST)
                response = requests.post(service.endpoint, json=request_body)

                return JsonResponse(response.json(), status=response.status_code)

            except Service.DoesNotExist:
                return HttpResponseBadRequest(f"Service with ID {self.service} does not exist")
            except ServiceAction.DoesNotExist:
                return HttpResponseBadRequest(f"Invalid methodName: {method_name}")
            except json.JSONDecodeError:
                return HttpResponseBadRequest("Invalid JSON")
        else:
            return HttpResponseBadRequest("Only POST requests are allowed")
