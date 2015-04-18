#include "../../include/TimeMod.hpp"
#include "../../include/TimeColl.hpp"

TimeMod::TimeMod(void): AModule(true, "Time")
{
	this->_collector = new TimeColl;
}

TimeMod::~TimeMod(void)
{
	delete this->_collector;
}

std::string					TimeMod::getDay(void) const
{
	return (this->_dayStr);
}

std::string					TimeMod::getTime(void) const
{
	return (this->_timeStr);
}

void						TimeMod::setDay(std::string day)
{
	this->_dayStr = day;
}

void						TimeMod::setTime(std::string t)
{
	this->_timeStr = t;
}

void						TimeMod::getData(void)
{
	this->_collector->getData(*this);
}

TimeMod::TimeMod(TimeMod& src): AModule(src)
{
	*this = src;
}

TimeMod&	TimeMod::operator=(TimeMod &src)
{
	static_cast<void>(src);
	return *this;
}

