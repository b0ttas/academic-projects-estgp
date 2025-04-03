import io

from PyPDF2 import PdfWriter, PdfReader
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import mm
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table
from reportlab.platypus.tables import TableStyle

from scheduler.models import Service


def generate_pae_story(report_data:dict) -> list:
    story = [Spacer(1, 297 * mm - 247 * mm)]
    styles = getSampleStyleSheet()

    # Custom styles
    title_style = styles['Title']
    normal_style = styles['Normal']
    bold_style = ParagraphStyle(
        'BoldStyle',
        parent=normal_style,
        fontName='Helvetica-Bold',  # Specify a bold font
        fontSize=12,
        spaceAfter=12,
    )

    description_style = ParagraphStyle('description', fontSize=10, spaceAfter=10, leading=12)

    report_title = report_data['reportTitle']
    report_description = report_data['reportDescription']
    # persons_to_notify = ", ".join([p['name'] for p in report_data['personstoNotify']])
    items = report_data['items']

    report_item_title_singular = report_data['reportItemPluralTitleSingular']
    report_item_title_plural = report_data['reportItemPluralTitlePlural']

    # Add title and description to the story
    story.append(Paragraph(report_title, title_style))
    story.append(Spacer(1, 12))
    story.append(Paragraph(report_description, description_style))
    story.append(Spacer(1, 12))

    story.append(Paragraph(report_item_title_plural, bold_style))
    story.append(Spacer(1, 12))

    for item in items:
        item_code = item['code']
        item_email = item['email']
        item_label = item['label']
        factual_fields = item['factualFieldList']

        story.append(Paragraph(report_item_title_singular + ' ' + item_code, normal_style))
        if item_email: story.append(Paragraph(f'Email: ' + item_email, normal_style))
        if item_label: story.append(Paragraph(f'Label: ' + item_label, normal_style))
        story.append(Spacer(1, 12))
        # Prepare table header
        table_data = [[Paragraph('Field Label', styles['Heading4']), Paragraph('Value', styles['Heading4'])]]

        # Populate table with labels and values
        for field in factual_fields:
            label = field['fieldLabel']
            value = field['fieldStringValue']
            table_data.append([label, value])

        # Create a table with the field labels and their values
        table = Table(table_data, hAlign='LEFT', splitByRow=True)
        table.setStyle(TableStyle([
            ('BACKGROUND', (0, 0), (-1, 0), colors.darkorange),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.black),
            ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
            ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
            ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
            ('BACKGROUND', (0, 1), (-1, -1), colors.peachpuff),
            ('GRID', (0, 0), (-1, -1), 1, colors.darkorange)
        ]))

        # Add table to the story
        story.append(table)
        story.append(Spacer(1, 24))

    return story


def generate_pae_pdf(json_input:dict, service: Service):
    packet = io.BytesIO()
    doc = SimpleDocTemplate(packet, pagesize=A4)

    story = generate_pae_story(json_input)

    doc.build(story)
    packet.seek(0) # Move to the beginning of the buffer

    # Read PDF template
    pdf_path = service.pdf_template.path or "./templates/pdf/default_pae.pdf"
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

        generated_page.merge_page(template_page) # Merge the generated page onto the template
        output.add_page(generated_page) # Add the merged page to the output

    output_buffer = io.BytesIO()
    output.write(output_buffer)
    output_buffer.seek(0)

    return output_buffer.getvalue()