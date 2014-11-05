#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <stdexcept>

class Injector
{
public:
	
	// Get Debug privileges on current process
	void GetSeDebugPrivilege();

private:
	Injector();
	~Injector();
public:
	// Singleton static function to retrieve unique instance
	static Injector &GetInstance();
	// Inject the Dll into Process using CreateRemoteThread methode
	HANDLE InjectRemoteThread(DWORD ProcessId, LPCSTR DllPath);
};

