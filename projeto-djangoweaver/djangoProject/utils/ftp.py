from ftplib import FTP
import os
from typing import Iterable
from urllib.parse import urlparse


def send_files_via_ftp(url: str, attachment_paths: Iterable) -> bool:
    try:
        # Parse the FTP URL
        parsed_url = urlparse(url)
        server_address = parsed_url.hostname
        username = parsed_url.username
        password = parsed_url.password
        destination_directory = parsed_url.path

        # Connect to the FTP server
        ftp = FTP(server_address)
        ftp.login(user=username, passwd=password)

        # Change to the desired directory on the FTP server
        ftp.cwd(destination_directory)

        # Upload files
        for filepath in attachment_paths:
            filename = os.path.basename(filepath)
            with open(filepath, 'rb') as f:
                ftp.storbinary(f'STOR {filename}', f)

        # Close the FTP connection
        ftp.quit()
        return True
    except Exception as e:
        print(f"Error sending files via FTP: {str(e)}")
        return False
