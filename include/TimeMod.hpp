#ifndef TIMEMOD_H
# define TIMEMOD_H
# include "AModule.hpp"
# include "TimeColl.hpp"
# include <string>

class TimeColl;

class TimeMod : public AModule
{
	private:
		std::string	_dayStr;
		std::string	_timeStr;
		TimeColl*			_collector;

	public:
		TimeMod(void);
		virtual ~TimeMod();
		TimeMod(TimeMod & src);
		TimeMod&	operator=(TimeMod& src);
		void		getData();
		std::string			getDay() const;
		std::string			getTime() const;
		void				setDay(std::string day);
		void				setTime(std::string time);

};


#endif
