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

#ifndef THREAD_HH_
#define THREAD_HH_

#include "IThread.hh"

#if defined(_WIN32) || defined(WIN32) // WINDOWS
#include "Windows/Includes/ThreadWindows.hh"

namespace Utils
{
  inline IThread	*newThread()
  {
    return (new ThreadWindows);
  }
}

#elif defined(__unix) // UNIX
#include "Unix/Includes/ThreadUnix.hh"

namespace Utils
{
  inline IThread	*newThread()
  {
    return (new ThreadUnix);
  }
}
#else
#error "Unknown platform"
#endif // Platform recognition

#endif // THREAD_HH_
