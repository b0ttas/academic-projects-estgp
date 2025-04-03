from rest_framework import serializers

from scheduler.serializers import ServiceSerializer
from .models import PAEDestination, PAEEmail, PAEAttachment


class AttachmentSerializer(serializers.ModelSerializer):
    class Meta:
        model = PAEAttachment
        fields = ['id', 'filename', 'file']


class EmailSerializer(serializers.ModelSerializer):
    attachments = AttachmentSerializer(many=True, read_only=True)

    class Meta:
        model = PAEEmail
        fields = ['id', 'subject', 'body', 'date_sent', 'attachments']


class DestinationSerializer(serializers.ModelSerializer):
    service = ServiceSerializer(read_only=True)  # This will include the service info for each destination

    class Meta:
        model = PAEDestination
        fields = ['email', 'service', 'is_active']

class SubscriptionDetailSerializer(serializers.ModelSerializer):
    emails = EmailSerializer(many=True, read_only=True)  # List of emails for each destination
    service = ServiceSerializer(read_only=True)  # Include service details

    class Meta:
        model = PAEDestination
        fields = ['service', 'is_active', 'emails']  # Include the service and its emails
