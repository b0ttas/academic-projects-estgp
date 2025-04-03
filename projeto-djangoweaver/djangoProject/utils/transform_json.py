
def transform_json(input_data, template: dict):
    output_data = {}

    for key, value in template.items():
        if key.startswith("custom_"):
            output_data[key] = value
        elif isinstance(value, dict):
            output_data[key] = transform_json(input_data.get(key), value)
        elif isinstance(value, list):
            output_data[key] = []
            for sub_template in value:
                if isinstance(sub_template, dict):
                    output_data[key] = [transform_json(item2, sub_template) for item2 in input_data.get(key)]
                else:
                    output_data[key] = input_data.get(key)
        elif value == "display":
            output_data[key] = input_data.get(key)
        elif value == "hide":
            pass
        else:
            pass

    return output_data
