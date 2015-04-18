#ifndef AMONITORDISPLAY_HPP
# define AMONITORDISPLAY_HPP
# include <string>
# include <list>
# include <algorithm>
# include <iostream>
# include "IMonitorDisplay.hpp"
# include "AModule.hpp"
# include "TimeMod.hpp"
# include "UseHostMod.hpp"
# include "OsInfoMod.hpp"
# include "CpuMod.hpp"

struct Point
{
	unsigned int			row;
	unsigned int			col;
};

class AMonitorDisplay: public IMonitorDisplay
{
protected:
	std::list<AModule*>	_modList;
	std::string				_mode;

	AModule*				detect_module(const std::string& name);


public:
	AMonitorDisplay(void);
	AMonitorDisplay(const std::string& mode);
	AMonitorDisplay(const AMonitorDisplay& src);
	virtual ~AMonitorDisplay(void);
	virtual AMonitorDisplay&		operator=(const AMonitorDisplay& rhs);

	std::string				getMode(void) const;
	std::list<AModule*>&	getModList(void);
	AModule*				buildTimeMod(void);
	AModule*				buildUserHostMod(void);
	AModule*				buildOSInfo(void);
	AModule*				buildCpuMod(void);
	void					addModules(void);
	void					displayAllMods(void);
	virtual void			displaySingleMod(AModule* mod) = 0;
	virtual void			displayTime(AModule* mod) = 0;
	virtual void			displayUserHost(AModule* mod) = 0;
	virtual void			displayOsInfo(AModule* mod) = 0;
	virtual void			displayCpu(AModule* mod) = 0;
	class InvalidModFileException: public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

typedef AModule* (AMonitorDisplay::*CLONEPTR)(void);

struct stringToClone
{
	std::string		name;
	CLONEPTR		f;
};

#endif
