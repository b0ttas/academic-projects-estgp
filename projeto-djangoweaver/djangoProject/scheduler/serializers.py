from rest_framework import serializers
from .models import Service


class ServiceSerializer(serializers.HyperlinkedModelSerializer):
    # specify model and fields
    class Meta:
        model = Service
        fields = ('name', 'endpoint')
