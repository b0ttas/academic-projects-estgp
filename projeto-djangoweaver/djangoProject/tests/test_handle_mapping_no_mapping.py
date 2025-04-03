import unittest


class TestHandleServiceMapping(unittest.TestCase):
    def test_handle_service_mapping(self):
        # Example usage
        input_data = {
            "data": [
                {
                    "id": "2cd15e5a-1013-4f23-abd5-45cbdceba59c",
                    "type": "fact",
                    "attributes": {
                        "body": "Female dogs carry puppies for about nine weeks before birth."
                    }
                },
                {
                    "id": "2cd15e5a-1234-5678-9012-45cbdceba59c",
                    "type": "wololo",
                    "attributes": {
                        "body": "Cotton candy is a great treat about nine weeks before birth."
                    }
                }
            ]
        }

        custom_mapping = {
            'help': "You can replace every value with a matching key from the returning endpoint.'",
            'reset_mapping': False,
            'mail_subject': '',
            'mail_body': 'body',
            'pdf_title': '',
            'pdf_text': 'body'
        }

        expected_result = {
            'help': "You can replace every value with a matching key from the returning endpoint.'",
            'reset_mapping': False,
            'mail_subject': '',
            'mail_body': "Female dogs carry puppies for about nine weeks before birth.",
            'pdf_title': '',
            'pdf_text': "Female dogs carry puppies for about nine weeks before birth."
        }

        result = map_json(custom_mapping, input_data)
        # Assert the result
        self.assertEqual(expected_result, result)


def map_json(mapping, data):
    """Maps a JSON structure based on a provided mapping dictionary.

    Args:
        mapping: A dictionary containing mapping rules.
        data: The JSON data to be mapped.

    Returns:
        The mapped JSON structure.
    """

    result = {}
    for key, value in mapping.items():
        if key in ['help', 'reset_mapping']:
            result[key] = value
        elif not value:
            result[key] = value
        elif isinstance(value, str):
            # Handle string values (e.g., 'data[0].attributes.body')
            result[key] = _extract_values(value, data)
        elif isinstance(value, dict):
            # Handle nested mappings
            result[key] = map_json(value, data)
        else:
            # Handle other data types (e.g., lists, numbers)
            result[key] = value  # Consider appropriate handling
    return result


def _extract_values(search_key, data):
    """Extracts all values associated with a given key from a JSON structure.

    Args:
        search_key: The key to search for.
        data: The JSON data to search in.

    Returns:
        A list of extracted values.
    """

    results = []

    def _recursive_search(json_data):
        if isinstance(json_data, dict):
            for key, value in json_data.items():
                if key == search_key:
                    results.append(value)
                _recursive_search(value)
        elif isinstance(json_data, list):
            for item in json_data:
                _recursive_search(item)

    _recursive_search(data)
    return results


if __name__ == '__main__':
    unittest.main()
