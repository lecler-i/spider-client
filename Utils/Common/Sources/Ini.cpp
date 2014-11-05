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

#include "Ini.hh"
#include <iostream>
#include <sstream>

Utils::Ini::_Positions::_Positions()
{
}

void		Utils::Ini::_Positions::process(const std::string &line)
{
  this->_comment = line.find(';');
  this->_beginSection = line.find('[');
  this->_endSection = line.find(']');
  this->_firstChar = line.find_first_not_of(" \t");
  this->_equal = line.find('=');
  this->_firstAfterEqual = line.find_first_not_of(" \t", this->_equal + 1);
  this->_lastChar = line.find_last_not_of(" \t");
  this->_lastEqual = line.rfind('=');
  this->_lastBeginSection = line.rfind('[');
  this->_lastEndSection = line.rfind(']');
  this->_firstQuote = line.find('"');
  this->_lastQuote = line.rfind('"');
}

Utils::Ini::_Positions::_Positions(const std::string &line)
{
  this->process(line);
}

Utils::Ini::Ini()
  : _opened(false), _filename("")
{
}

const std::map<std::string, std::string> &Utils::Ini::getSection(const std::string &section) const
{
  return (this->_map.find(section)->second);
}

std::string           Utils::Ini::get(const std::string &section,
                                      const std::string &key,
                                      const std::string &def) const
{
  std::map<std::string, std::map<std::string, std::string> >::const_iterator	it1;
  std::map<std::string, std::string>::const_iterator				            it2;

  it1 = this->_map.find(section);
  if (it1 != this->_map.end())
  {
    it2 = it1->second.find(key);
    if (it2 != it1->second.end())
      return (it2->second);
  }
  return (def);
}

void		Utils::Ini::put(const std::string &section,
                            const std::string &key,
                            const std::string &value)
{
  Utils::ScopedMutex(this->_mutex);
  this->_map[section][key] = value;
}

Utils::Ini::Ini(const std::string &filename)
  : _opened(false)
{
  this->open(filename);
}

Utils::Ini::~Ini()
{
  this->close();
}

