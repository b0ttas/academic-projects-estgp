from django.contrib import admin
from django.urls import path, include
from rest_framework import routers

from dispatcher.urls import router as dispatcher_router, urlpatterns as dispatcher_urls
from djangoProject.views import home
from scheduler.urls import router as scheduler_router, urlpatterns as scheduler_urls
from pae.urls import router as pae_router, urlpatterns as pae_urls

router = routers.DefaultRouter()

router.registry.extend(dispatcher_router.registry)
router.registry.extend(scheduler_router.registry)
router.registry.extend(pae_router.registry)

admin.site.site_header = 'DjangoWeaver'
admin.site.site_title = 'DjangoWeaver'

urlpatterns = ([
    path('', home, name='home'),
    path('admin/', admin.site.urls),
    path('api/', include(router.urls)),
] + dispatcher_urls + scheduler_urls + pae_urls)
