from django.utils import timezone

from pae.models import PAEToken


class TokenManager:
    @staticmethod
    def store_token(token, expiration_time):
        PAEToken.objects.create(token=token, expiration_time=expiration_time)

    @staticmethod
    def get_token():
        try:
            token = PAEToken.objects.get(expiration_time__gt=timezone.now())
            return token.token
        except PAEToken.DoesNotExist:
            return None

    @staticmethod
    def delete_expired_tokens():
        PAEToken.objects.filter(expiration_time__lte=timezone.now()).delete()
