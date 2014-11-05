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

#include "Unix/Includes/TCPClientUnix.hh"

Utils::TCPClientUnix::TCPClientUnix()
  : _socket(-1)
{
}

Utils::TCPClientUnix::~TCPClientUnix()
{
  if (_socket != -1)
    close(this->_socket);
}

size_t			Utils::TCPClientUnix::write(const void *buf, size_t len) const
{
  if (_socket == -1)
    throw new TCPClientLogicException("Can't send because socket is uninitialized");
  return (::write(_socket, buf, len));
}

bool			Utils::TCPClientUnix::connect(const std::string &ip, unsigned short int port)
{
  struct protoent       *proto;
  struct sockaddr_in    sin;

  proto = getprotobyname("TCP");
  if ((_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto)) < 0)
    return (false);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip.c_str());
  if ((::connect(_socket, (const struct sockaddr *)&sin, sizeof(sin))) < 0)
    return (false);
  return (true);
}

size_t			Utils::TCPClientUnix::read(void *buf, size_t len)
{
  int			read_len;

  if (_socket == -1)
    throw new TCPClientLogicException("Can't receive because socket is uninitialized");
  read_len = ::read(_socket, buf, len);
  return (read_len);
}

void			Utils::TCPClientUnix::initializeFromAccept(int sock)
{
  if (sock < 0)
    throw new TCPClientRuntimeException("Socket is invalid");
  if (_socket != -1)
    throw new TCPClientRuntimeException("Already initialized");
  _socket = sock;
}

Utils::TCPClientLogicException::TCPClientLogicException(const std::string &msg)
  : LogicException(std::string("TCPClient logic error : ") + msg)
{
}

Utils::TCPClientLogicException::~TCPClientLogicException() throw()
{
}

Utils::TCPClientRuntimeException::TCPClientRuntimeException(const std::string &msg)
  : RuntimeException(std::string("TCPClient runtime error : ") + msg)
{
}

Utils::TCPClientRuntimeException::~TCPClientRuntimeException() throw()
{
}
