import json

from django.http import HttpResponse
from django.utils import timezone
from scheduler.models import Service
from utils.pdf_build import generate_pdf
from utils.response_conversions import json2xml, csv2json, xml2json, json2html
from utils.smtp import send_email, collect_delivery_addresses


def handle_response(response: HttpResponse, service: Service):
    input_type = service.input_data_type
    output_type = service.output_type

    if input_type == output_type:
        return response
    # try:
    if input_type == 'JSON':
        return handle_json_response(response, output_type, service)

    elif input_type == 'XML':
        return handle_xml_response(response, output_type, service)

    elif input_type == 'CSV':
        return handle_csv_response(response, output_type, service)

    elif input_type == 'TEXT':
        return handle_text_response(response, output_type, service)
    # except Exception:
    #     return HttpResponse(status=500, content='There was an issue handling your request.',
    #     content_type='text/plain')


def handle_json_response(response: HttpResponse, output_type: str, service: Service):
    if output_type == 'XML':
        xml_data = json2xml(response.content)
        return HttpResponse(xml_data, content_type='application/xml')
    elif output_type == 'HTML':
        html = json2html(response.content)
        return html
    elif output_type == 'EMAIL':
        if service.delivery == 'REQUEST':
            delivery_urls, delivery_emails = collect_delivery_addresses(service)
            success = send_email(service=service, attachment_paths='', file_binary_data=response.content,
                                 recipients=delivery_emails)
            if success:
                return HttpResponse("OK", code=200)
            else:
                return HttpResponse(code=500)
        else:
            return response
    elif output_type == 'PDF':
        timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
        pdf_content = generate_pdf(response.content, service)
        response = HttpResponse(content_type="application/pdf")
        response["Content-Disposition"] = f'attachment; filename="{timestamp}_{service.name}.pdf"'
        response.write(pdf_content)
        return response

    elif output_type == 'EMAIL_ATTACHMENT':
        if service.delivery == 'REQUEST':
            pdf_content = generate_pdf(response.content, service)
            return create_pdf_and_send(service, pdf_content)
        else:
            return response


def handle_xml_response(response: HttpResponse, output_type: str, service: Service):
    if output_type == 'JSON':
        data = xml2json(response.content)
        return HttpResponse(data, content_type='application/json')
    elif output_type == 'HTML':
        data = xml2json(response.content)
        html = json2html(data)
        return html
    elif output_type == 'EMAIL':
        if service.delivery == 'REQUEST':
            data = xml2json(response.content)
            delivery_urls, delivery_emails = collect_delivery_addresses(service)
            success = send_email(service=service, attachment_paths='', file_binary_data=data,
                                 recipients=delivery_emails)
            if success:
                return HttpResponse("OK", code=200)
            else:
                return HttpResponse(code=500)
        else:
            return response

    elif output_type == 'PDF':
        timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
        json_data = xml2json(response.content)
        pdf_content = generate_pdf(json_data, service)
        response = HttpResponse(content_type="application/pdf")
        response["Content-Disposition"] = f'attachment; filename="{timestamp}_{service.name}.pdf"'
        response.write(pdf_content)
        return response

    elif output_type == 'EMAIL_ATTACHMENT':
        if service.delivery == 'REQUEST':
            json_data = xml2json(response.content)
            pdf_content = generate_pdf(json_data, service)
            return create_pdf_and_send(service, pdf_content)
        else:
            return response


def handle_csv_response(response: HttpResponse, output_type: str, service: Service):
    if output_type == 'JSON':
        data = {'text': response.content}
        return HttpResponse(json.dumps(data), content_type='application/json')
    elif output_type == 'XML':
        data = csv2json(response.content)
        xml_data = json2xml(data)
        return HttpResponse(xml_data, content_type='application/xml')
    elif output_type == 'EMAIL':
        if service.delivery == 'REQUEST':
            delivery_urls, delivery_emails = collect_delivery_addresses(service)
            success = send_email(service=service, attachment_paths='', file_binary_data=response.content,
                                 recipients=delivery_emails)
            if success:
                return HttpResponse("OK", code=200)
            else:
                return HttpResponse(code=500)
        else:
            return response
    elif output_type == 'PDF':
        timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
        pdf_content = generate_pdf(response.content, service)
        response = HttpResponse(content_type="application/pdf")
        response["Content-Disposition"] = f'attachment; filename="{timestamp}_{service.name}.pdf"'
        response.write(pdf_content)
        return response
    elif output_type == 'EMAIL_ATTACHMENT':
        if service.delivery == 'REQUEST':
            pdf_content = generate_pdf(response.content, service)
            return create_pdf_and_send(service, pdf_content)
        else:
            return response


def handle_text_response(response: HttpResponse, output_type: str, service: Service):
    if output_type == 'JSON':
        data = {'text': response.content}
        return HttpResponse(json.dumps(data), content_type='application/json')
    elif output_type == 'XML':
        data = {'text': response.content}
        xml_data = json2xml(data)
        return HttpResponse(xml_data, content_type='application/xml')
    elif output_type == 'EMAIL':
        if service.delivery == 'REQUEST':
            delivery_urls, delivery_emails = collect_delivery_addresses(service)
            success = send_email(service=service, attachment_paths='', file_binary_data=response.content,
                                 recipients=delivery_emails)
            if success:
                return HttpResponse("OK", code=200)
            else:
                return HttpResponse(code=500)
        else:
            return response
    elif output_type == 'PDF':
        timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
        pdf_content = generate_pdf(response.content, service)
        response = HttpResponse(content_type="application/pdf")
        response["Content-Disposition"] = f'attachment; filename="{timestamp}_{service.name}.pdf"'
        response.write(pdf_content)
        return response
    elif output_type == 'EMAIL_ATTACHMENT':
        if service.delivery == 'REQUEST':
            pdf_content = generate_pdf(response.content, service)
            return create_pdf_and_send(service, pdf_content)
        else:
            return response


def create_pdf_and_send(service: Service, pdf_content: bytes):
    timestamp = timezone.now().strftime("%Y%m%d-%H%M%S")
    pdf_path = f"./data/attachments/{service.name}/{timestamp}_{service.name}" + ".pdf"
    delivery_urls, delivery_emails = collect_delivery_addresses(service)

    with open(pdf_path, 'wb') as output_stream:
        output_stream.write(pdf_content)

    if delivery_emails:
        success:bool = send_email(service=service, attachment_paths=pdf_path, file_binary_data=b'',
                             recipients=delivery_emails)
    else:
        success = True

    if success:
        return HttpResponse("OK", status=200)
    else:
        return HttpResponse(status=500)
