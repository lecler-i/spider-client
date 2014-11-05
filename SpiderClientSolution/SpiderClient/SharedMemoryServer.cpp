#include "stdafx.h"
#include "SharedMemoryServer.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

SharedMemoryServer::SharedMemoryServer(const std::string &shm_name) :
_mutex(create_only, "my_mutex"), _shmName(shm_name)
{
	named_mutex::remove("my_mutex");
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
	named_mutex::remove("my_mutex");
}

Data			SharedMemoryServer::pop()
{
	Data		ret;
	ret.t = KEYPRESS;
	{
		scoped_lock<named_mutex> sl(_mutex);

		if (!_q->empty())
		{
			std::cout << "NOT EMPTY" << std::endl;
			ret = _q->front();
			_q->pop_front();
		}
	}	
	return ret;
}