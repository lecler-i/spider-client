/*
	The MIT License(MIT)

	Copyright (c) 2014 Cedric Sana (Ninetainedo - cedricsana@gmail.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "Unix/Includes/MutexUnix.hh"

Utils::MutexUnix::MutexUnix(const pthread_mutexattr_t *attr)
  : _locked(false)
{
  if (pthread_mutex_init(&this->_mutex, attr) != 0)
    throw new Utils::MutexRuntimeException("Could not initialize mutex");
}

Utils::MutexUnix::~MutexUnix()
{
  if (pthread_mutex_destroy(&this->_mutex) != 0)
    throw new Utils::MutexLogicException("Could not destroy mutex");
}

bool	Utils::MutexUnix::locked() const
{
  return (this->_locked);
}

void	Utils::MutexUnix::lock()
{
  if (pthread_mutex_lock(&this->_mutex) != 0)
    throw new Utils::MutexLogicException("Could not lock mutex");
  this->_locked = true;
}

void	Utils::MutexUnix::unlock()
{
  this->_locked = false;
  if (pthread_mutex_unlock(&this->_mutex) != 0)
    throw new Utils::MutexLogicException("Could not unlock mutex");
}

bool	Utils::MutexUnix::try_lock()
{
  if (pthread_mutex_trylock(&this->_mutex) == 0)
    {
      this->_locked = true;
      return (true);
    }
  this->_locked = false;
  return (false);
}

Utils::MutexLogicException::MutexLogicException(const std::string &msg)
  : LogicException(std::string("Mutex logic error : ") + msg)
{
}

Utils::MutexLogicException::~MutexLogicException() throw()
{
}

Utils::MutexRuntimeException::MutexRuntimeException(const std::string &msg)
  : RuntimeException(std::string("Mutex runtime error : ") + msg)
{
}

Utils::MutexRuntimeException::~MutexRuntimeException() throw()
{
}
