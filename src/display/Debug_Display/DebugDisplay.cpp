#include "../../../include/DebugDisplay.hpp"

DebugDisplay::DebugDisplay(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	this->_scnSize.col = w.ws_col;
	this->_scnSize.row = w.ws_row;
	this->_cursor.col = 0;
	this->_cursor.row = 0;
	this->fetchModSize();
}

DebugDisplay::DebugDisplay(const DebugDisplay& src): AMonitorDisplay()
{
	this->_scnSize = src._scnSize;
	this->_modSize = src._modSize;
	this->_cursor = src._cursor;
}

DebugDisplay::~DebugDisplay(void)
{

}

DebugDisplay&				DebugDisplay::operator=(const DebugDisplay& rhs)
{
	*this = rhs;
	return (*this);
}



void						DebugDisplay::displaySingleMod(AModule* mod)
{
	stringToDisplay			table[] = {
		{"Time", &DebugDisplay::displayTime},
		{"UserHost", &DebugDisplay::displayUserHost},
		{"OsInfo", &DebugDisplay::displayOsInfo},
		{"Cpu", &DebugDisplay::displayCpu}
	};

	try
	{
		for (int i = 0; i < 4; i++)
		{
			if (mod->getClassName() == table[i].name)
			{
				(this->*table[i].f)(mod);
				break ;
			}
		}
		this->setNextModCursor();
	}
	catch (DebugDisplay::NoSpaceLeftException& e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
}

void						DebugDisplay::printInfo()
{
	std::cout << "SCREEN " << this->_scnSize.row << "/" << this->_scnSize.col << std::endl;
	std::cout << "MODULE " << this->_modSize.row << "/" << this->_modSize.col << std::endl;
}

const char*					DebugDisplay::NoSpaceLeftException::what() const throw()
{
	return ("Cannot display next module, no more room on screen.");
}

void						DebugDisplay::fetchModSize(void)
{
	std::ifstream			o;
	std::string				discard;

	o.open("debugdisplay.conf");
	if (!o.is_open())
		return ; // CALL EXCEPTION HERE
	o >> discard >> this->_modSize.row >> discard >> this->_modSize.col;
	o.close();
}

void						DebugDisplay::setNextModCursor(void)
{
	if (this->_cursor.col + this->_modSize.col + this->_modSize.col + 3 < this->_scnSize.col)
	{
		this->_cursor.col += this->_modSize.col;
		return ;
	}
	else
	{
		this->_cursor.col = 0;
		this->_cursor.row += this->_modSize.row;
	}
	if (this->_cursor.row >= this->_scnSize.row)
		throw DebugDisplay::NoSpaceLeftException();
}

static void					print_top(unsigned int mod_col)
{
	addch('/');
	for (unsigned int j = 1; j <= mod_col - 1; j++)
		addch('-');
	addch('\\');
}

static void					print_btm(unsigned int mod_col)
{
	addch('\\');
	for (unsigned int j = 1; j <= mod_col - 1; j++)
		addch('-');
	addch('/');
}

static void					print_hbar(unsigned int mod_col)
{
	addch('|');
	for (unsigned int j = 1; j <= mod_col - 1; j++)
		addch('-');
	addch('|');
}

void						print_mid(unsigned int row, unsigned int col)
{
	addch('|');
	move(row, col);
	addch('|');
}


void						DebugDisplay::displayTime(AModule* mod)
{
	TimeMod* tmp_mod = reinterpret_cast<TimeMod*>(mod);
	mod->getData();
	Point					cursor_tmp;
	cursor_tmp.col = this->_cursor.col;
	cursor_tmp.row = this->_cursor.row;
	unsigned int			mod_col = this->_modSize.col - 1;
	unsigned int			mod_row = this->_modSize.row - 1;
	std::string				word1 = "Date";
	std::string				word2 = "Time";

	for (unsigned int i = 0; i <= mod_row; i++)
	{
		move(cursor_tmp.row, cursor_tmp.col);
		if (i == 0)
			print_top(mod_col);
		else if (i == 1)
		{
			addch('|');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2);
			addch('&');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 - 5);
			printw("%s", word1.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 + 2);
			printw("%s", word2.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == 2)
			print_hbar(mod_col);
		else if (i == mod_row)
			print_btm(mod_col);
		else
			print_mid(cursor_tmp.row, cursor_tmp.col + mod_col);
		cursor_tmp.row++;
	}
	move((this->_cursor.row + mod_row + 3) / 2 - 1, (this->_cursor.col + mod_col) / 2 - 4);
	printw("%s", tmp_mod->getDay().c_str());
	move((this->_cursor.row + mod_row + 3) / 2 + 1, (this->_cursor.col + mod_col) / 2 - 4);
	printw("%s", tmp_mod->getTime().c_str());
}

