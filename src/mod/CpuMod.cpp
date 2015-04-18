#include "../../include/CpuMod.hpp"
#include "../../include/CpuColl.hpp"
#include <iostream>

CpuMod::CpuMod(void): AModule(false, "Cpu")
{
	this->_activity = std::list<int>(100);
	this->_collector = new CpuColl;
}

CpuMod::~CpuMod(void)
{
	delete this->_collector;
}

std::string					CpuMod::getModel(void) const
{
	return (this->_model);
}

void						CpuMod::setModel(std::string info)
{
	this->_model = info;
}


std::string					CpuMod::getCore(void) const
{
	return (this->_core);
}

void						CpuMod::setCore(std::string info)
{
	this->_core = info;
}

int							CpuMod::getClock(void) const
{
	return (this->_clock);
}

void						CpuMod::setClock(int info)
{
	this->_clock = info;
}


std::list<int>&						CpuMod::getActivity(void)
{
	return (this->_activity);
}

void						CpuMod::setActivity(std::list<int>&	 info)
{
	this->_activity = info;
}


void						CpuMod::getData(void)
{
	try {
		this->_collector->getData(*this);
	}
	catch( CpuMod::Cpumodexc e)
	{}
}

CpuMod::CpuMod(CpuMod& src): AModule(src)
{
	*this = src;
}

CpuMod&	CpuMod::operator=(CpuMod &src)
{
	AModule::operator=(src);
	this->_activity = src._activity;
	this->_clock = src._clock;
	this->_model = src._model;
	return *this;
}




/*
*----------------------------------------------------------------*
							Exceptions
*----------------------------------------------------------------*
*/


const char* CpuMod::Cpumodexc::what() const throw()
{
	return ("Un probleme avec l'execution de la commande.");
}

CpuMod::Cpumodexc::Cpumodexc() throw() : std::exception()
{
}

CpuMod::Cpumodexc::Cpumodexc(CpuMod::Cpumodexc const & src) throw()
{
	*this = src;
}

CpuMod::Cpumodexc			& CpuMod::Cpumodexc::operator=(CpuMod::Cpumodexc const &src)  {
		std::exception::operator=(src);
		return (*this);
}

CpuMod::Cpumodexc::~Cpumodexc() throw()
{
}


