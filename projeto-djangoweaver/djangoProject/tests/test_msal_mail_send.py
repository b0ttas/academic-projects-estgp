import json
import os
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

import msal
import requests


import unittest

from dotenv import load_dotenv

load_dotenv()
class TestHandleServiceMapping(unittest.TestCase):

    CLIENT_ID = os.getenv('CLIENT_ID')
    CLIENT_SECRET = os.getenv('CLIENT_SECRET')
    TENANT_ID = os.getenv('TENANT_ID')
    AUTHORITY = os.getenv('AUTHORITY')
    MAIL_USERNAME = os.getenv('MAIL_USERNAME')
    SCOPE = os.getenv('SCOPE').split(',')
    AUTHORITY = AUTHORITY.format(TENANT_ID=TENANT_ID)

    def test_get_access_token(self):
        app = msal.ConfidentialClientApplication(
            self.CLIENT_ID,
            authority=self.AUTHORITY,
            client_credential=self.CLIENT_SECRET,
        )

        scope = ['https://outlook.office.com/SMTP.Send/.default']

        result = app.acquire_token_for_client(scopes=scope)
        if "access_token" in result:
            return result['access_token']
        else:
            raise Exception("Failed to acquire token", result.get("error"), result.get("error_description"))

    def test_send_email_via_graph_api(self):
        access_token = self.test_get_access_token()
        subject = 'test'
        recipient = 'carvalho-luis@outlook.com'
        body = 'welolo'

        headers = {
            'Authorization': f'Bearer {access_token}',
            'Content-Type': 'application/json'
        }
        email_data = {
            "message": {
                "subject": subject,
                "body": {
                    "contentType": "Text",
                    "content": body
                },
                "from": {
                    "emailAddress": {
                        "address": self.MAIL_USERNAME
                    }
                },
                "toRecipients": [
                    {
                        "emailAddress": {
                            "address": recipient
                        }
                    }
                ]
            }
        }
        user_endpoint = f'https://graph.microsoft.com/v1.0/users/'
        #user_endpoint = f'https://graph.microsoft.com/v1.0/me/sendMail'
        response = requests.post(
            user_endpoint,
            headers=headers,
            data=json.dumps(email_data)
        )
        if response.status_code != 202:
            raise Exception(f"Error sending email: {response.status_code} - {response.text}")

    def test_via_smtplib(self):
        access_token = self.test_get_access_token()

        me_mail = 'carvalho-luis@outlook.com'

        msg = MIMEMultipart()
        msg["From"] = me_mail
        msg["To"] = os.getenv("OUTLOOK_TO")
        msg["Subject"] = "Meet for lunch?"
        msg.attach(
            MIMEText("Hey it's good to see you again. Let's meet for lunch today.", "plain")
        )

        smtp_conn = smtplib.SMTP(
            'smtp-mail.outlook.com', 587
        )
        smtp_conn.starttls()
        smtp_conn.ehlo()
        smtp_conn.docmd('AUTH', 'XOAUTH2 ' + access_token)
        smtp_conn.send_message(msg)
        print(f"Email sent")

        smtp_conn.quit()