void						DebugDisplay::displayUserHost(AModule* mod)
{
	UserHostMod* tmp_mod = reinterpret_cast<UserHostMod*>(mod);
	mod->getData();
	Point					cursor_tmp;
	cursor_tmp.col = this->_cursor.col;
	cursor_tmp.row = this->_cursor.row;
	unsigned int			mod_col = this->_modSize.col - 1;
	unsigned int			mod_row = this->_modSize.row - 1;
	std::string				word1 = "User";
	std::string				word2 = "Host";

	for (unsigned int i = 0; i <= mod_row; i++)
	{
		move(cursor_tmp.row, cursor_tmp.col);
		if (i == 0)
			print_top(mod_col);
		else if (i == 1)
		{
			addch('|');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2);
			addch('&');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 - 5);
			printw("%s", word1.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 + 2);
			printw("%s", word2.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == 2)
			print_hbar(mod_col);
		else if (i == mod_row)
			print_btm(mod_col);
		else
			print_mid(cursor_tmp.row, cursor_tmp.col + mod_col);
		cursor_tmp.row++;
	}
	move((this->_cursor.row + 2 + mod_row / 2) - 1, ((this->_cursor.col + mod_col / 2) - tmp_mod->getUser().size() / 2));
	printw("%s", tmp_mod->getUser().c_str());
	move((this->_cursor.row + 2 + mod_row / 2) + 1, ((this->_cursor.col + mod_col / 2) - tmp_mod->getHost().size() / 2));
	printw("%s", tmp_mod->getHost().c_str());
}

void						DebugDisplay::displayOsInfo(AModule* mod)
{
	OsInfoMod* tmp_mod = reinterpret_cast<OsInfoMod*>(mod);
	mod->getData();
	Point					cursor_tmp;
	cursor_tmp.col = this->_cursor.col;
	cursor_tmp.row = this->_cursor.row;
	unsigned int			mod_col = this->_modSize.col - 1;
	unsigned int			mod_row = this->_modSize.row - 1;
	std::string				word1 = "OS Info";

	for (unsigned int i = 0; i <= mod_row; i++)
	{
		move(cursor_tmp.row, cursor_tmp.col);
		if (i == 0)
			print_top(mod_col);
		else if (i == 1)
		{
			addch('|');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 - 4);
			printw("%s", word1.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == 2)
			print_hbar(mod_col);
		else if (i == mod_row)
			print_btm(mod_col);
		else
			print_mid(cursor_tmp.row, cursor_tmp.col + mod_col);
		cursor_tmp.row++;
	}
	move((this->_cursor.row + 2 + mod_row / 2) - 2, ((this->_cursor.col + mod_col / 2) - tmp_mod->getSysV().size() / 2));
	printw("%s", tmp_mod->getSysV().c_str());
	move((this->_cursor.row + 2 + mod_row / 2), ((this->_cursor.col + mod_col / 2) - tmp_mod->getKerV().size() / 2));
	printw("%s", tmp_mod->getKerV().c_str());
	move((this->_cursor.row + 2 + mod_row / 2) + 2, ((this->_cursor.col + mod_col / 2) - tmp_mod->getBootVol().size() / 2));
	printw("%s", tmp_mod->getBootVol().c_str());
}

void						DebugDisplay::displayCpu(AModule* mod)
{
	CpuMod* tmp_mod = reinterpret_cast<CpuMod*>(mod);
	mod->getData();
	Point					cursor_tmp;
	cursor_tmp.col = this->_cursor.col;
	cursor_tmp.row = this->_cursor.row;
	unsigned int			mod_col = this->_modSize.col - 1;
	unsigned int			mod_row = this->_modSize.row - 1;
	unsigned int			data_nb = mod_col - 2;
	unsigned int			height;
	std::string				word1 = "CPU Usage";

	for (unsigned int i = 0; i <= mod_row; i++)
	{
		move(cursor_tmp.row, cursor_tmp.col);
		if (i == 0)
			print_top(mod_col);
		else if (i == 1)
		{
			addch('|');
			move(cursor_tmp.row, cursor_tmp.col + mod_col / 2 - 5);
			printw("%s", word1.c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == 2 || i == 4 || i == 6)
			print_hbar(mod_col);
		else if (i == 3)
		{
			addch('|');
			addch(' ');
			printw("%s", tmp_mod->getModel().c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == 5)
		{
			addch('|');
			addch(' ');
			printw("%s", tmp_mod->getCore().c_str());
			move(cursor_tmp.row, cursor_tmp.col + mod_col);
			addch('|');
		}
		else if (i == mod_row)
			print_btm(mod_col);
		else
			print_mid(cursor_tmp.row, cursor_tmp.col + mod_col);
		cursor_tmp.row++;
	}
	std::list<int>::iterator it = tmp_mod->getActivity().end();
	for (unsigned int i = 0; i <= data_nb; i++)
	{
		it--;
		height = *it / 4 / 10;
		if (height > 10)
			height = 10;
		for (unsigned int j = 0; j < height; j++)
		{
			move(this->_cursor.row + mod_row - 1 - j, this->_cursor.col + mod_col - 1 - i);
			addch('#');
		}
	}
}


void				DebugDisplay::reinitCursor(void)
{
	this->_cursor.col = 0;
	this->_cursor.row = 0;
}
