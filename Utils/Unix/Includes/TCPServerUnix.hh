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

#ifndef TCPSERVERUNIX_HH_
#define TCPSERVERUNIX_HH_

#include "ITCPServer.hh"
#include "Exceptions.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace		Utils
{

  class			TCPServerUnix : public ITCPServer
  {
  public:
    TCPServerUnix();
    ~TCPServerUnix();

  private:
    TCPServerUnix(const TCPServerUnix &);
    TCPServerUnix	&operator=(const TCPServerUnix &);

  public:
    virtual bool	start(unsigned short int port);
    virtual ITCPClient	*accept() const;

  private:
    int			_socket;
  }; // TCPServerUnix

  class			TCPServerLogicException : public LogicException
  {
  public:
    explicit		TCPServerLogicException(const std::string &msg);
    ~TCPServerLogicException() throw();
  }; // TCPServerLogicException

  class			TCPServerRuntimeException : public RuntimeException
  {
  public:
    explicit		TCPServerRuntimeException(const std::string &msg);
    ~TCPServerRuntimeException() throw();
  }; // TCPServerRuntimeException

} // Utils

#endif // TCPSERVERUNIX_HH_
