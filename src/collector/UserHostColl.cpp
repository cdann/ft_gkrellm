#include "../../include/UseHostColl.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

UserHostColl::UserHostColl(void): ACollector()
{

}

UserHostColl::~UserHostColl(void)
{

}

void				UserHostColl::getData(UserHostMod& mod)
{
	struct passwd *psuid;
	char hostname[1024];

	psuid = getpwuid(getuid());

	mod.setUser(psuid->pw_name);
	gethostname(hostname, 1023);
	mod.setHost(hostname);

}

UserHostColl::UserHostColl(UserHostColl& src) :ACollector(src)
{
	*this = src;
}

UserHostColl&	UserHostColl::operator=(UserHostColl& src)
{
	ACollector::operator=(src);
	return *this;
}
