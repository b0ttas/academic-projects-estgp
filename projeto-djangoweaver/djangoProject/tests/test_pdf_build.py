from django.test import TestCase

from scheduler.models import Service
from utils.pdf_build import generate_pdf


class PDFAutoBuildTestCase(TestCase):
    def setUp(self):
        self.test_string = ('{"data":[{"status":{"verified":true,"sentCount":1},"_id":"58e008780aac31001185ed05",'
                            '"user":"58e007480aac31001185ecef","text":"Owning a cat can reduce the risk of stroke and '
                            'heart attack by a third.","__v":0,"source":"user",'
                            '"updatedAt":"2020-08-23T20:20:01.611Z","type":"cat",'
                            '"createdAt":"2018-03-29T20:20:03.844Z","deleted":false,"used":false},{"status":{'
                            '"verified":true,"sentCount":1},"_id":"58e009390aac31001185ed10",'
                            '"user":"58e007480aac31001185ecef","text":"Most cats are lactose intolerant, and milk can '
                            'cause painful stomach cramps and diarrhea. It\'s best to forego the milk and just give '
                            'your cat the standard: clean, cool drinking water.","__v":0,"source":"user",'
                            '"updatedAt":"2020-08-23T20:20:01.611Z","type":"cat",'
                            '"createdAt":"2018-03-04T21:20:02.979Z","deleted":false,"used":false},{"status":{'
                            '"verified":true,"sentCount":1},"_id":"588e746706ac2b00110e59ff",'
                            '"user":"588e6e8806ac2b00110e59c3","text":"Domestic cats spend about 70 percent of the '
                            'day sleeping and 15 percent of the day grooming.","__v":0,"source":"user",'
                            '"updatedAt":"2020-08-26T20:20:02.359Z","type":"cat",'
                            '"createdAt":"2018-01-14T21:20:02.750Z","deleted":false,"used":true},{"status":{'
                            '"verified":true,"sentCount":1},"_id":"58e008ad0aac31001185ed0c",'
                            '"user":"58e007480aac31001185ecef","text":"The frequency of a domestic cat\'s purr is the '
                            'same at which muscles and bones repair themselves.","__v":0,"source":"user",'
                            '"updatedAt":"2020-08-24T20:20:01.867Z","type":"cat",'
                            '"createdAt":"2018-03-15T20:20:03.281Z","deleted":false,"used":true},{"status":{'
                            '"verified":true,"sentCount":1},"_id":"58e007cc0aac31001185ecf5",'
                            '"user":"58e007480aac31001185ecef","text":"Cats are the most popular pet in the United '
                            'States: There are 88 million pet cats and 74 million dogs.","__v":0,"source":"user",'
                            '"updatedAt":"2020-08-23T20:20:01.611Z","type":"cat",'
                            '"createdAt":"2018-03-01T21:20:02.713Z","deleted":false,"used":false}]}')

        self.my_list = bytes(self.test_string, 'utf-8')

        self.my_service = Service.objects.create(
            id=1,
            name='JSON2PDF - Cat facts',
            delivery='REQUEST',
            endpoint='https://cat-fact.herokuapp.com/facts',
            delivery_endpoint='cat',
            input_data_type='JSON',
            output_type='PDF',
            pdf_template='templates/pdf/Cat_facts.pdf',
            mapping={'help': "You can replace every value with a matching key from the service using 'reply.'",
                     'mail_body': 'This is an example', 'mail_subject': 'reply.title', 'pdf_auto_mapping': True,
                     'pdf_text': 'body', 'pdf_title': 'body', 'reset_mapping': False}
        )

    def test_build_auto_pdf_from_content(self):
        story = generate_pdf(self.my_list, self.my_service)
        pdf_path = f"./templates/pdf/tests/output" + ".pdf"

        with open(pdf_path, 'wb') as output_stream:
            output_stream.write(story)

        self.assertIsNotNone(story)
