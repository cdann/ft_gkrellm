#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP
# include <string>
# include "AModule.hpp"

class AModule;

class IMonitorDisplay
{
public:
	virtual ~IMonitorDisplay(void) {};
	//virtual IMonitorDisplay() = 0;
	//virtual IMonitorDisplay(IMonitorDisplay& src) = 0;
	//virtual IMonitorDisplay& operator=(const IMonitorDisplay& src) = 0;

	virtual void			displayAllMods(void) = 0;
	virtual void			displaySingleMod(AModule* mod) = 0;
};

#endif
