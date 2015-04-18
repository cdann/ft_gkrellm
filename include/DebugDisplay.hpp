#ifndef DEBUGDISPLAY_HPP
# define DEBUGDISPLAY_HPP
# include "AMonitorDisplay.hpp"
# include "sys/ioctl.h"
# include <fstream>
# include <iostream>
#include <ncurses.h>

class DebugDisplay: public AMonitorDisplay
{
public:
	DebugDisplay(void);
	DebugDisplay(const DebugDisplay& src);
	virtual ~DebugDisplay(void);
	DebugDisplay&			operator=(const DebugDisplay& rhs);

	unsigned int			getScnX(void) const;
	unsigned int			getScnY(void) const;
	void					getScreenSize(void);
	virtual void			displaySingleMod(AModule* mod);

	virtual void			displayTime(AModule* mod);
	virtual void			displayUserHost(AModule* mod);
	virtual void			displayOsInfo(AModule* mod);
	virtual void			displayCpu(AModule* mod);
	void					reinitCursor(void);
	void					printInfo(void);
	class NoSpaceLeftException: public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
private:
	Point					_scnSize;
	Point					_modSize;
	Point					_cursor;

	void					fetchModSize(void);
	void					setNextModCursor(void);
};

typedef void (DebugDisplay::*DISPPTR)(AModule* mod);

struct stringToDisplay
{
	std::string		name;
	DISPPTR			f;
};

#endif
