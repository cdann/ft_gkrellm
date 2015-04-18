#ifndef CpuMod_H
# define CpuMod_H
# include "AModule.hpp"
# include "../include/CpuColl.hpp"
# include <string>
# include <list>

class CpuColl;

class CpuMod : public AModule
{
	private:
		std::string			_model;
		std::string			_core;
		std::list<int>		_activity;
		int					_clock;
		CpuColl*			_collector;

	public:
		CpuMod(void);
		virtual ~CpuMod();
		CpuMod(CpuMod & src);
		CpuMod&	operator=(CpuMod& src);
		void		getData();
		std::string			getModel() const;
		std::string			getCore() const;
		void				setCore(std::string info);
		int					getClock() const;
		std::list<int>&		getActivity();
		void				setModel(std::string info);
		void				setClock(int info);
		void				setActivity(std::list<int>& info);

		class Cpumodexc: public std::exception
		{
			public:
				virtual const char* what() const throw();
				Cpumodexc() throw();
				Cpumodexc(CpuMod::Cpumodexc const & src) throw();
				CpuMod::Cpumodexc		&operator=(CpuMod::Cpumodexc const &src);
				virtual ~Cpumodexc() throw();
		};

};


#endif
