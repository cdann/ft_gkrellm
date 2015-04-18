#ifndef OsInfoCOLL_H
# define OsInfoCOLL_H
# include "ACollector.hpp"
# include "OsInfoMod.hpp"
# include <string>
#include <algorithm>
#include <sstream>

class OsInfoMod;

class OsInfoColl: public ACollector
{
	public:
		OsInfoColl();
		virtual ~OsInfoColl();
		OsInfoColl(OsInfoColl & src);
		OsInfoColl& 	operator=(OsInfoColl & src);
		void		getData(OsInfoMod& mod);
		inline std::string &ltrim(std::string &s);
		inline std::string &rtrim(std::string &s);
		inline std::string &trim(std::string &s);


};

#endif
