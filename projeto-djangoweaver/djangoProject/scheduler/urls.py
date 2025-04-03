from django.urls import path
from rest_framework.routers import DefaultRouter

from .views import ServiceCustomViewSet, endpoint_internal, ServiceViewSet

router = DefaultRouter()
router.register(r'services_callable', ServiceCustomViewSet, basename='services_callable')
router.register(r'services', ServiceViewSet, basename='services')

urlpatterns = [
    path('services/<str:endpoint>/', endpoint_internal, name='endpoint_internal'),
]
