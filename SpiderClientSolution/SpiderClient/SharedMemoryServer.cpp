#include "stdafx.h"
#include "SharedMemoryServer.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

SharedMemoryServer::SharedMemoryServer(const std::string &shm_name) :
_mutex(open_or_create, "testmutex"), _shmName(shm_name)
{
	shared_memory_object::remove(shm_name.c_str());
	_shm = new managed_shared_memory(create_only, shm_name.c_str(), 65536);
	_alloc_inst = new ShmemAllocator(_shm->get_segment_manager());
	_q = _shm->construct<MyDeQueue>("testde")(*_alloc_inst);
	std::cout << "Test !" << std::endl;
}

SharedMemoryServer::~SharedMemoryServer()
{
	_shm->destroy<MyDeQueue>("testde");
	delete _alloc_inst;
	delete _shm;
	shared_memory_object::remove(_shmName.c_str());
	named_mutex::remove("testmutex");
}

Data			SharedMemoryServer::pop()
{
	Data		ret;

	ret.t = NONE;
	{
		scoped_lock<named_mutex> sl(_mutex);
		if (!_q->empty())
		{
			ret = _q->front();
			_q->pop_front();
		}
	}	
	return ret;
}