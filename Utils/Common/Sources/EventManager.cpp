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

#include "EventManager.hh"

Utils::EventManager::EventManager()
{
}

Utils::EventManager::~EventManager()
{
  std::map<std::string, SharedPtr<EventHandler> >::const_iterator	it2;
  std::map<std::string, SharedPtr<EventHandler> >::const_iterator	end2;
  Utils::EventManager::t_collection::const_iterator			        it1;
  Utils::EventManager::t_collection::const_iterator			        end1;

  end1 = this->_events.end();
  for (it1 = this->_events.begin();
    it1 != end1;
    ++it1)
  {
    end2 = it1->second.end();
    for (it2 = it1->second.begin();
      it2 != end2;
      ++it2)
    {
      static_cast<SharedPtr<EventHandler> >(it2->second).reset();
    }
  }
}

void		Utils::EventManager::on(const std::string &event,
                                    const std::string &id,
                                    Utils::t_callback callback,
                                    void *param)
{
  Utils::ScopedMutex(this->_mutex);

  this->cancel(event, id);
  this->_events[event][id] = new EventHandler(id, callback, param);
}

void		Utils::EventManager::cancel(const std::string &event, const std::string &id)
{
  Utils::ScopedMutex(this->_mutex);

  if (this->_events.find(event) != this->_events.end() &&
      this->_events[event].find(id) != this->_events[event].end())
  {
    this->_events[event][id].reset();
    this->_events[event].erase(id);
  }
}

void					Utils::EventManager::trigger(const std::string &event,
                                                     void *triggerParam)
{
  Utils::ScopedMutex(this->_mutex);
  std::map<std::string, SharedPtr<EventHandler> >::const_iterator	it;
  std::map<std::string, SharedPtr<EventHandler> >::const_iterator	end;

  end = this->_events[event].end();
  for (it = this->_events[event].begin();
       it != end;
       ++it)
  {
    it->second->call(triggerParam);
  }
}

Utils::EventManager::EventHandler::EventHandler(const std::string &name,
                                                Utils::t_callback func,
                                                void *param)
  : _name(name), _param(param), _func(func)
{
}

Utils::EventManager::EventHandler::~EventHandler()
{
}

void		Utils::EventManager::EventHandler::call(void *triggerParam)
{
  this->_func(triggerParam, this->_param);
}
