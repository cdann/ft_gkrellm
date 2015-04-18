#ifndef AMOD_H
# define AMOD_H
# include <string>

class IMonitorModule
{
	public:
		virtual ~IMonitorModule(void) {} = 0;
		//virtual IMonitorModule() = 0;
		//virtual IMonitorModule(IMonitorModule& src) = 0;
		//virtual IMonitorModule&	operator=(const IMonitorModule & src) = 0;
		virtual bool		getRefresh() = 0;
		virtual std::string	getTitle() = 0;
		virtual void		getData() = 0;

};

#endif
