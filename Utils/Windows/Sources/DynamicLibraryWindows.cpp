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

#include "Windows/Includes/DynamicLibraryWindows.hh"
#include <iostream>

Utils::DynamicLibraryWindows::DynamicLibraryWindows(std::string const &path)
	: _lib(NULL)
{
	this->load(path);
}

Utils::DynamicLibraryWindows::DynamicLibraryWindows()
	: _lib(NULL)
{
}

Utils::DynamicLibraryWindows::~DynamicLibraryWindows()
{
	this->unload();
}

void	*Utils::DynamicLibraryWindows::findFunc(std::string const &name)
{
	if (!this->_lib)
		throw Utils::DynamicLibraryLogicException("No library loaded");
	return (GetProcAddress(this->_lib, name.c_str()));
}

bool	Utils::DynamicLibraryWindows::load(std::string const &path)
{
	this->unload();
	this->_lib = LoadLibrary(path.c_str());
	if (!this->_lib)
		return (false);
	return (true);
}

void	Utils::DynamicLibraryWindows::unload()
{
	int	ret;

	if (this->_lib != NULL)
	{
		ret = FreeLibrary(this->_lib);
		if (ret == 0)
			throw Utils::DynamicLibraryRuntimeException("Error while unloading library");
	}
	this->_lib = NULL;
}

Utils::DynamicLibraryLogicException::DynamicLibraryLogicException(const std::string &msg)
	: LogicException(std::string("DynamicLibrary logic error : ") + msg)
{
}

Utils::DynamicLibraryLogicException::~DynamicLibraryLogicException() throw()
{
}

Utils::DynamicLibraryRuntimeException::DynamicLibraryRuntimeException(const std::string &msg)
	: RuntimeException(std::string("DynamicLibrary runtime error : ") + msg)
{
}

Utils::DynamicLibraryRuntimeException::~DynamicLibraryRuntimeException() throw()
{
}