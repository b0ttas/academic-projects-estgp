import io
import textwrap
import unittest

from PyPDF2 import PdfWriter, PdfReader
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import mm
from reportlab.pdfgen import canvas


class TestPdfManipulation(unittest.TestCase):
    def test_add_text_to_pdf(self):
        # Create a sample PDF with Reportlab
        packet = io.BytesIO()
        can = canvas.Canvas(packet, pagesize=A4)  # A4 = (210*mm,297*mm)
        can.drawCentredString(A4[0] / 2, 200 * mm, "Hello world")
        long_text = (
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do tempor incididunt ut labore. "
            "Sed do, eiusmod tempor incididunt ut labore et dolore magna aliqua. "
            "Ut enim ad, quis nostrud exercitation ullamco laboris nisi"
        )
        wrapped_text = textwrap.fill(long_text, width=90)
        can.setFont("Helvetica", 12)  # Set font and size
        can.setFillColorRGB(0, 0, 0)  # Set text color (black)
        can.drawCentredString(A4[0] / 2, 190 * mm, wrapped_text)  # Adjust Y position as needed
        can.save()

        # Move to the beginning of the buffer
        packet.seek(0)

        # Read existing PDF
        existing_pdf = PdfReader(open("../templates/pdf/default.pdf", "rb"))
        new_pdf = PdfReader(packet)

        # Create a new PDF with the added text
        output = PdfWriter()
        page = existing_pdf.pages[0]
        page.merge_page(new_pdf.pages[0])
        output.add_page(page)

        # Write the output to a file
        with open("../templates/pdf/test_output.pdf", "wb") as output_stream:
            output.write(output_stream)

        # Verify that the new PDF contains the expected text
        with open("../templates/pdf/test_output.pdf", "rb") as temp_file:
            temp_pdf = PdfReader(temp_file)
            text_found = False
            for page in temp_pdf.pages:
                if "Hello world" in page.extract_text():
                    text_found = True
                    break
            self.assertTrue(text_found, "Text 'Hello world' not found in the PDF")


if __name__ == "__main__":
    unittest.main()
