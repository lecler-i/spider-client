#pragma once

#include "SharedMemoryServer.h"
#include "writer.h"
#include <windows.h>
#include "TCPClient.hh"
#include "ThreadWindows.hh"
#include "Protocole.h"

class Core
{
public:
	Core();
	~Core();

	void	run();
	void	stop();
	void	reseauTCP(const std::string IP, int port);

private:
	SharedMemoryServer		*_shm;
	writer					*_writer;
	Utils::ITCPClient		*_cli;
	HMODULE					_Dll;
	Utils::ThreadWindows	_thr;
	//structure				_buffshm;
	std::string				_buff;
	std::string				_IP;
	int						_PORT;
	int						_mod;
	Protocole				_data;
	t_msg					_msg;
	//	int					_myID; > myID sera dans l'objet proto. on fera un get dessus
};

