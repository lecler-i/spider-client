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

#ifndef DYNAMICLIBRARYWINDOWS_HH_
#define DYNAMICLIBRARYWINDOWS_HH_

#include "IDynamicLibrary.hh"
#include "Exceptions.hh"
#include <string>
#include <windows.h>

namespace	                Utils
{

  class			            DynamicLibraryWindows : public IDynamicLibrary
  {
  public:
    bool		            load(std::string const &path);
    void		            unload();
    void		            *findFunc(std::string const &name);
    DynamicLibraryWindows(std::string const &path);
    DynamicLibraryWindows();
    ~DynamicLibraryWindows();

  private:
    DynamicLibraryWindows(const DynamicLibraryWindows &model);
    DynamicLibraryWindows	&operator=(const DynamicLibraryWindows &model);

  private:
    HMODULE					_lib;
  }; // DynamicLibraryWindows

  class			DynamicLibraryLogicException : public LogicException
  {
  public:
    DynamicLibraryLogicException(const std::string &msg);
    ~DynamicLibraryLogicException() throw();
  }; // DynamicLibraryLogicException

  class			DynamicLibraryRuntimeException : public RuntimeException
  {
  public:
    DynamicLibraryRuntimeException(const std::string &msg);
    ~DynamicLibraryRuntimeException() throw();
  }; // DynamicLibraryRuntimeException

} // Utils

#endif // DYNAMICLIBRARYWINDOWS_HH_
