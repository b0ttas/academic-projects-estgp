import io
import unittest

from PyPDF2 import PdfWriter, PdfReader
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.platypus import Paragraph, SimpleDocTemplate, Spacer, Table, TableStyle


class TestPdfManipulation(unittest.TestCase):
    def test_add_text_to_pdf(self):
        # Create a sample PDF with Reportlab
        packet = io.BytesIO()
        doc = SimpleDocTemplate(packet, pagesize=A4)
        styles = getSampleStyleSheet()
        story = [Spacer(1, 297 * mm - 247 * mm), Paragraph("Hello world", styles['Title'])]

        long_text = (
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do tempor incididunt ut labore. "
            "Sed do, eiusmod tempor incididunt ut labore et dolore magna aliqua. "
            "Ut enim ad, quis nostrud exercitation ullamco laboris nisi"
        )
        story.append(Paragraph(long_text, styles['BodyText']))
        story.append(Spacer(1 * mm, 10 * mm))
        # Add a simple table
        data = [
            ['Cities', 'Countries', 'Places'],
            ['1', '2', '3']
        ]
        table = Table(data)
        table.setStyle(TableStyle([
            ('BACKGROUND', (0, 0), (-1, 0), colors.grey),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
            ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
            ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
            ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
            ('BACKGROUND', (0, 1), (-1, -1), colors.beige),
            ('GRID', (0, 0), (-1, -1), 1, colors.black),
        ]))
        story.append(table)

        doc.build(story)

        # Move to the beginning of the buffer
        packet.seek(0)

        # Read existing PDF
        existing_pdf = PdfReader(open("../templates/pdf/test_input.pdf", "rb"))
        new_pdf = PdfReader(packet)

        # Create a new PDF with the added text
        output = PdfWriter()
        page = existing_pdf.pages[0]
        page.merge_page(new_pdf.pages[0])
        output.add_page(page)

        # Write the output to a file
        with open("../templates/pdf/test_output.pdf", "wb") as output_stream:
            output.write(output_stream)


if __name__ == "__main__":
    unittest.main()
