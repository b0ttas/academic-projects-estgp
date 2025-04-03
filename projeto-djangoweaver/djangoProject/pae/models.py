import uuid
from datetime import timedelta

from django.db import models
from django.utils import timezone

from utils.validators import validate_crontab


class PAEDestination(models.Model):
    email = models.EmailField()
    service = models.ForeignKey('scheduler.Service', on_delete=models.CASCADE, related_name='destinations')
    report_id = models.CharField(max_length=255, default='')
    is_active = models.BooleanField(default=True) # Indicates if the subscription is active

    #TODO: must be offered to the user a way to update the update interval via email token links
    last_updated = models.DateTimeField(default=timezone.now, blank=True, null=True, editable=False)
    cron_update_interval = models.CharField(max_length=100, blank=True, null=True, validators=[validate_crontab],
                                            default='* * * * *',
                                            help_text="Here you can specify an interval for updates, following the "
                                                      "use of Cron expressions, valid examples are '* 12 * * ?', ")

    class Meta:
        verbose_name = "PAE Destination"
        verbose_name_plural = "PAE Destinations"
        constraints = [
            models.UniqueConstraint(
                fields=['email', 'service', 'report_id'], name='unique_email_service_report_combination',
            )
        ]
        indexes = [models.Index(fields=['service', 'report_id', 'is_active'])]

    def __str__(self):
        return f"{self.email} ({'Active' if self.is_active else 'Inactive'})"

class PAEToken(models.Model):
    token = models.CharField(max_length=255)
    expiration_time = models.DateTimeField()

    def __str__(self):
        return self.token

class PAEEmail(models.Model):
    destination = models.ForeignKey(PAEDestination, on_delete=models.CASCADE, related_name='emails')
    subject = models.CharField(max_length=255)
    body = models.TextField()
    date_sent = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.subject} ({self.date_sent.strftime('%Y-%m-%d')})"

class PAEAttachment(models.Model):
    email = models.ForeignKey(PAEEmail, on_delete=models.CASCADE, related_name='attachments')
    file = models.FileField(upload_to='./data/attachments/')
    filename = models.CharField(max_length=255)

    def __str__(self):
        return self.filename

class PAESentReport(models.Model):
    user = models.ForeignKey(PAEDestination, on_delete=models.CASCADE)
    subject = models.CharField(max_length=255)
    body = models.TextField()
    sent_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name = "PAE Sent Report"
        verbose_name_plural = "PAE Sent Reports"

class PAEUserAccessToken(models.Model):
    destination = models.ForeignKey(PAEDestination, on_delete=models.CASCADE, related_name='access_tokens')
    token = models.UUIDField(default=uuid.uuid4, unique=True, editable=False)
    expires_at = models.DateTimeField()

    class Meta:
        verbose_name = "PAE User Access Token"
        verbose_name_plural = "PAE User Access Tokens"

    def is_expired(self):
        return timezone.now() > self.expires_at

    def save(self, *args, **kwargs):
        if not self.token:
            self.token = uuid.uuid4()
        if not self.expires_at:
            self.expires_at = timezone.now() + timedelta(days=7)
        super().save(*args, **kwargs)

    def is_valid(self):
        return timezone.now() < self.expires_at

    def __str__(self):
        return f"Token for {self.destination.email} (Expires: {self.expires_at})"
