from django import forms
from scheduler.models import Authentication, Service


class AuthenticationForm(forms.ModelForm):
    class Meta:
        model = Authentication
        fields = '__all__'

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        if self.instance.pk is None:
            pass
            self.fields['service'].queryset = Service.objects.exclude(authentication__isnull=False)
