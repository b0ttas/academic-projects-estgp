from django.contrib import admin
from dispatcher.models import Destination


class DestinationAdmin(admin.ModelAdmin):
    list_display = ('user', 'url', 'cron_update_interval')


admin.site.register(Destination, DestinationAdmin)
