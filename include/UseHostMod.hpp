#ifndef UserHostMod_H
# define UserHostMod_H
# include "AModule.hpp"
# include "../include/UseHostColl.hpp"
# include <string>

class UserHostColl;

class UserHostMod : public AModule
{
	private:
		std::string			_HostName;
		std::string			_UserName;
		UserHostColl*		_collector;

	public:
		UserHostMod(void);
		virtual ~UserHostMod();
		UserHostMod(UserHostMod & src);
		UserHostMod&	operator=(UserHostMod& src);
		void		getData();
		std::string			getHost() const;
		std::string			getUser() const;
		void				setHost(std::string day);
		void				setUser(std::string time);

};


#endif
