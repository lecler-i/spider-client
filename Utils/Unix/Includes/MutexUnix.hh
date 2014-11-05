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

#ifndef MUTEXUNIX_HH_
#define MUTEXUNIX_HH_

#include "ILockable.hh"
#include <string>
#include "Exceptions.hh"
#include <pthread.h>
#include "IMutex.hh"

namespace			    Utils
{

  class	       			MutexUnix : public IMutex
  {
  public:
    explicit			MutexUnix(const pthread_mutexattr_t *attr = NULL);
    ~MutexUnix();
    virtual void		lock();
    virtual void		unlock();
    virtual bool		try_lock();
    virtual bool		locked() const;

  private:
    MutexUnix			&operator=(const MutexUnix &);
    MutexUnix(const MutexUnix &);
    pthread_mutex_t		_mutex;
    bool			    _locked;
  }; // MutexUnix

  class				MutexLogicException : public LogicException
  {
  public:
    explicit			MutexLogicException(const std::string &msg);
    ~MutexLogicException() throw();
  }; // MutexLogicException

  class				MutexRuntimeException : public RuntimeException
  {
  public:
    explicit			MutexRuntimeException(const std::string &msg);
    ~MutexRuntimeException() throw();
  }; // MutexRuntimeException

} // Utils

#endif // MUTEXUNIX_HH_
