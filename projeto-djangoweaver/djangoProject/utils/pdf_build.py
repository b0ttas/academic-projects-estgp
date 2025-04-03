import io
import json

from PyPDF2 import PdfWriter, PdfReader
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer

from scheduler.models import Service
from utils.mapping_handler import handle_service_mapping
from utils.pdf_content_parser import build_auto_pdf_from_content
from utils.transform_json import transform_json


def generate_pdf(binary_data: bytes, service: Service):
    # Create PDF with Reportlab
    packet = io.BytesIO()
    doc = SimpleDocTemplate(packet, pagesize=A4)
    styles = getSampleStyleSheet()
    mapping_content = {}
    # Add a spacer to move the text down
    story = [Spacer(1, 297 * mm - 247 * mm)]

    if not binary_data.startswith(b'{') and not binary_data.endswith(b'}'):
        binary_data = b'{ "data":' + binary_data + b'}'

    if binary_data != b'':
        json_str = json.dumps(service.mapping)
        mapping = json.loads(json_str)
        mapping_content = handle_service_mapping(mapping, binary_data)

    if mapping_content.get('pdf_auto_mapping'):
        data = json.loads(binary_data)
        if service.response_mapping:
            response_mapping = json.loads(service.response_mapping)
            data = transform_json(data, response_mapping)
        story = build_auto_pdf_from_content(story, data)
    else:
        if mapping_content['pdf_title']:
            text = '\n'.join(mapping_content['pdf_title'])
            story.append(Paragraph(text, styles['Title']))
        else:
            story.append(Paragraph(service.name, styles['Title']))

        if mapping_content['pdf_text']:
            text_list = mapping_content['pdf_text']
            long_text = ('\n'.join(text_list))
        else:
            long_text = "Content determination failed."

        story.append(Paragraph(long_text, styles['BodyText']))
        story.append(Spacer(1 * mm, 10 * mm))  # Adjust the height as needed

    doc.build(story)

    # Move to the beginning of the buffer
    packet.seek(0)

    # Read PDF template
    pdf_path = service.pdf_template or "./templates/pdf/default.pdf"
    existing_pdf = PdfReader(open(pdf_path, "rb"))
    new_pdf = PdfReader(packet)

    # Create a new PDF with the added text
    output = PdfWriter()

    # Determine the number of pages in both the template and the new PDF
    num_existing_pages = len(existing_pdf.pages)
    num_new_pages = len(new_pdf.pages)

    # Iterate over all the pages in the new generated PDF
    for i in range(num_new_pages):
        # Get the corresponding template page, or if there are more new pages than template pages, just reuse the last template page
        template_page = existing_pdf.pages[min(i, num_existing_pages - 1)]
        generated_page = new_pdf.pages[i]

        # Merge the generated page onto the template
        generated_page.merge_page(template_page)

        # Add the merged page to the output
        output.add_page(generated_page)

    output_buffer = io.BytesIO()
    output.write(output_buffer)
    output_buffer.seek(0)

    return output_buffer.getvalue()
