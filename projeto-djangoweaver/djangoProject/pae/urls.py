from django.urls import include, path
from rest_framework import routers

from pae.views import test_endpoints, email_history, manage_subscriptions, unsubscribe, refresh_token

from .views import (
    PaeViewSet,
    UnsubscribeAllView,
    DownloadEmailView,
    DownloadAttachmentView,
    DownloadMultipleEmailsView,
    generate_access_token
)

router = routers.DefaultRouter()
router.register(r'pae', PaeViewSet)

urlpatterns = [
    path('api/pae/test/<str:token>/', test_endpoints, name='pae_test'),
    path('api/pae/unsubscribe/<str:token>/', unsubscribe, name='unsubscribe'),
    path('api/pae/email_history/<str:token>/', email_history, name='email_history'),
    path('api/pae/manage_subscriptions/<str:token>/', manage_subscriptions, name='manage_subscriptions'),
    path('api/pae/refresh_token/<str:token>/', refresh_token, name='refresh_token'),
]