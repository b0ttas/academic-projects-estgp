import os
import shutil
from datetime import datetime
from typing import Iterable

import requests
from celery import shared_task
from croniter import croniter
from django.utils import timezone

import utils.smtp
import utils.ftp
from logger.models import Log
from scheduler.models import Service
from utils.file_handlers import get_or_create_output_and_archive_folders


@shared_task()
def check_tasks() -> None:
    """
    Dispatcher task runs every minute
    """
    Log.objects.create(log_level="1", message="Scheduled task started", content="", message_type="info")
    # print("DISPATCHER: process started")
    services = Service.get_all_periodic_expired()

    amount = services.count()
    Log.objects.create(log_level="1", message="Tasks found: " + str(amount), content="", message_type="info")
    # print('DISPATCHER: tasks found: ' + str(amount))

    for service in services:
        input_path, output_path = get_or_create_output_and_archive_folders(service.name)

        if os.path.exists(input_path):
            # Get the most recent file in the directory based on filename
            files = os.listdir(input_path)
            if not files:
                Log.objects.create(log_level="1", message=f"DISPATCHER: No files found in './{service.name}'.",
                                   content="", message_type="warning")
                # print(f"DISPATCHER: No files found in './{service.name}'.")
                continue
            else:
                files.sort(key=lambda x: os.path.getctime(os.path.join(input_path, x)))
                most_recent_file = files[-1]
                input_file_path = input_path + '/' + most_recent_file
                file_timestamp = most_recent_file.split("_")[0]

                if os.getenv('TEST_MODE') == 'TRUE':
                    distribute(service=service, attachment_paths=[input_file_path], output_path=output_path)
                else:
                    if not is_file_still_valid(service, file_timestamp):
                        continue

                    distribute.delay(service=service, attachment_paths=[input_file_path], output_path=output_path)
                    Log.objects.create(log_level="1", message="DISPATCHER: distribution started", content="",
                                       message_type="info")
                    # print("DISPATCHER: distribution started")
        else:
            os.makedirs(input_path, exist_ok=True)
            Log.objects.create(log_level="1", message="DISPATCHER: Input folder non-existent. Skipping...",
                               content="", message_type="info")
            # print("DISPATCHER: Input folder non-existent. Skipping...")
    Log.objects.create(log_level="1", message="DISPATCHER: process finished", content="",
                       message_type="info")
    # print('DISPATCHER: process finished')


@shared_task()
def distribute(service: Service, attachment_paths: Iterable, output_path: str):
    delivery_urls, delivery_emails = utils.smtp.collect_delivery_addresses(service)

    if len(delivery_urls) > 0:
        send_as_file(attachment_paths=attachment_paths, recipients=delivery_urls)
    if len(delivery_emails) > 0:
        send_as_email(service=service, attachment_paths=attachment_paths, recipients=delivery_emails)

    service.last_updated = timezone.now()
    service.save(update_fields=['last_updated'])

    for filepath in attachment_paths:
        filename = filepath.split("/")[-1]
        if output_path is not None:
            output_filepath = output_path + '/' + filename
            shutil.move(filepath, output_filepath)


def send_as_email(service: Service, attachment_paths: Iterable, recipients: Iterable):
    return utils.smtp.send_email(service=service, attachment_paths=attachment_paths, file_binary_data=b'',
                                 recipients=recipients)


def send_as_file(attachment_paths: Iterable, recipients: Iterable):
    for item in recipients:
        if item.startswith("ftp://"):
            # Send files via FTP
            return utils.ftp.send_files_via_ftp(url=item, attachment_paths=attachment_paths)
        else:
            # Send an HTTP request with the same data
            for attachment_path in attachment_paths:
                with open(attachment_path, 'rb') as file:
                    return requests.post(item, files={'file': file})


def is_file_still_valid(service, file_timestamp):
    file_datetime = datetime.strptime(file_timestamp, "%Y%m%d-%H%M%S")
    file_datetime_aware = file_datetime.replace(tzinfo=timezone.get_current_timezone())

    # deadline = file_datetime_aware + service.update_interval

    cron_iterable = croniter(service.cron_update_interval, file_datetime_aware)
    next_update = cron_iterable.get_next(datetime)

    should_update = file_datetime_aware >= next_update
    return should_update
