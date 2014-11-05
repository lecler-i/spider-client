#pragma once

#ifndef __WRITER_H__
#define	__WRITER_H__

#include <fstream>
#include <string>

#define	W_MOD (1)
#define S_MOD (2)

class writer
{
public:
	writer();
	~writer();

	void putOnFile();
	void clean_buff();

	std::string	getBuff();
	void	setBuff(std::string);
	void	setMod(int);
	int		getMod();

private:
	std::string		buff;
	std::fstream	stream;
	int				mod;
};


#endif // !__WRITER_H__
