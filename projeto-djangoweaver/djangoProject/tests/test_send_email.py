import os
import smtplib
import unittest
from email.message import EmailMessage

from dotenv import load_dotenv

load_dotenv()
class TestHandleServiceMapping(unittest.TestCase):
    def test_send_pae_email(self) -> bool:
        """
        Sends an email with attachments and given content.
        """
        email = EmailMessage()
        email['From'] = os.getenv("SENDER_EMAIL")
        email['Bcc'] = os.getenv("FALLBACK_EMAIL")
        email['Subject'] = 'Gmail Test'

        email.set_content("This is a test email.")

        try:
            with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
                server.ehlo()
                server.login(os.getenv("SENDER_EMAIL"), 'jsyw iffm cjrf thqd')
                server.send_message(email)
                server.close()
            return True
        except Exception as e:
            print(f"Error sending email: {str(e)}")
            return False