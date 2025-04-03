from django.test import TestCase
from croniter import croniter
from datetime import datetime


class CronTest(TestCase):
    def test_last_day_of_month(self):
        base = datetime(2024, 9, 7)  # Use a fixed date for testing
        cron_expression = '0 0 L * *'
        iterable = croniter(cron_expression, base)

        next_date = iterable.get_next(datetime)
        expected_date = datetime(2024, 9, 30, 0, 0)  # Expected last day of the month

        self.assertEqual(next_date, expected_date)

    def test_first_day_of_month(self):
        base = datetime(2024, 9, 7)  # Use a fixed date for testing
        cron_expression = '0 0 1 * *'
        iterable = croniter(cron_expression, base)

        next_date = iterable.get_next(datetime)
        expected_date = datetime(2024, 10, 1, 0, 0)  # Expected first day of the next month

        self.assertEqual(next_date, expected_date)

    def test_next_update_date_time(self):
        last_update = datetime(2024, 9, 1, 0, 0)  # Example last update time
        cron_expression = '0 0 * * *'  # Example cron expression for daily updates
        current_time = datetime(2024, 9, 7, 18, 22)  # Current time for testing

        iterable = croniter(cron_expression, last_update)
        next_update = iterable.get_next(datetime)

        # Check if the current time is past the next scheduled update time
        should_update = current_time >= next_update

        self.assertTrue(should_update)
