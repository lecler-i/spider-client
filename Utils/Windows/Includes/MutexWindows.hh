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

#ifndef MUTEXWINDOWS_HH_
#define MUTEXWINDOWS_HH_

#include "IMutex.hh"
#include <string>
#include "Exceptions.hh"
#include <windows.h>

namespace				Utils
{

  class					MutexWindows : public IMutex
  {
  public:
    explicit			MutexWindows(LPSECURITY_ATTRIBUTES attr = NULL);
    ~MutexWindows();
    virtual void		lock();
    virtual void		unlock();
    virtual bool		try_lock();

  private:
    MutexWindows		&operator=(const MutexWindows &);
    MutexWindows(const MutexWindows &);
    CRITICAL_SECTION	_criticalSection;
  }; // MutexWindows

  class			MutexLogicException : public LogicException
  {
  public:
    explicit	MutexLogicException(const std::string &msg);
    ~MutexLogicException() throw();
  }; // MutexLogicException

  class			MutexRuntimeException : public RuntimeException
  {
  public:
    explicit	MutexRuntimeException(const std::string &msg);
    ~MutexRuntimeException() throw();
  }; // MutexRuntimeException

} // Utils

#endif // MUTEXWINDOWS_HH_
