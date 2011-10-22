#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>

#include <math.h>

#define DIAMETER 0.700

int
main(int argc, char **argv)
{
	int tick;
	struct timeval t0, t1, tstart;
	double delta_t;
	int ticks = 0;
	char buf[80];
	double moving_avg = 0.0;
	double elapsed = 0.0;

	initscr();
	cbreak();
	noecho();

	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	if( (tick = getch()) == 'w' ) {
		gettimeofday(&t0, NULL);
		gettimeofday(&tstart, NULL);
	} else if (tick == 'q') {
		goto end;
	}

	for(;;)
	{
		if( (tick = getch()) == 'w' )
		{
			clear();

			gettimeofday(&t1, NULL);
			ticks++;

			delta_t = (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_usec - t0.tv_usec) / 1000.0;
			snprintf(buf, 80, "Revolution time: %.2f ms\n", delta_t);
			addstr(buf);

			moving_avg = moving_avg + ((delta_t - moving_avg) / (double) ticks);
			snprintf(buf, 80, "Moving average: %.2f ms\n", moving_avg);
			addstr(buf);


			snprintf(buf, 80, "Travelled: %.2f m\n", ticks * DIAMETER * M_PI);
			addstr(buf);

			snprintf(buf, 80, "Start Time: %s", ctime(&tstart.tv_sec));
			addstr(buf);

			snprintf(buf, 80, "Current Time: %s", ctime(&t1.tv_sec));
			addstr(buf);

			elapsed = (t1.tv_sec - tstart.tv_sec) / 60.0;
			snprintf(buf, 80, "Elapsed Time: %.2f minutes\n", elapsed);
			addstr(buf);

			t0 = t1;
		} else if ( tick == 'q' ) {
			break;
		}
	}

end:

	endwin();
	return 0;
}
