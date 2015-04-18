#include "../../include/UseHostMod.hpp"
#include "../../include/UseHostColl.hpp"

UserHostMod::UserHostMod(void): AModule(false, "UserHost")
{
	this->_collector = new UserHostColl;
}

UserHostMod::~UserHostMod(void)
{
	delete this->_collector;
}

std::string					UserHostMod::getUser(void) const
{
	return (this->_UserName);
}

std::string					UserHostMod::getHost(void) const
{
	return (this->_HostName);
}

void						UserHostMod::setUser(std::string user)
{
	this->_UserName = user;
}

void						UserHostMod::setHost(std::string h)
{
	this->_HostName = h;
}

void						UserHostMod::getData(void)
{
	this->_collector->getData(*this);
}

UserHostMod::UserHostMod(UserHostMod& src): AModule(src)
{
	*this = src;
}

UserHostMod&	UserHostMod::operator=(UserHostMod &src)
{
	AModule::operator=(src);
	this->_UserName = src._UserName;
	this->_HostName = src._HostName;
	return *this;
}

