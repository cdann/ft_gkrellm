#include "../../include/GTKDisplay.hpp"
/*
static void do_drawing(cairo_t *);

struct gglob{
	int count;
	double coordx[100];
	double coordy[100];
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
	gpointer user_data)
{
	do_drawing(cr);
	static_cast<void>(user_data);
	static_cast<void>(widget);
	return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.5);

	int i, j;
	for (i = 0; i <= glob.count - 1; i++ )
	{
		for (j = 0; j <= glob.count - 1; j++ ) {
			cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
			cairo_line_to(cr, glob.coordx[j], glob.coordy[j]);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		glob.coordy[i] = 20 * i;
	}
	for (int i = 0; i < 10; i++)
	{
		glob.coordx[i] = 20 * i;
	}
	for (int i = 0; i < 10 - 1; i++)
	{
		cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
		cairo_line_to(cr, glob.coordx[i+1], glob.coordy[i+1]);
	}

	glob.count = 0;
	cairo_stroke(cr);
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
	gpointer user_data)
{
	static_cast<void>(user_data);
	if (event->button == 1) {
		glob.coordx[glob.count] = event->x;
		glob.coordy[glob.count++] = event->y;
	}

	if (event->button == 3) {
		gtk_widget_queue_draw(widget);
	}

	return TRUE;
}
*/

static gboolean
on_expose_event(GtkWidget *widget,
	GdkEventExpose *event,
	gpointer data)
{
	static_cast<void>(widget);
	static_cast<void>(event);
	static_cast<void>(data);
	gtk_widget_show_all(GTKMONITOR->getWindow());
	return FALSE;
}

gboolean					time_handler(GtkWidget *widget)
{
	//strftime(buffer, 256, "%T", loctime);
	GTKMONITOR->displayAllMods();
	gtk_widget_queue_draw(widget);
	return TRUE;
}

GTKDisplay*					glob_monitor(void)
{
	static GTKDisplay		monitor;

	return (&monitor);
}

GTKDisplay::GTKDisplay(void)
{
	/*GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *mod = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	GtkWidget *title = gtk_header_bar_new();
	//GtkWidget *title2 = gtk_header_bar_new();
	GtkWidget *time = gtk_button_new_with_label("Time");
	GtkWidget *userhost = gtk_button_new_with_label("UserHost");
	GtkWidget *darea;
	glob.count = 0;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	//vbox2 = gtk_vbox_new();
	darea = gtk_drawing_area_new();

	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_box_pack_start(GTK_BOX(vbox), mod, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mod), title, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(mod), time, TRUE, TRUE, 0);

	gtk_header_bar_set_title(GTK_HEADER_BAR(title), "Part 1");;

	//gtk_widget_set_halign(time, GTK_ALIGN_START);
	//gtk_widget_set_halign(userhost, GTK_ALIGN_END);
	//gtk_container_add(GTK_CONTAINER(window), darea);

	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	g_signal_connect(G_OBJECT(darea), "draw",
		G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(window, "button-press-event",
		G_CALLBACK(clicked), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);
	gtk_window_set_title(GTK_WINDOW(window), "GtkVBox");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);*/

	this->_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(this->_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(this->_window), 1200, 1080);
	gtk_window_set_title(GTK_WINDOW(this->_window), "FT_GKRELLM");
	gtk_container_set_border_width(GTK_CONTAINER(this->_window), 5);

	this->_mainContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
	gtk_container_add(GTK_CONTAINER(this->_window), this->_mainContainer);
	this->_container1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
	this->_container2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
	this->_container3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
	gtk_container_add(GTK_CONTAINER(this->_mainContainer), this->_container1);
	gtk_container_add(GTK_CONTAINER(this->_mainContainer), this->_container2);
	gtk_container_add(GTK_CONTAINER(this->_mainContainer), this->_container3);

	g_signal_connect(this->_window, "draw",
		G_CALLBACK(on_expose_event), NULL);
	g_signal_connect(this->_window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	this->_time = 0;
	this->_userhost = 0;
}

GTKDisplay::~GTKDisplay(void)
{

}

GtkWidget*					GTKDisplay::getWindow(void) const
{
	return (this->_window);
}

void						GTKDisplay::displaySingleMod(AModule* mod)
{
	stringToGTK			table[] = {
		{"Time", &GTKDisplay::displayTime},
		{"UserHost", &GTKDisplay::displayUserHost},
		{"OsInfo", &GTKDisplay::displayOsInfo}
	};
	for (int i = 0; i < 3; i++)
	{
		std::cout << "class name = " << mod->getClassName() << std::endl;
		if (mod->getClassName() == table[i].name)
		{
			(this->*table[i].f)(mod);
			break ;
		}
	}

}

void						GTKDisplay::displayTime(AModule* mod)
{
	static GtkWidget*		label = 0;
	static GtkWidget*		day = 0;
	static GtkWidget*		time = 0;
	mod->getData();
	if (this->_time)
	{
		gtk_widget_destroy(this->_time);
		gtk_widget_destroy(label);
		gtk_widget_destroy(day);
		gtk_widget_destroy(time);
	}
	this->_time = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	gtk_container_add(GTK_CONTAINER(this->_container1), this->_time);
	TimeMod* tmp_mod = reinterpret_cast<TimeMod*>(mod);
	label = gtk_label_new("Date & Time");
	day = gtk_label_new(tmp_mod->getDay().c_str());
	time = gtk_label_new(tmp_mod->getTime().c_str());
	gtk_box_pack_start(GTK_BOX(this->_time), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_time), day, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_time), time, TRUE, TRUE, 0);
	//std::cout << "Time module data: " << tmp_mod->getDay() << " "<< tmp_mod->getTime() << std::endl;
}

