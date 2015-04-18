#ifndef AMOD_H
# define AMOD_H
# include "IMonitorModule.hpp"
# include "ACollector.hpp"
# include <string>
# include <fstream>

class ACollector;

class AModule
{
	protected:
		bool				_refresh;
		std::string			_className;
		ACollector*			_collector;

	public:
		AModule(void);
		AModule(bool refresh, std::string cN);
		virtual ~AModule(void);
		AModule(AModule & src);
		AModule& 			operator=(AModule & src);
		bool				getRefresh() const;
		std::string			getClassName() const;
		virtual void		getData() = 0;
};

#endif
