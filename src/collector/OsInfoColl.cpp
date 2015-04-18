#include "../../include/OsInfoColl.hpp"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

// trim from start
inline std::string &OsInfoColl::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
inline std::string &OsInfoColl::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
inline std::string &OsInfoColl::trim(std::string &s) {
        return ltrim(rtrim(s));
}


OsInfoColl::OsInfoColl(void): ACollector()
{

}

OsInfoColl::~OsInfoColl(void)
{

}

void				OsInfoColl::getData(OsInfoMod& mod)
{
	FILE *in;
	std::string str;
    char buff[512];
    std::string line;

    if(!(in = popen("system_profiler SPSoftwareDataType", "r"))){
        throw OsInfoMod::OsInfomodexc();
    }
    while(fgets(buff, sizeof(buff), in)!=NULL){
       str += buff;
    }

	std::stringstream ss(str);
	int i = 0;
    while(std::getline(ss,line,'\n'))
    {
    	line = trim(line);
    	if (i == 4)
    		mod.setSysV(line);
    	if(i == 5)
    		mod.setKerV(line);
    	if(i == 6)
    		mod.setBootVol(line);
    	i++;
    }

    pclose(in);

}

OsInfoColl::OsInfoColl(OsInfoColl& src) :ACollector(src)
{
	*this = src;
}

OsInfoColl&	OsInfoColl::operator=(OsInfoColl& src)
{
	ACollector::operator=(src);
	return *this;
}
