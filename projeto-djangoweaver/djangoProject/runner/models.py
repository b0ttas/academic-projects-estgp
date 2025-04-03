import datetime

from django.db import models


class RunnerResponse(models.Model):
    service = models.ForeignKey('scheduler.Service', on_delete=models.CASCADE)
    raw_response = models.BinaryField()
    status_code = models.IntegerField()
    created_at = models.DateTimeField(auto_now_add=True)


class Attachment(models.Model):
    FILE_TYPE = (
        ('PDF', 'pdf'),
        ('JSON', 'json'),
        ('XML', 'xml'),
    )
    service = models.ForeignKey('scheduler.Service', on_delete=models.CASCADE)
    response = models.ForeignKey(RunnerResponse, on_delete=models.CASCADE, related_name='attachment')
    type = models.CharField(max_length=20, choices=FILE_TYPE)
    file = models.FileField(upload_to='attachments/%(service)s/')  # Dynamic upload path
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.service}.{self.file.name}"  # Update name format

    def save(self, *args, **kwargs):
        # Generate unique filename with timestamp before saving
        timestamp = datetime.datetime.now().strftime("%Y-%m-%dT%H-%M-%S")
        filename = f"{self.service}.{timestamp}.{self.type}"
        self.file.name = filename
        super().save(*args, **kwargs)
