import re

from croniter.croniter import croniter
from django.core.exceptions import ValidationError
from django.core.validators import validate_email


def validate_email_or_url(value):
    url_pattern = re.compile(r'^(https?|ftp)://\S+$')
    try:
        validate_email(value)
        return True
    except ValidationError:
        if url_pattern.match(value):
            return True
        else:
            raise ValidationError("Please enter a valid email address or URL.")


def validate_crontab(crontab):
    is_valid = croniter.is_valid(crontab)
    if not is_valid:
        raise ValidationError('This string is not a valid cron expression')
