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

#ifndef TCPCLIENTWINDOWS_HH_
#define TCPCLIENTWINDOWS_HH_

#include <string>
#include <Winsock2.h>
#include <Mswsock.h>
#include "Exceptions.hh"
#include "ITCPClient.hh"

#define BUFFER_SIZE	(4096)

namespace					Utils
{

  class						TCPClientWindows : public ITCPClient
  {
    friend class			TCPServerWindows;
  public:
    explicit				TCPClientWindows();
    ~TCPClientWindows();

  private:
    TCPClientWindows(const TCPClientWindows &);
    TCPClientWindows		&operator=(const TCPClientWindows &);

  public:
    virtual size_t			write(const void *buf, size_t len) const;
    virtual size_t		    read(void *buf, size_t len);
    virtual bool			connect(const std::string &ip, unsigned short int port);

  private:
    void					initializeFromAccept(SOCKET &sock);

  private:
    SOCKET					_socket;
  }; // TCPClientWindows

  class			TCPClientLogicException : public LogicException
  {
  public:
    explicit	TCPClientLogicException(const std::string &msg);
    ~TCPClientLogicException() throw();
  }; // TCPClientLogicException

  class			TCPClientRuntimeException : public RuntimeException
  {
  public:
    explicit	TCPClientRuntimeException(const std::string &msg);
    ~TCPClientRuntimeException() throw();
  }; // TCPClientRuntimeException

} // Utils

#endif // TCPCLIENTWINDOWS_HH_
