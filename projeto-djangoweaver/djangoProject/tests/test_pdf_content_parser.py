from django.test import TestCase

from utils.pdf_content_parser import build_auto_pdf_from_content


class DataTypeTestCase(TestCase):
    def setUp(self):
        self.my_list = {
            'text': "Hello",
            'int': 123,
            'float': 45.67,
            'bool': True,
            'null': None,
            'object': {"key": "value"},
            'list': [1, 2, 3]
        }

    def test_build_auto_pdf_from_content(self):
        story = []
        story = build_auto_pdf_from_content(story, self.my_list)
        self.assertIsInstance(story, list)
