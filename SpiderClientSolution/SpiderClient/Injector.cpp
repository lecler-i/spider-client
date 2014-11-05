#include "stdafx.h"
#include "Injector.h"


Injector::Injector()
{
}


Injector::~Injector()
{
}


// Get Debug privileges on current process
void Injector::GetSeDebugPrivilege()
{
	// Open current process token with adjust rights
	HANDLE TempToken;
	BOOL RetVal = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &TempToken);
	if (!RetVal)
		throw std::runtime_error("Injector::GetSeDebugPrivilege: Could not open process token.");
	HANDLE Token = TempToken;

	// Get the LUID for SE_DEBUG_NAME 
	LUID Luid = { NULL }; // Locally unique identifier
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
		throw std::runtime_error("Injector::GetSeDebugPrivilege: Could not look up privilege value for SeDebugName.");
	if (Luid.LowPart == NULL && Luid.HighPart == NULL)
		throw std::runtime_error("Injector::GetSeDebugPrivilege: Could not get LUID for SeDebugName.");

	// Process privileges
	TOKEN_PRIVILEGES Privileges = { NULL };
	// Set the privileges we need
	Privileges.PrivilegeCount = 1;
	Privileges.Privileges[0].Luid = Luid;
	Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Apply the adjusted privileges
	if (!AdjustTokenPrivileges(Token, FALSE, &Privileges,
		sizeof(Privileges), NULL, NULL))
		throw std::runtime_error("Injector::GetSeDebugPrivilege: Could not adjust token privileges.");
}


// Singleton static function to retrieve unique instance
Injector &Injector::GetInstance()
{
	static Injector	instance;
	return instance;
}


// Inject the Dll into Process using CreateRemoteThread methode
HANDLE Injector::InjectRemoteThread(DWORD ProcessId, LPCSTR DllPath)
{
	HANDLE RemoteProc;
	LPVOID MemAlloc;
	LPVOID LoadLibAddress;
	HANDLE ThreadId;

	RemoteProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);
	if (!RemoteProc)
		throw std::runtime_error("Failed to open remote process");

	LoadLibAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	MemAlloc = (LPVOID)VirtualAllocEx(RemoteProc, NULL, strlen(DllPath) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(RemoteProc, (LPVOID)MemAlloc, DllPath, strlen(DllPath) + 1, NULL);
	ThreadId = CreateRemoteThread(RemoteProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddress, (LPVOID)MemAlloc, NULL, NULL);
	
	if (!ThreadId)
		throw std::runtime_error("Failed to create remote thread");
	
	CloseHandle(RemoteProc);
	VirtualFreeEx(RemoteProc, (LPVOID)MemAlloc, 0, MEM_RELEASE | MEM_DECOMMIT);
	return ThreadId;
}
