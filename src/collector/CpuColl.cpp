#include "../../include/CpuColl.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

CpuColl::CpuColl(void): ACollector()
{
//sysctl -n machdep.cpu.brand_string
}

CpuColl::~CpuColl(void)
{

}

// trim from start
inline std::string &CpuColl::ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
}

// trim from end
inline std::string &CpuColl::rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
}

// trim from both ends
inline std::string &CpuColl::trim(std::string &s) {
		return ltrim(rtrim(s));
}

std::string	CpuColl::setModel()
{
	FILE *in;
	std::string str;
	char buff[512];
	std::string line;

	if(!(in = popen("sysctl -n machdep.cpu.brand_string", "r"))){
		throw CpuMod::Cpumodexc();
	}
	while(fgets(buff, sizeof(buff), in)!=NULL){
	   str += buff;
	}
	str = trim(str);

	pclose(in);
	return(str);
}

int			CpuColl::setClock()
{
	clock_t cl = clock();
	return (int)cl;
}

void	CpuColl::setActivity(std::list<int>& lst)
{
	FILE *in;
	int ret;
	char buff[512];
	std::string line;

	if(!(in = popen("ps aux | awk {'sum+=$3;print sum'} | tail -n 1", "r"))){
		throw CpuMod::Cpumodexc();
	}
	fgets(buff, sizeof(buff), in);
	pclose(in);
	ret = atoi(buff);
	lst.pop_front();
	lst.push_back(ret);
}

std::string			CpuColl::setCore()
{
	FILE *in;
	std::string str;
	std::string ret;
	char buff[512];
	std::string part;

	if(!(in = popen("sysctl -a | grep core_count", "r"))){
		throw CpuMod::Cpumodexc();
	}
	while(fgets(buff, sizeof(buff), in)!=NULL){
	   str += buff;
	}
	std::stringstream ss(str);
	while(std::getline(ss,part,':'))
	{
		part = trim(part);
	}
	ret += "Number of Cores: " + part;

	return (ret);
}


void				CpuColl::getData(CpuMod& mod)
{
	mod.setModel(this->setModel());
	mod.setClock(this->setClock());
	this->setActivity(mod.getActivity());
	//std::cout << "$$$$$$$$$$$$["<< mod.getActivity().back() <<  "]";
	mod.setCore(this->setCore());
}


CpuColl::CpuColl(CpuColl& src) :ACollector(src)
{
	*this = src;
}

CpuColl&	CpuColl::operator=(CpuColl& src)
{
	ACollector::operator=(src);
	return *this;
}

