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

#ifndef EVENTMANAGER_HH_
#define EVENTMANAGER_HH_

#include <string>
#include <map>
#include "SharedPtr.hh"

namespace		    Utils
{

  typedef		    void(*t_callback)(void *, void *);

  class			    EventManager
  {
  public:
    EventManager();
    ~EventManager();

    void		    on(const std::string &event, const std::string &id, t_callback callback, void *param);
    void		    cancel(const std::string &event, const std::string &id);
    void		    trigger(const std::string &event, void *triggerParam);

  private:
    class		    EventHandler
    {
    public:
      EventHandler(const std::string &name, t_callback func, void *param);
      ~EventHandler();
      void		    call(void *triggerParam);

    private:
      EventHandler(const EventHandler &model);
      EventHandler	&operator=(const EventHandler &model);
      std::string	_name;
      void		    *_param;
      t_callback	_func;
    }; // EventHandler

  private:
    EventManager	&operator=(const EventManager &model);
    EventManager(const EventManager &model);

  private:
    typedef		std::map<std::string, std::map<std::string, SharedPtr<EventManager::EventHandler> > >	t_collection;
    std::map<std::string, std::map<std::string, SharedPtr<EventManager::EventHandler> > >	_events;
    IMutex		                                                                            *_mutex;
  }; // EventManager

} // Utils

#endif // EVENTMANAGER_HH_
