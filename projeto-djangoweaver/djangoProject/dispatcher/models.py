from django.contrib.auth.models import User
from django.db import models
from django.utils import timezone

from utils.validators import validate_email_or_url, validate_crontab


class Destination(models.Model):
    service = models.ForeignKey('scheduler.Service', on_delete=models.CASCADE)
    description = models.TextField(blank=True, null=True)
    url = models.CharField(max_length=200, validators=[validate_email_or_url])
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    last_updated = models.DateTimeField(default=timezone.now, blank=True, null=True, editable=False)
    cron_update_interval = models.CharField(max_length=100, blank=True, null=True, validators=[validate_crontab],
                                            default='* * * * *',
                                            help_text="Here you can specify an interval for updates, following the "
                                                      "use of Cron expressions, valid examples are '* 12 * * ?', ")

    def get_update_interval(self):
        pass

    def __str__(self):
        return f"{self.service} - {self.cron_update_interval} - {self.url}"

    @staticmethod
    def get_all_destinations_from_service(service):
        return Destination.objects.filter(service=service)