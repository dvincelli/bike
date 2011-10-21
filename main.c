#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>

int
main(int argc, char **argv)
{
	int tick;
	// time_t t0, t1;
	struct timeval t0, t1;
	double delta_t;
	int ticks = 0;
	char buf[80];

	initscr();
	cbreak();
	noecho();

	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	gettimeofday(&t0, NULL);
	for(;;)
	{
		if( (tick = getch()) == 'w' )
		{
			gettimeofday(&t1, NULL);
			ticks++;
			clear();
			delta_t = (t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000;
			snprintf(buf, 80, "%f ms\n", delta_t);
			addstr(buf);
			addstr(ctime(&t1.tv_sec));
			echochar('\n');
			t0 = t1;
		}
	}

	return 1;
}
