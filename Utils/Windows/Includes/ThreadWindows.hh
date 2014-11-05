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

#ifndef THREADWINDOWS_HH_
#define THREADWINDOWS_HH_

#include <windows.h>
#include <cstdlib>
#include "Exceptions.hh"
#include <string>
#include "IThread.hh"

namespace	        Utils
{

  class				ThreadWindows : public IThread
  {
  public:
    explicit		ThreadWindows(IThreadFunctor *functor, void *arg = NULL);
    explicit		ThreadWindows(void(*func)(void *), void *arg = NULL);
    explicit		ThreadWindows();
    virtual void	join();
    virtual void	launch(IThreadFunctor *functor, void *arg = NULL);
    virtual void	launch(void(*func)(void *), void *arg = NULL);
    ~ThreadWindows();

  private:
    ThreadWindows(const ThreadWindows &ref);
    ThreadWindows	&operator=(const ThreadWindows &ref);
    HANDLE			_thread;
    bool			_started;

  private:
    struct			  FunctorParams
    {
      FunctorParams(IThreadFunctor *f, void *arg)
        : func(f), param(arg)
      {}
      IThreadFunctor  *func;
      void			  *param;
    }; // FunctorParams

    class				ThreadBasicLauncher : public IThreadFunctor
    {
    public:
      ThreadBasicLauncher(void(*f)(void *));
      ~ThreadBasicLauncher();
      virtual void	    operator()(void *arg);

    private:
      void(*_f)(void *);
    }; // ThreadBasicLauncher

  private:
    static DWORD WINAPI	_handler(LPVOID arg);
  }; // ThreadWindows

  class			ThreadLogicException : public LogicException
  {
  public:
    explicit	ThreadLogicException(const std::string &msg);
    ~ThreadLogicException() throw();
  }; // ThreadLogicException

  class			ThreadRuntimeException : public RuntimeException
  {
  public:
    explicit	ThreadRuntimeException(const std::string &msg);
    ~ThreadRuntimeException() throw();
  }; // ThreadRuntimeException

} // Utils

#endif // THREADWINDOWS_HH_
