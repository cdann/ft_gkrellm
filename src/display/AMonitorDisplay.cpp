#include "../../include/AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay(void)
{

}

AMonitorDisplay::AMonitorDisplay(const std::string& mode):
	_mode(mode)
{

}

static void					clear(AModule* mod)
{
	delete mod;
}

AMonitorDisplay::~AMonitorDisplay(void)
{
	for_each(this->_modList.begin(), this->_modList.end(), &clear);
}

AMonitorDisplay::AMonitorDisplay(const AMonitorDisplay& src)
{
	*this = src;
}

AMonitorDisplay&			AMonitorDisplay::operator=(const AMonitorDisplay& rhs)
{
	this->_modList = rhs._modList;
	return (*this);
}

AModule*					AMonitorDisplay::detect_module(const std::string& name)
{
	stringToClone		table[] = {
		{"time", &AMonitorDisplay::buildTimeMod},
		{"userhost", &AMonitorDisplay::buildUserHostMod},
		{"osinfo", &AMonitorDisplay::buildOSInfo},
		{"cpu", &AMonitorDisplay::buildCpuMod}
	};

	for (int i = 0; i < 4; i++)
	{
		if (name == table[i].name)
		{
			return ((this->*table[i].f)());
		}
	}
	throw AMonitorDisplay::InvalidModFileException();
	return (0);
}

std::string					AMonitorDisplay::getMode(void) const
{
	return (this->_mode);
}

std::list<AModule*>&		AMonitorDisplay::getModList(void)
{
	return (this->_modList);
}

AModule*					AMonitorDisplay::buildTimeMod(void)
{
	return (new TimeMod());
}

AModule*					AMonitorDisplay::buildUserHostMod(void)
{
	return (new UserHostMod());
}

AModule*					AMonitorDisplay::buildOSInfo(void)
{
	return (new OsInfoMod());
}

AModule*					AMonitorDisplay::buildCpuMod(void)
{
	return (new CpuMod());
}

void						AMonitorDisplay::addModules(void)
{
	std::ifstream			o;
	std::string				discard;
	std::string				name;
	int						flag;

	o.open("active_modules.conf");
	if (!o.is_open())
		return ; // CALL EXCEPTION HERE
	o >> discard; // Comment line in conf is thrown away.
	while (o >> name >> flag)
	{
		if (flag)
			this->_modList.push_back(this->detect_module(name));
	}
	o.close();
}

const char*					AMonitorDisplay::InvalidModFileException::what() const throw()
{
	return ("Invalid configuration file.");
}

void						AMonitorDisplay::displayAllMods(void)
{
	std::list<AModule*>::iterator it, ite = this->_modList.end();
	for (it = this->_modList.begin(); it != ite; it++)
	{
		this->displaySingleMod(*it);
	}
}
