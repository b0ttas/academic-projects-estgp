from typing import Dict

import json


def extract_values(search_key, data):
    """Extracts all values associated with a given key from a JSON structure.

    Args:
        search_key: The key to search for.
        data: The JSON data to search in.

    Returns:
        A list of extracted values.
    """

    results = []

    def recursive_search(json_data):
        if isinstance(json_data, dict):
            for key, value in json_data.items():
                if key == search_key:
                    results.append(value)
                recursive_search(value)
        elif isinstance(json_data, list):
            for item in json_data:
                recursive_search(item)

    recursive_search(data)

    if not results:  # Add the original information if no match is found
        results.append(search_key)
    return results


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
            result[key] = extract_values(value, data)
        elif isinstance(value, dict):
            # Handle nested mappings
            result[key] = map_json(value, data)
        else:
            # Handle other data types (e.g., lists, numbers)
            result[key] = value  # Consider appropriate handling
    return result


def handle_service_mapping(mapping: dict, file_binary_data: bytes) -> Dict[str, str]:
    try:
        data = json.loads(file_binary_data.decode())  # Load the response content as JSON
    except json.JSONDecodeError:
        raise ValueError("Invalid JSON content in file_binary_data")

    return map_json(mapping, data)
