#ifndef ACOLLECTOR_H
# define ACOLLECTOR_H
# include "AModule.hpp"

class AModule;

class ACollector
{
	public:
		ACollector(void);
		virtual ~ACollector(void);
		ACollector(ACollector & src);
		ACollector& 	operator=(ACollector & src);
		void	getData(AModule& mod);
};

#endif
