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

#include "Unix/Includes/ThreadUnix.hh"
#include "SharedPtr.hh"
#include <iostream>

Utils::ThreadUnix::ThreadUnix()
  : _started(false)
{
}

Utils::ThreadUnix::ThreadUnix(IThreadFunctor *functor, void *arg)
  : _started(false)
{
  this->launch(functor, arg);
}

Utils::ThreadUnix::ThreadUnix(void(*func)(void *), void *arg)
  : _started(false)
{
  this->launch(func, arg);
}

Utils::ThreadUnix::~ThreadUnix()
{
}

Utils::ThreadUnix::ThreadBasicLauncher::ThreadBasicLauncher(void(*f)(void *))
  : _f(f)
{
}

Utils::ThreadUnix::ThreadBasicLauncher::~ThreadBasicLauncher()
{
}

void	Utils::ThreadUnix::ThreadBasicLauncher::operator()(void *arg)
{
  _f(arg);
}

void		*Utils::ThreadUnix::_handler(void *arg)
{
  FunctorParams	*params = static_cast<FunctorParams *>(arg);

  (*params->func)(params->param);
  return (NULL);
}

void		Utils::ThreadUnix::launch(IThreadFunctor *functor, void *arg)
{
  FunctorParams	*params = new FunctorParams(functor, arg);

  if (_started == true)
    throw new ThreadLogicException("Thread already launched");
  if ((pthread_create(&this->_thread, NULL, _handler, params)) != 0)
    throw new ThreadRuntimeException("Could not initialize thread");
  _started = true;
}

void			Utils::ThreadUnix::launch(void(*func)(void *), void *arg)
{
  ThreadBasicLauncher	*_threadBasicLauncher = new ThreadBasicLauncher(func);

  this->launch(_threadBasicLauncher, arg);
}

void		Utils::ThreadUnix::join()
{
  if (_started == false)
    throw new ThreadLogicException("Thread wasn't running");
  if (pthread_join(this->_thread, NULL) != 0)
    throw new ThreadLogicException("Could not join thread");
}

Utils::ThreadLogicException::ThreadLogicException(const std::string &msg)
  : LogicException(std::string("Thread logic error : ") + msg)
{
}

Utils::ThreadLogicException::~ThreadLogicException() throw()
{
}

Utils::ThreadRuntimeException::ThreadRuntimeException(const std::string &msg)
  : RuntimeException(std::string("Thread runtime error : ") + msg)
{
}

Utils::ThreadRuntimeException::~ThreadRuntimeException() throw()
{
}
