import json
import os
import re
import smtplib
from email.message import EmailMessage
from typing import Iterable

from scheduler.models import Service
from utils.mapping_handler import handle_service_mapping
from dispatcher.models import Destination


def is_valid_email(email):
    pattern = r'^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,7}$'
    return re.match(pattern, email) is not None


def collect_delivery_addresses(service: Service) -> tuple[list[str], list[str]]:
    #TODO, instead, add method to Destinations and PAEDestinations
    #TODO, getDestinationsFromService and getAllDestinationsFromService
    delivery_urls = []
    delivery_emails = []

    for destination in Destination.get_all_destinations_from_service(service):
        # TODO: iterate destinations and add expired only
        if is_valid_email(destination.url):
            delivery_emails.append(destination.url)
        else:
            delivery_urls.append(destination.url)

    return delivery_urls, delivery_emails

def send_email(service: Service, recipients: Iterable, attachment_paths: Iterable, file_binary_data: bytes) -> bool:
    email = EmailMessage()
    email['From'] = os.getenv("SENDER_EMAIL")
    email['Bcc'] = recipients
    email['Subject'] = service.name
    mapping_content = []

    if service.mapping is not None:
        if file_binary_data == b'' and service.output_type != 'PDF':
            for path in attachment_paths:
                try:
                    with open(path, "rb") as file:
                        binary_data = file.read()
                        file_binary_data = binary_data
                except FileNotFoundError:
                    file_binary_data = b''
        if file_binary_data == b'':
            file_binary_data = json.dumps(service.mapping).encode()
        if file_binary_data != b'':
            json_str = json.dumps(service.mapping)
            mapping = json.loads(json_str)
            mapping_content = handle_service_mapping(mapping, file_binary_data)

    if mapping_content['mail_subject']:
        text = '\n'.join(mapping_content['mail_subject'])
        del email['Subject']
        email['Subject'] = text

    if mapping_content['mail_body']:
        text_list = mapping_content['mail_body']
        email.set_content('\n'.join(text_list))
    elif service.email_text is not None:
        email.set_content(service.email_text)
    else:
        email.set_content(service.name)

    # Adding attachments
    if service.output_type == 'EMAIL_ATTACHMENT' or service.output_type == 'PDF':
        for filepath in attachment_paths:
            filename = filepath.split("/")[-1]
            with open(filepath, "rb") as f:
                email.add_attachment(f.read(), maintype='application', subtype='octet-stream', filename=filename)

    try:
        with smtplib.SMTP('smtp-mail.outlook.com', 587) as server:
            server.starttls()  # Use TLS encryption
            server.login(os.getenv("SENDER_EMAIL"), os.getenv("EMAIL_PASSWORD"))
            server.send_message(email)
        return True
    except Exception as e:
        print(f"Error sending email: './{str(e)}'")
        return False
