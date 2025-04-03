import unittest
from utils.mapping_handler import handle_service_mapping


class TestHandleServiceMapping(unittest.TestCase):
    def test_handle_service_mapping(self):
        # Sample mapping and file binary data
        mapping = {
            "name": "user.name",
            "email": "user.email",
            "help": "ignore.this"
        }
        file_binary_data = b'{"user": {"name": "John Doe", "email": "john.doe@example.com"}}'

        # Expected result
        expected_result = {
            "name": "John Doe",
            "email": "john.doe@example.com"
        }

        # Call the function
        result = handle_service_mapping(mapping, file_binary_data)

        # Assert the result
        self.assertEqual(result, expected_result)

    def test_invalid_json(self):
        mapping = {
            "name": "user.name"
        }
        file_binary_data = b'Invalid JSON'

        with self.assertRaises(ValueError):
            handle_service_mapping(mapping, file_binary_data)

    def test_missing_key(self):
        mapping = {
            "name": "user.name",
            "age": "user.age"
        }
        file_binary_data = b'{"user": {"name": "John Doe"}}'

        expected_result = {
            "name": "John Doe",
            "age": None
        }

        result = handle_service_mapping(mapping, file_binary_data)

        self.assertEqual(result, expected_result)


if __name__ == '__main__':
    unittest.main()
