from django.contrib import admin
from .models import PAESentReport, PAEUserAccessToken, PAEDestination

admin.site.register(PAESentReport)
admin.site.register(PAEUserAccessToken)
admin.site.register(PAEDestination)
