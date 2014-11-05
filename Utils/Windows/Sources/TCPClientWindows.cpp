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

#include "Windows/Includes/TCPClientWindows.hh"

Utils::TCPClientWindows::TCPClientWindows()
  : _socket(INVALID_SOCKET)
{
  WSADATA		wsaData;

  if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    throw new TCPClientRuntimeException("Unable to startup properly");
}

Utils::TCPClientWindows::~TCPClientWindows()
{
  if (_socket != INVALID_SOCKET)
    closesocket(this->_socket);
  WSACleanup();
}

size_t		Utils::TCPClientWindows::write(const void *buf, size_t len) const
{
  int       res;

  if (_socket == INVALID_SOCKET)
    throw new TCPClientLogicException("Can't send because socket is uninitialized");
  res = ::send(_socket, static_cast<const char *>(buf), len, 0);
  return (res == SOCKET_ERROR ? -1 : res);
}

bool	    Utils::TCPClientWindows::connect(const std::string &ip, unsigned short int port)
{
  sockaddr_in		sin;

  if ((this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
    return (false);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip.c_str());
  if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
    return (false);
  if ((WSAConnect(_socket, (const struct sockaddr *)&sin, sizeof(sin), NULL, NULL, NULL, NULL)) == SOCKET_ERROR)
    return (false);
  return (true);
}

size_t		    Utils::TCPClientWindows::read(void *buf, size_t len)
{
  int			flags = 0;

  if (_socket == INVALID_SOCKET)
    throw new TCPClientLogicException("Can't receive because socket is uninitialized");
  int n = WSARecvEx(_socket, static_cast<char *>(buf), BUFFER_SIZE - 1, &flags);
  return (n == SOCKET_ERROR ? -1 : n);
}

void			Utils::TCPClientWindows::initializeFromAccept(SOCKET &sock)
{
  if (sock == INVALID_SOCKET)
    throw new TCPClientRuntimeException("Socket is invalid");
  if (_socket != INVALID_SOCKET)
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
