#include "../include/DebugDisplay.hpp"
#include "../include/GTKDisplay.hpp"
#include <ncurses.h>

void						test_debug(void)
{
	DebugDisplay			monitor;

	monitor.printInfo();
	//monitor.displaySingleMod();
	//monitor.displaySingleMod();
	//monitor.displaySingleMod();
	monitor.addModules();


	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
	while (1)
	{
		int key = getch();
		if (key == KEY_LEFT)
			break ;
		monitor.reinitCursor();
		clear();
		monitor.displayAllMods();
		refresh();
		usleep(1000000);
	}
	//monitor.displayTime(monitor.getModList());
//	char ch = getch();
//	if(ch == KEY_F(1))		/* Without keypad enabled this will */
//		printw("F1 Key pressed");/*  not get to us either	*/
//	else
//	{	printw("The pressed key is ");
//		attron(A_BOLD);
//		printw("%c", ch);
//		attroff(A_BOLD);
//	}
//	refresh();			/* Print it on to the real screen */
//	getch();			/* Wait for user input */
//	endwin();			/* End curses mode		  */
}

void						test_gtk(void)
{
	GTKMONITOR->addModules();
	GTKMONITOR->displayAllMods();
	g_timeout_add(1000, reinterpret_cast<GSourceFunc>(time_handler), reinterpret_cast<gpointer>(GTKMONITOR->getWindow()));
	gtk_widget_show_all(GTKMONITOR->getWindow());
	gtk_main();
}

int							main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	std::string mode = av[1];
	if (mode == "debug")
		test_debug();
	else if (mode == "gtk")
	{
		gtk_init(&ac, &av);
		test_gtk();
		return (0);
	}
	//refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */
	return (0);
}
