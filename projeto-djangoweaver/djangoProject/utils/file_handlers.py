import os

from django.http import HttpResponse

from scheduler.models import Service


def get_or_create_output_and_archive_folders(service_name: str) -> tuple[str, str]:
    input_path = os.getenv('INPUT_PATH') + service_name
    output_path = os.getenv('OUTPUT_PATH') + service_name
    os.makedirs(input_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    return input_path, output_path


def save_response_to_file(response: HttpResponse, service: Service, timestamp: str) -> str:
    content_mapping = {
        'JSON': '.json',
        'XML': '.xml',
        'CSV': '.csv',
        'TEXT': '.txt'
    }
    output_path = f"./runner/output/{service.name}/{timestamp}_{service.name}"
    file_extension = content_mapping.get(service.input_data_type, '.unknown')
    output_path += file_extension
    with open(output_path, 'w') as file:
        file.write(response.content.decode())
    return output_path


def save_handled_data_to_file(handled_data: HttpResponse, service: Service, timestamp: str) -> None:
    content_type = handled_data.headers['Content-Type']
    if service.input_data_type != service.output_type:
        if service.output_type == 'EMAIL' or service.output_type == 'EMAIL_ATTACHMENT':
            service.output_type = service.input_data_type

        content_mapping = {
            'application/json': '.json',
            'text/html': '.html',
            'application/pdf': '.pdf',
            'application/xml': '.xml',
            'text/plain': '.txt',
            'text/csv': '.csv'
        }

        file_extension = content_mapping.get(content_type, '.unknown')
        output_path = f"./runner/output/{service.name}/{timestamp}_{service.name}" + file_extension

        if file_extension == '.pdf':
            with open(output_path, 'wb') as file:
                file.write(handled_data.content)
        else:
            with open(output_path, 'w') as file:
                file.write(handled_data.content.decode())
