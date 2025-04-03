import os
import shutil
from datetime import datetime

from celery import shared_task
from croniter import croniter
from django.utils import timezone

from logger.models import Log
from runner.models import RunnerResponse
from scheduler.models import Service
from utils.file_handlers import save_response_to_file, save_handled_data_to_file, \
    get_or_create_output_and_archive_folders
from utils.response_handlers import handle_response


@shared_task()
def check_tasks():
    Log.objects.create(log_level="1", message="RUNNER: process started", content="", message_type="info")

    services = Service.get_all_periodic_expired()
    amount = services.count()

    Log.objects.create(log_level="1", message=f'RUNNER: tasks found: {amount}', content="", message_type="info")

    for service in services:
        input_path, output_path = get_or_create_output_and_archive_folders(service.name)

        if os.path.exists(input_path):
            files = os.listdir(input_path)
            if not files:
                print(f"RUNNER: No files found in './{service.name}', making new request")
            else:
                is_update = handle_update_interval(service)
                if not is_update:
                    continue
        else:
            print(f"RUNNER: No folder found for '{service.name}', creating new folder and making request")

        response = service.send_request()
        RunnerResponse.objects.create(service=service, raw_response=response.content, status_code=response.status_code)

        if response:
            timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
            save_response_to_file(response, service, timestamp)

            handled_data = handle_response(response, service)
            if handled_data.status_code != 500:
                save_handled_data_to_file(handled_data, service, timestamp)

            print(f"RUNNER: Processed service '{service.name}'")
        else:
            print(f"RUNNER: Failed to get response from '{service.endpoint}', status code: '{response.status_code}'")
    print('RUNNER: process finished')


@shared_task()
def archive_process():
    services = Service.objects.all()
    for service in services:
        input_path, output_path = get_or_create_output_and_archive_folders(service_name=service.name)
        if os.path.exists(input_path):
            for filename in os.listdir(input_path):
                source_file = os.path.join(input_path, filename)
                file_timestamp = source_file.split("_")[0]
                if not is_file_still_valid(service, file_timestamp):
                    destination_file = os.path.join(output_path, filename)
                    shutil.move(source_file, destination_file)
                    print(f"Moved {filename} to {output_path}")
        else:
            print(f"Input path '{input_path}' does not exist.")


def is_file_still_valid(service, file_timestamp):
    file_datetime = datetime.strptime(file_timestamp, "%Y%m%d-%H%M%S")
    file_datetime_aware = file_datetime.replace(tzinfo=timezone.get_current_timezone())

    # deadline = file_datetime_aware + service.update_interval

    cron_iterable = croniter(service.cron_update_interval, file_datetime_aware)
    next_update = cron_iterable.get_next(datetime)

    should_update = file_datetime_aware >= next_update
    return should_update

    # if deadline < datetime.now():
    #     return False
    # else:
    #     return True


def handle_update_interval(service: Service) -> bool:
    current_time = timezone.now()
    # update_deadline = service.get_last_updated() + service.update_interval
    cron_iterable = croniter(service.cron_update_interval, service.get_last_updated())
    next_update = cron_iterable.get_next(datetime)

    should_update = current_time >= next_update
    return should_update

    # if update_deadline > current_time:
    #     print(f"RUNNER: File for '{service.name}' is still valid")
    #     return False
    # else:
    #     print(f"RUNNER: File for '{service.name}' is expired, making new request")
    #     return True
