from django.test import TestCase


def transform_json(input_data, template):
    """Transforms the input JSON data based on the given template.

    Args:
        input_data: The input JSON data.
        template: The template JSON.

    Returns:
        The transformed JSON data.
    """

    output_data = {}

    for key, value in template.items():
        if key.startswith("custom_"):
            output_data[key] = value
        elif isinstance(value, dict):
            output_data[key] = [transform_json(item, value) for item in input_data.get(key)]
        elif isinstance(value, list):
            output_data[key] = [transform_json(item, dict(value)) for item in input_data.get(key)]
        elif value == "display":
            output_data[key] = input_data.get(key)
        elif value == "hide":
            pass
        else:
            pass

    return output_data


class TestNewMappingLogic(TestCase):
    def setUp(self):
        self.input_data = {
            "data": [{
                "status": {
                    "verified": True,
                    "sentCount": 1
                },
                "_id": "58e00b5f0aac31001185ed24",
                "user": "58e007480aac31001185ecef",
                "text": "When asked if her husband had any hobbies, "
                        "Mary Todd Lincoln is said to have replied \"cats.\"",
                "__v": 0,
                "source": "user",
                "updatedAt": "2020-08-23T20:20:01.611Z",
                "type": "cat",
                "createdAt": "2018-02-19T21:20:03.434Z",
                "deleted": False,
                "used": False
            }, {
                "status": {
                    "verified": True,
                    "sentCount": 1
                },
                "_id": "58e00b5f0aac31001185ed24",
                "user": "58e007480aac31001185ecef",
                "text": "This is some other text",
                "__v": 0,
                "source": "user",
                "updatedAt": "2020-08-23T20:20:01.611Z",
                "type": "cat",
                "createdAt": "2018-02-19T21:20:03.434Z",
                "deleted": False,
                "used": False
            }]
        }

        self.template = {
            "custom_header": "This is a custom header",
            "data": {
                "status": "hide",
                "_id": "hide",
                "user": "hide",
                "custom_text": "This is a custom text",
                "text": "display",
                "__v": "hide",
                "source": "hide",
                "updatedAt": "hide",
                "type": "hide",
                "createdAt": "hide",
                "deleted": "hide",
                "used": "hide"
            },
            "custom_footer": "This is a custom footer"
        }

    def test_transform_json(self):
        expected_result = {
            "custom_header": "This is a custom header",
            "data": [
                {
                    "custom_text": "This is a custom text",
                    "text": "When asked if her husband had any hobbies, Mary Todd Lincoln is said to have replied "
                            "\"cats.\"",
                },
                {
                    "custom_text": "This is a custom text",
                    "text": "This is some other text",
                }
            ],
            "custom_footer": "This is a custom footer"
        }

        output_data = transform_json(self.input_data, self.template)
        print("break")
        self.assertEqual(output_data, expected_result)
