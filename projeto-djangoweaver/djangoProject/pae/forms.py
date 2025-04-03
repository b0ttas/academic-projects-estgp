# forms.py
from django import forms

class SubscriptionForm(forms.Form):
    subscription_id = forms.CharField(widget=forms.HiddenInput())
    cron_update_interval = forms.ChoiceField(
        choices=[
            ('* * * * *', 'Every minute'),
            ('*/5 * * * *', 'Every 5 minutes'),
            ('0 * * * *', 'Hourly'),
            ('0 0 * * *', 'Daily'),
            ('0 0 * * 0', 'Weekly'),
            ('0 0 1 * *', 'Monthly'),
        ],
        help_text="Choose an interval for updates."
    )
