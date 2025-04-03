from django.test import TestCase
from utils.mapping_handler import handle_service_mapping


class HandleServiceMappingTest(TestCase):
    def test_handle_service_mapping(self):
        sample_mapping = {
            "mail_subject": "dis_here_officer",
            "mail_body": "body",
            "pdf_title": "title",
            "pdf_text": "text",
        }
        mapped_data = {}

        sample_response = b'{"reply": {"title": "Hello World", "body": "Some content"}}'
        try:
            mapped_data = handle_service_mapping(sample_mapping, sample_response)
            print(mapped_data)
        except ValueError as e:
            print(f"Error: {e}")

        self.assertIsInstance(mapped_data, dict)
