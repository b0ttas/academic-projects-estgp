import unittest

from utils.ftp import send_files_via_ftp


class TestFTP(unittest.TestCase):
    def test_send_ftp(self):
        ftp_url = 'ftp://user:password@localhost:14148/'
        attachment_paths = ["../templates/pdf/test_output.pdf"]

        success = send_files_via_ftp(url=ftp_url, attachment_paths=attachment_paths)
        if success:
            print("Files sent successfully via FTP.")
        else:
            print("Error sending files via FTP.")
        self.assertTrue(success)


if __name__ == "__main__":
    unittest.main()
