#ifndef UserHostColl_H
# define UserHostColl_H
# include "ACollector.hpp"
# include "../include/UseHostMod.hpp"
# include <string>

class UserHostMod;

class UserHostColl: public ACollector
{
	public:
		UserHostColl();
		virtual ~UserHostColl();
		UserHostColl(UserHostColl & src);
		UserHostColl& 	operator=(UserHostColl & src);
		void		getData(UserHostMod& mod);

};

#endif
