#include "../../include/TimeColl.hpp"

TimeColl::TimeColl(void): ACollector()
{

}

TimeColl::~TimeColl(void)
{

}

void				TimeColl::getData(TimeMod& mod)
{
	this->makeTime();
	mod.setDay(this->_day);
	mod.setTime(this->_time);
	static_cast<void>(mod);

}

void				TimeColl::makeTime(void)
{
	time_t rawtime;
	struct tm * timeinfo;
	char buftime [10];
	char bufday [10];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buftime,10,"%H:%M:%S",timeinfo);
	this->_time = std::string(buftime);
	strftime (bufday,10,"%m/%d/%y",timeinfo);
	this->_day = std::string(bufday);
}

TimeColl::TimeColl(TimeColl& src) :ACollector(src)
{
	*this = src;
}

TimeColl&	TimeColl::operator=(TimeColl& src)
{
	ACollector::operator=(src);
	this->_time = src._time;
	this->_day = src._day;
	return *this;
}
