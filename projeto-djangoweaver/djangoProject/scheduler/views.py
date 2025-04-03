import logging
import os

from django.http import HttpResponse
from rest_framework import viewsets, permissions
from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.decorators import api_view
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response

import pae.handle_pae_response
import utils.response_handlers
from runner.models import RunnerResponse
from runner.tasks import check_tasks as runner_check_tasks  # For testing
from dispatcher.tasks import check_tasks as dispatcher_check_tasks  # For testing
from .models import Service
from .serializers import ServiceSerializer

logger = logging.getLogger(__name__)

@api_view(['GET'])
def endpoint_internal(request, endpoint):
    response = HttpResponse("Accepted", status=202)

    try:
        test_periodic = os.getenv('TEST_MODE')
        if test_periodic == 'TRUE':
            runner_check_tasks()
            dispatcher_check_tasks()
            return HttpResponse("Accepted", status=202)

        service = Service.objects.get(delivery_endpoint=endpoint, delivery='REQUEST')
        if service:
            response = service.send_request()
            RunnerResponse.objects.create(service=service, raw_response=response.content, status_code=response.status_code)
        try:
            if service.authentication.authentication_handler == 'PAE':
                return pae.handle_pae_response.handle_pae_response(response, service)
            else:
                return utils.response_handlers.handle_response(response, service)
        except Exception as e:
            logger.error(f"[LOGGER - Error]: {e}")
            return HttpResponse(f"Internal Server Error", status=500)
    except Service.DoesNotExist:
        return HttpResponse("Endpoint not found", status=404)


class ServiceCustomViewSet(viewsets.ModelViewSet):
    authentication_classes = [SessionAuthentication, BasicAuthentication]
    permission_classes = [IsAuthenticated]
    http_method_names = ['get']

    queryset = Service.objects.all()
    serializer_class = ServiceSerializer

    # Your existing methods (list, retrieve, etc.) go here
    def list(self, request, **kwargs):
        # Customize this method to return your desired service names and URLs
        services = Service.objects.filter(delivery='REQUEST').order_by('name')
        service_data = {s.name: f"{os.getenv('DOMAIN')}services/{s.delivery_endpoint}/" for s in
                        services}
        return Response(service_data)


class ServiceViewSet(viewsets.ModelViewSet):
    queryset = Service.objects.all()
    serializer_class = ServiceSerializer
    permission_classes = [permissions.IsAuthenticated]
