#ifndef CpuCOLL_H
# define CpuCOLL_H
# include "ACollector.hpp"
# include "CpuMod.hpp"
# include <string>
# include <list>

class CpuMod;

class CpuColl: public ACollector
{
	public:
		CpuColl();
		virtual ~CpuColl();
		CpuColl(CpuColl & src);
		CpuColl& 	operator=(CpuColl & src);
		void		getData(CpuMod& mod);
		inline std::string &ltrim(std::string &s);
		inline std::string &rtrim(std::string &s);
		inline std::string &trim(std::string &s);
		std::string			setModel();
		void				setActivity(std::list<int>& lst);
		int					setClock();
		std::string			setCore();


};

#endif
