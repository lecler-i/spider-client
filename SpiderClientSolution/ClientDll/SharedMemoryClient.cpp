#include "stdafx.h"
#include "SharedMemoryClient.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

SharedMemoryClient::SharedMemoryClient(const std::string &shm_name) :
_mutex(open_or_create, "myMutex")
{
	//_shm = new managed_shared_memory(open_only, shm_name.c_str());
	//_q = _shm->find<MyDeQueue>("dequeue").first;
}


SharedMemoryClient::~SharedMemoryClient()
{
}

void		SharedMemoryClient::push(Data &data)
{
	scoped_lock<named_mutex> sl(_mutex);
	_q->push_back(data);
}