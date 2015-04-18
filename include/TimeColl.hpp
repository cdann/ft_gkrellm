#ifndef TIMECOLL_H
# define TIMECOLL_H
# include "ACollector.hpp"
# include "TimeMod.hpp"
# include <string>

class TimeMod;

class TimeColl: public ACollector
{
	public:
		TimeColl();
		virtual ~TimeColl();
		TimeColl(TimeColl & src);
		TimeColl& 	operator=(TimeColl & src);
		void		getData(TimeMod& mod);
		void		makeTime(void);


	private:
		std::string		_time;
		std::string		_day;

};

#endif
