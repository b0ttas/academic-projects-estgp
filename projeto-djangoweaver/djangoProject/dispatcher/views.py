from rest_framework import permissions, viewsets

from .models import Destination  # , Group
from .serializers import DestinationSerializer  # , GroupSerializer


class DestinationViewSet(viewsets.ModelViewSet):
    queryset = Destination.objects.all()
    serializer_class = DestinationSerializer
    permission_classes = [permissions.IsAuthenticated]