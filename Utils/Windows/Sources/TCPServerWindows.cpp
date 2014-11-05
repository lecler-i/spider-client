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

#include "Windows/Includes/TCPServerWindows.hh"
#include "Windows/Includes/TCPClientWindows.hh"

Utils::TCPServerWindows::TCPServerWindows()
  : _socket(INVALID_SOCKET)
{
  WSADATA		wsaData;

  if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    throw new TCPServerRuntimeException("Unable to startup properly");
}

Utils::TCPServerWindows::~TCPServerWindows()
{
  if (this->_socket != INVALID_SOCKET)
  {
    if ((closesocket(_socket)) == SOCKET_ERROR)
      throw new TCPServerRuntimeException("Error while closing socket");
  }
  WSACleanup();
}

Utils::ITCPClient	*Utils::TCPServerWindows::accept() const
{
  SOCKET			clientSocket = INVALID_SOCKET;
  sockaddr_in		sinClient;
  int				len = sizeof(sinClient);

  if (_socket == INVALID_SOCKET)
    throw new TCPServerLogicException("Server isn't initialized. Call start first.");
  if ((clientSocket = WSAAccept(_socket, (SOCKADDR*)&sinClient, &len, NULL, NULL)) == 0)
    throw new TCPServerRuntimeException("Unable to accept client");
  ITCPClient		*client = new TCPClientWindows;
  ((TCPClientWindows*)client)->initializeFromAccept(clientSocket);
  return (client);
}

bool				Utils::TCPServerWindows::start(unsigned short int port)
{
  sockaddr_in		sin;

  if ((this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
    return (false);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
    return (false);
  if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
    return (false);
  return (true);
}

Utils::TCPServerLogicException::TCPServerLogicException(const std::string &msg)
  : LogicException(std::string("TCPServer logic error : ") + msg)
{
}

Utils::TCPServerLogicException::~TCPServerLogicException() throw()
{
}

Utils::TCPServerRuntimeException::TCPServerRuntimeException(const std::string &msg)
  : RuntimeException(std::string("TCPServer runtime error : ") + msg)
{
}

Utils::TCPServerRuntimeException::~TCPServerRuntimeException() throw()
{
}