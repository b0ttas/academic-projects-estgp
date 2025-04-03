import json

from django.http import HttpResponse
from django.test import TestCase

from pae.handle_pae_response import handle_pae_response
from utils.pdf_build import generate_pdf
from .models import Service, Authentication
from utils.response_handlers import create_pdf_and_send


class HandleResponseTestCase(TestCase):
    def setUp(self):
        with open('scheduler/test_sample_pae_response.json') as json_file:
            self.json_response = json.load(json_file)

    def test_pae_pdf_generate(self):
        # Creating a mock service with input and output types
        service = Service.objects.create(input_data_type='JSON', output_type='EMAIL_ATTACHMENT', name='tests')
        authentication = Authentication.objects.create(service=service, authentication_handler='PAE')
        data = HttpResponse()
        data.status_code = '200'
        data.content = json.dumps(self.json_response).encode('utf-8')

        test = generate_pdf(data.content, service)
        create_pdf_and_send(service, test)

    def test_handle_pae_response(self):
        # Creating a mock service with input and output types
        service = Service.objects.create(input_data_type='JSON', output_type='EMAIL_ATTACHMENT', name='tests')
        authentication = Authentication.objects.create(service=service, authentication_handler='PAE')
        data = HttpResponse()
        data.status_code = '200'
        data.content = json.dumps(self.json_response)

        test = handle_pae_response(data, service)
        self.assertEqual(data.status_code, 200)
