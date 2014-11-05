#include "stdafx.h"
#include "writer.h"


void	writer::putOnFile()
{
	this->stream.open("C:\\Users\\Nqd\\.log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	this->stream << buff.c_str();
	this->stream.close();
}

void	clean_file()
{
	int	i;

	i = remove("C:\\Users\\Nqd\\.log.txt");
	/* if i != 0 > fail*/
}

void	writer::setBuff(std::string s)
{
	this->buff = s;
}

std::string		writer::getBuff()
{
	return (this->buff);
}

void			writer::setMod(int m)
{
	this->mod = m;
}

int				writer::getMod() { return (this->mod); }

writer::writer()
{

}

writer::~writer()
{
}
