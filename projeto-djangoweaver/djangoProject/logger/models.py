from django.db import models


class Log(models.Model):
    DATETIME_FORMAT = '%Y-%m-%d %H:%M:%S'

    MESSAGE_TYPES = [
        ('success', 'Success'),
        ('warning', 'Warning'),
        ('info', 'Info'),
        ('error', 'Error'),
    ]

    LOG_LEVEL = [
        ('1', 'Minimal'),
        ('2', 'Below Average'),
        ('3', 'Average'),
        ('4', 'Major'),
        ('5', 'Verbose'),
    ]

    timestamp = models.DateTimeField(auto_now_add=True)
    message = models.CharField(max_length=255)
    content = models.TextField()
    message_type = models.CharField(max_length=7, choices=MESSAGE_TYPES)
    log_level = models.CharField(max_length=15, choices=LOG_LEVEL)

    def save(self, *args, **kwargs):
        super().save(*args, **kwargs)
        if self.log_level >= '3':
            print(f"{self}")

    def __str__(self):
        return f"[{self.timestamp.strftime(self.DATETIME_FORMAT)}] {self.get_message_type_display()}: {self.message}"