void						GTKDisplay::displayUserHost(AModule* mod)
{
	static GtkWidget*		label = 0;
	static GtkWidget*		user = 0;
	static GtkWidget*		host = 0;
	mod->getData();
	if (this->_userhost)
	{
		gtk_widget_destroy(this->_userhost);
		gtk_widget_destroy(label);
		gtk_widget_destroy(user);
		gtk_widget_destroy(host);
	}
	this->_userhost = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	UserHostMod* tmp_mod = reinterpret_cast<UserHostMod*>(mod);
	label = gtk_label_new("User & Host");
	user = gtk_label_new(tmp_mod->getUser().c_str());
	host = gtk_label_new(tmp_mod->getHost().c_str());
	gtk_container_add(GTK_CONTAINER(this->_container1), this->_userhost);
	gtk_box_pack_start(GTK_BOX(this->_userhost), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_userhost), user, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_userhost), host, TRUE, TRUE, 0);
}

void						GTKDisplay::displayOsInfo(AModule* mod)
{
	static GtkWidget*		title = 0;
	static GtkWidget*		label1 = 0;
	static GtkWidget*		label2 = 0;
	static GtkWidget*		label3 = 0;
	mod->getData();
	if (this->_osInfo)
	{
		gtk_widget_destroy(this->_osInfo);
		gtk_widget_destroy(title);
		gtk_widget_destroy(label1);
		gtk_widget_destroy(label2);
		gtk_widget_destroy(label1);
	}
	this->_osInfo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	OsInfoMod* tmp_mod = reinterpret_cast<OsInfoMod*>(mod);
	title = gtk_label_new("Operating System Info");
	label1 = gtk_label_new(tmp_mod->getSysV().c_str());
	label2 = gtk_label_new(tmp_mod->getKerV().c_str());
	label3 = gtk_label_new(tmp_mod->getBootVol().c_str());
	gtk_container_add(GTK_CONTAINER(this->_container1), this->_osInfo);
	gtk_box_pack_start(GTK_BOX(this->_osInfo), title, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_osInfo), label1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_osInfo), label2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->_osInfo), label3, TRUE, TRUE, 0);
}

void						GTKDisplay::displayCpu(AModule* mod)
{
	static_cast<void>(mod);
}
