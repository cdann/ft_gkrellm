#ifndef GTKDISPLAY_HPP
# define GTKDISPLAY_HPP
# include "AMonitorDisplay.hpp"
# include <gtk/gtk.h>
# define GTKMONITOR (glob_monitor())

class GTKDisplay: public AMonitorDisplay
{
public:
	GTKDisplay(void);
	virtual ~GTKDisplay(void);
	GTKDisplay(const GTKDisplay& src);
	GTKDisplay&				operator=(const GTKDisplay& rhs);

	GtkWidget*				getWindow(void) const;

	virtual void			displaySingleMod(AModule* mod);
	virtual void			displayTime(AModule* mod);
	virtual void			displayUserHost(AModule* mod);
	virtual void			displayOsInfo(AModule* mod);
	virtual void			displayCpu(AModule* mod);
private:
	Point					_scnSize;
	Point					_modSize;
	Point					_cursor;
	GtkWidget*				_window;
	GtkWidget*				_mainContainer;
	GtkWidget*				_container1;
	GtkWidget*				_container2;
	GtkWidget*				_container3;
	GtkWidget*				_time;
	GtkWidget*				_userhost;
	GtkWidget*				_osInfo;
	void					fetchModSize(void);
};
gboolean					time_handler(GtkWidget *widget);
GTKDisplay*					glob_monitor(void);
typedef void (GTKDisplay::*GTKPTR)(AModule* mod);

struct stringToGTK
{
	std::string		name;
	GTKPTR			f;
};

#endif
