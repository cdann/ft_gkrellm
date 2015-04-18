#ifndef OsInfoMod_H
# define OsInfoMod_H
# include "AModule.hpp"
# include "../include/OsInfoColl.hpp"
# include <string>

class OsInfoColl;

class OsInfoMod : public AModule
{
	private:
		std::string			_SysV;
		std::string			_KerV;
		std::string			_BootVol;
		OsInfoColl*			_collector;

	public:
		OsInfoMod(void);
		virtual ~OsInfoMod();
		OsInfoMod(OsInfoMod & src);
		OsInfoMod&	operator=(OsInfoMod& src);
		void		getData();
		std::string			getSysV() const;
		std::string			getKerV() const;
		std::string			getBootVol() const;
		void				setSysV(std::string info);
		void				setKerV(std::string info);
		void				setBootVol(std::string info);

		class OsInfomodexc: public std::exception
		{
			public:
				virtual const char* what() const throw();
				OsInfomodexc() throw();
				OsInfomodexc(OsInfoMod::OsInfomodexc const & src) throw();
				OsInfoMod::OsInfomodexc		&operator=(OsInfoMod::OsInfomodexc const &src);
				virtual ~OsInfomodexc() throw();
		};

};


#endif
