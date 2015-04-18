#include "../../include/AModule.hpp"

AModule::AModule(void)
{
	this->_refresh = false;
}

AModule::~AModule(void)
{

}

AModule::AModule(bool refresh, std::string cN) : _refresh(refresh), _className(cN)
{

}


AModule::AModule(AModule& src)
{
	*this = src;
}

AModule&	AModule::operator=(AModule& src)
{
	this->_refresh = src._refresh;
	this->_className = src._className;
	this->_collector = src._collector;
	return *this;
}

bool						AModule::getRefresh() const
{
	return (this->_refresh);
}

std::string					AModule::getClassName() const
{
	return (this->_className);
}
