#pragma once

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/sync/named_condition.hpp>

#include "data.h"

using namespace boost::interprocess;

typedef allocator<Data, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef deque<Data, ShmemAllocator> MyDeQueue;

class SharedMemoryClient
{
public:
	SharedMemoryClient(const std::string &shm_name);
	~SharedMemoryClient();

	void					push(Data &);

private:
	named_mutex				_mutex;
	managed_shared_memory	*_shm;
	MyDeQueue				*_q;
};

