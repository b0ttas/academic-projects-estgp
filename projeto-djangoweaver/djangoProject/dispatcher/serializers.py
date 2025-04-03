from rest_framework import serializers

# import model from models.py
from .models import *


# Create a model serializer
class DestinationSerializer(serializers.HyperlinkedModelSerializer):
    # specify model and fields
    class Meta:
        model = Destination
        fields = ('url', 'description')
