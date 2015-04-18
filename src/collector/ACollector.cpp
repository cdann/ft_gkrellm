#include "../../include/ACollector.hpp"
#include "../../include/AModule.hpp"

ACollector::ACollector(void)
{

}

ACollector::~ACollector(void)
{

}

ACollector::ACollector(ACollector& src)
{
	*this = src;
}

ACollector&	ACollector::operator=(ACollector& src)
{
	static_cast<void>(src);
	return *this;
}

void	ACollector::getData(AModule& mod)
{
	static_cast<void>(mod);

}

