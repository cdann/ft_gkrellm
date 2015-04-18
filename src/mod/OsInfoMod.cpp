#include "../../include/OsInfoMod.hpp"
#include "../../include/OsInfoColl.hpp"

OsInfoMod::OsInfoMod(void): AModule(false, "OsInfo")
{
	this->_collector = new OsInfoColl;
}

OsInfoMod::~OsInfoMod(void)
{
	delete this->_collector;
}

std::string					OsInfoMod::getSysV(void) const
{
	return (this->_SysV);
}

void						OsInfoMod::setSysV(std::string info)
{
	this->_SysV = info;
}

std::string					OsInfoMod::getKerV(void) const
{
	return (this->_KerV);
}

void						OsInfoMod::setKerV(std::string info)
{
	this->_KerV = info;
}


std::string					OsInfoMod::getBootVol(void) const
{
	return (this->_BootVol);
}

void						OsInfoMod::setBootVol(std::string info)
{
	this->_BootVol = info;
}


void						OsInfoMod::getData(void)
{
	try{
	this->_collector->getData(*this);
	} catch (OsInfoMod::OsInfomodexc e)
	{}
}

OsInfoMod::OsInfoMod(OsInfoMod& src): AModule(src)
{
	*this = src;
}

OsInfoMod&	OsInfoMod::operator=(OsInfoMod &src)
{
	AModule::operator=(src);
	this->_SysV = src._SysV;
	this->_KerV = src._KerV;
	this->_BootVol = src._BootVol;
	return *this;
}

/*
*----------------------------------------------------------------*
							Exceptions
*----------------------------------------------------------------*
*/


const char* OsInfoMod::OsInfomodexc::what() const throw()
{
	return ("Un probleme avec l'execution de la commande.");
}

OsInfoMod::OsInfomodexc::OsInfomodexc() throw() : std::exception()
{
}

OsInfoMod::OsInfomodexc::OsInfomodexc(OsInfoMod::OsInfomodexc const & src) throw()
{
	*this = src;
}

OsInfoMod::OsInfomodexc			& OsInfoMod::OsInfomodexc::operator=(OsInfoMod::OsInfomodexc const &src)  {
		std::exception::operator=(src);
		return (*this);
}

OsInfoMod::OsInfomodexc::~OsInfomodexc() throw()
{
}

