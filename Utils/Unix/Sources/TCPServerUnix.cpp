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

#include "Unix/Includes/TCPServerUnix.hh"
#include "Unix/Includes/TCPClientUnix.hh"

Utils::TCPServerUnix::TCPServerUnix()
  : _socket(-1)
{
}

Utils::TCPServerUnix::~TCPServerUnix()
{
  if (this->_socket != -1)
  {
    if ((close(_socket)) == -1)
      throw new TCPServerRuntimeException("Error while closing socket");
  }
}

Utils::ITCPClient	*Utils::TCPServerUnix::accept() const
{
  int			clientSocket = -1;
  sockaddr_in		sinClient;
  int			len = sizeof(sinClient);

  if (_socket == -1)
    throw new TCPServerLogicException("Server isn't initialized. Call start first.");
  if ((clientSocket = ::accept(_socket, (struct sockaddr *)&sinClient,
			       (socklen_t *)&len)) < 0)
    throw new TCPServerRuntimeException("Unable to accept client");
  ITCPClient		*client = new TCPClientUnix;
  ((TCPClientUnix*)client)->initializeFromAccept(clientSocket);
  return (client);
}

bool			Utils::TCPServerUnix::start(unsigned short int port)
{
  struct protoent	*protocol;
  sockaddr_in		sin;

  if ((protocol = getprotobyname("TCP")) == NULL)
    return (false);
  if ((this->_socket = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) < 0)
    return (false);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
    return (false);
  if (listen(this->_socket, 100) < 0)
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
