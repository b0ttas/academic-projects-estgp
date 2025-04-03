from django.contrib import admin
from django.contrib.auth.models import User
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin

from .forms import AuthenticationForm
from .models import Service
from scheduler.models import Authentication, ServiceAction

class UserAdmin(BaseUserAdmin):
    pass


class ServiceAdmin(admin.ModelAdmin):
    list_display = ('name', 'delivery', 'endpoint', 'input_data_type', 'output_type', 'cron_update_interval')


class AuthenticationAdmin(admin.ModelAdmin):
    form = AuthenticationForm
    list_display = ('service', 'authentication_type')

class ServiceActionAdmin(admin.ModelAdmin):
    list_display = ('service', 'method_name', 'description')

admin.site.unregister(User)
admin.site.register(User, UserAdmin)
admin.site.register(Authentication, AuthenticationAdmin)
admin.site.register(Service, ServiceAdmin)
admin.site.register(ServiceAction, ServiceActionAdmin)

