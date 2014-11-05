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
	void clean_file();

	std::string	getBuff();
	void	setBuff(std::string);
	void	setMod(int);
	int		getMod() const;

private:
	std::string		buff;
	std::fstream	stream;
	int				mod; // attention ne sert surement a rien pas oublié d'enlever
};


#endif // !__WRITER_H__
