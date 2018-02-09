package edu.estgp.sdis;

import java.util.Calendar;
import java.util.concurrent.PriorityBlockingQueue;

/**
 * Checks queue of events yet to start
 */
public class CalendarServerNotificator implements Runnable {

	private final CalendarServerImpl _server;
	private static final int SLEEP = 200;
	private long _lastRun;

	public CalendarServerNotificator(CalendarServerImpl server) {
		_server = server;
		_lastRun = currentTime();
	}

	/**
	 * Checks for events
	 */
	public void run() {

		while (_server.running()) {

			PriorityBlockingQueue<Event> events = _server.getUpcomingEvents();

			// Remove all events before last run
			Event event = events.peek();
			boolean found = false;
			while (event != null && !found) {
				if (_lastRun > event.getBegin().getTime()) {
					events.poll();
					event = events.peek();
				} else {
					found = true;
				}
			}

			// Notifies server if events happen in current iteration
			boolean finished = false;
			while(event != null && !finished) {
				// Check, whether notify now or later
				long abs = event.getBegin().getTime() - _lastRun;
				if (abs < SLEEP) {
					// Notify
					events.poll();
					_server.notify(event);
					event = events.peek();
				}
				else {
					finished = true;
				}
			}

			_lastRun = currentTime();

			try {
				Thread.sleep(SLEEP);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

	}

	/**
	 * Returns current time in milliseconds
	 */
	public long currentTime() {
		Calendar calendar = Calendar.getInstance();
		return calendar.getTime().getTime();
	}
}