void		Utils::Ini::open(std::string const &filename,
                             std::ios_base::openmode mode)
{
  Utils::ScopedMutex(this->_mutex);

  if (this->_opened)
  {
    this->close();
    this->_map.clear();
  }
  this->_opened = false;
  this->_filename = filename;
  this->_stream.open(filename.c_str(), mode);
  if (!this->_stream.is_open())
    this->_stream.open(filename.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
  if (!this->_stream.is_open())
    throw new IniRuntimeException("Unable to open/create file " + filename);
  this->_opened = true;
}

void		Utils::Ini::open(std::ios_base::openmode mode)
{
  Utils::ScopedMutex(this->_mutex);

  if (this->_opened)
    return;
  this->_opened = false;
  this->_stream.open(this->_filename.c_str(), mode);
  if (!this->_stream.is_open())
    this->_stream.open(this->_filename.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
  if (!this->_stream.is_open())
    throw new IniRuntimeException("Unable to open/create file " + this->_filename);
  this->_opened = true;
}

void		Utils::Ini::close()
{
  Utils::ScopedMutex(this->_mutex);

  if (this->_opened)
    this->_stream.close();
  this->_opened = false;
}

void				        Utils::Ini::errors(int num, const Utils::Ini::_Positions &pos)
{
  std::string			    error("");
  std::ostringstream		ss;
  Utils::ScopedMutex(this->_mutex);

  error = ((pos._beginSection > pos._endSection) ?
    "bad section declaration" : error);
  error = ((pos._equal == std::string::npos &&
    (pos._beginSection != pos._firstChar ||
    pos._endSection != pos._lastChar)) ?
    "bad section declaration" : error);
  error = ((pos._beginSection == std::string::npos &&
    pos._equal == std::string::npos &&
    pos._firstChar != std::string::npos) ?
    "ununderstandable line found" : error);
  error = (pos._equal != std::string::npos &&
    (pos._beginSection != std::string::npos ||
    pos._endSection != std::string::npos) ?
    "can't mix section and value declaration" : error);
  error = (pos._equal != std::string::npos &&
    pos._firstAfterEqual == std::string::npos ?
    "value needed after key" : error);
  error = (pos._equal != std::string::npos &&
    pos._lastEqual != pos._equal ?
    "multiple '=' on line" : error);
  error = (pos._beginSection != std::string::npos &&
    pos._lastBeginSection != pos._beginSection ?
    "multiple '[' on line" : error);
  error = (pos._endSection != std::string::npos &&
    pos._lastEndSection != pos._endSection ?
    "multiple ']' on line" : error);
  error = (pos._equal != std::string::npos &&
    pos._firstChar == pos._equal ?
    "key needed before value" : error);
  error = (pos._firstQuote != std::string::npos &&
    pos._firstQuote != pos._firstAfterEqual ?
    "quote can't be here" : error);
  if (error != "")
  {
    ss << error << " (line " << num << " in file " << this->_filename << ")";
    throw new IniRuntimeException(ss.str());
  }
}

void		    Utils::Ini::parse()
{
  Utils::ScopedMutex(this->_mutex);
  std::string	line;
  int		    lineNumber;
  std::string	section;
  std::string	key;
  std::string	value;
  bool		    sectionFound;
  _Positions	pos;

  if (!this->_opened)
    this->open();
  lineNumber = 0;
  sectionFound = false;
  while (std::getline(this->_stream, line))
  {
    lineNumber++;
    pos.process(line);
    if (pos._comment != std::string::npos)
    {
      line.erase(pos._comment);
      pos.process(line);
    }
    this->errors(lineNumber, pos);
    if (pos._firstChar != pos._comment && pos._firstChar == pos._beginSection)
    {
      section = line.substr(pos._beginSection + 1, pos._endSection - pos._beginSection - 1);
      sectionFound = true;
    }
    else if (pos._equal != std::string::npos)
    {
      if (!sectionFound)
        throw new IniRuntimeException("section expected before key");
      key = line.substr(pos._firstChar,
        line.find_first_of(" \t=", pos._firstChar + 1) - pos._firstChar);
      if (pos._firstQuote == std::string::npos)
      {
        value = line.substr(pos._firstAfterEqual,
          line.find_first_of(" \t=", pos._firstAfterEqual)
          - pos._firstAfterEqual);
      }
      else
      {
        value = line.substr(pos._firstQuote + 1,
          pos._lastQuote - pos._firstQuote - 1);
      }
      this->_map[section][key] = value;
    }
  }
  this->close();
}

void										                                    Utils::Ini::save()
{
  Utils::ScopedMutex(this->_mutex);
  std::map<std::string, std::map<std::string, std::string> >::const_iterator	it1;
  std::map<std::string, std::map<std::string, std::string> >::const_iterator	end1;
  std::map<std::string, std::string>::const_iterator				            it2;
  std::map<std::string, std::string>::const_iterator				            end2;
  std::string									                                section;

  if (!this->_opened)
    this->open(std::ios_base::out | std::ios_base::trunc);
  end1 = this->_map.end();
  for (it1 = this->_map.begin();
       it1 != end1;
       ++it1)
  {
    section = it1->first;
    this->_stream << "[" << section << "]" << std::endl;
    end2 = it1->second.end();
    for (it2 = it1->second.begin();
      it2 != end2;
      ++it2)
    {
      this->_stream << it2->first << "=" << '"' << it2->second << '"' << std::endl;
    }
  }
  this->close();
}

Utils::IniLogicException::IniLogicException(const std::string &msg)
  : LogicException(std::string("Ini logic error : ") + msg)
{
}

Utils::IniLogicException::~IniLogicException() throw()
{
}

Utils::IniRuntimeException::IniRuntimeException(const std::string &msg)
  : RuntimeException(std::string("Ini runtime error : ") + msg)
{
}

Utils::IniRuntimeException::~IniRuntimeException() throw()
{
}
