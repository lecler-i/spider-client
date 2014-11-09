#include "stdafx.h"
#include "SharedMemoryClient.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

SharedMemoryClient::SharedMemoryClient(const std::string &shm_name) :
_mutex(open_only, "testmutex")
{
	_shm = new managed_shared_memory(open_only, shm_name.c_str());
	_q = _shm->find<MyDeQueue>("testde").first;
}


SharedMemoryClient::~SharedMemoryClient()
{
}

void		SharedMemoryClient::push(Data &data)
{
	OutputDebugStringW(L"TY TO PUSH");

	scoped_lock<named_mutex> sl(_mutex);
	OutputDebugStringW(L"LOCK DONE");
	_q->push_back(data);
	OutputDebugStringW(L"PUSH OK");
}