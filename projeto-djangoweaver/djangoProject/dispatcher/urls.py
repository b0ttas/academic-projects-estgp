from django.urls import include, path
from rest_framework import routers

from .views import DestinationViewSet  # GroupViewSet

# define the router
router = routers.DefaultRouter()

# define the router path and view set to be used
router.register(r'destination', DestinationViewSet)

# specify URL Path for rest_framework
urlpatterns = [
    path('api-auth/', include('rest_framework.urls', namespace='rest_framework')),
]
