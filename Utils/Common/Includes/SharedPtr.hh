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

#ifndef SHAREDPTR_HH_
#define SHAREDPTR_HH_

#include <cstdlib>
#include <iostream>
#include "Mutex.hh"

namespace	Utils
{

  template <typename T>
  class		SharedPtr
  {
  public:
    typedef	T	ptr_type;
    typedef	void(*delete_func)(T *);

    SharedPtr(ptr_type *ptr = NULL, delete_func f = NULL)
      : _ptr(ptr), _d(f)
    {
      this->_count = new _Count(ptr);
      ScopedMutex(this->_count->_mutex);
      if (this->_count->_count == 0)
        this->_count->_count = 1;
      else
        this->_count->_count += 1;
    }

    SharedPtr(const SharedPtr<T> &model)
      : _ptr(model.get()), _d(model._d)
    {
      this->_count = model._count;
      if (this->_count)
      {
        ScopedMutex(this->_count->_mutex);
        if (this->_count->_count == 0)
          this->_count->_count = 1;
        else
          this->_count->_count += 1;
      }
    }

    ~SharedPtr()
    {
      if (this->_count)
      {
        ScopedMutex(this->_count->_mutex);
        if (this->_count->_count == 1)
        {
          if (this->_d == NULL)
            delete (this->_ptr);
          else
            this->_d(this->_ptr);
        }
        this->_count->_count -= 1;
        if (this->_count->_count == 0)
        {
          delete (this->_count);
          this->_count = NULL;
        }
      }
    }

    std::ostream  &operator<<(const std::ostream &os)
    {
      os << this->_ptr;
      return (os);
    }

    operator T*()
    {
      return (this->get());
    }

    T			  **operator&()
    {
      return (&this->_ptr);
    }

    SharedPtr	  &operator=(const SharedPtr &model)
    {
      _Count	  *tmp;
      ptr_type	  *ptr;

      if (this->_count)
        ScopedMutex(this->_count->_mutex);
      if (this->_count != model._count && model._count)
        ScopedMutex(model._count->_mutex);
      ptr = model.get();
      tmp = model._count;
      if (tmp)
      {
        if (tmp->_count == 0)
          tmp->_count = 1;
        else
          tmp->_count += 1;
      }
      if (this->_count)
      {
        if (this->_count->_count == 1)
        {
          if (this->_d == NULL)
            delete (this->_ptr);
          else
            this->_d(this->_ptr);
        }
        this->_count->_count -= 1;
        if (this->_count->_count == 0)
          delete (this->_count);
      }
      this->_count = tmp;
      this->_ptr = ptr;
      this->_d = model._d;
      return (*this);
    }

    // TODO : change this system to use a static function which registers for all SharedPtr instances
    void	      registerDestroyFunc(delete_func f)
    {
      this->_d = f;
    }

    SharedPtr	  &operator=(ptr_type *ptr)
    {
      _Count	  *tmp;

      tmp = new _Count(ptr);
      if (this->_count)
        ScopedMutex(this->_count->_mutex);
      if (tmp->_count == 0)
        tmp->_count = 1;
      else
        tmp->_count += 1;
      if (this->_count)
      {
        if (this->_count->_count == 1)
        {
          if (this->_d == NULL)
            delete (this->_ptr);
          else
            this->_d(this->_ptr);
        }
        this->_count->_count -= 1;
        if (this->_count->_count == 0)
          delete (this->_count);
      }
      this->_count = tmp;
      this->_ptr = ptr;
      return (*this);
    }

    ptr_type	  &operator*() const
    {
      return (*this->_ptr);
    }

    bool	      operator==(void *ptr) const
    {
      return (this->_ptr == ptr);
    }

    template <typename U>
    bool	      operator==(const SharedPtr<U> &ptr) const
    {
      return (this->_ptr == ptr.get());
    }

    bool	      operator!=(void *ptr) const
    {
      return (this->_ptr != ptr);
    }

    template <typename U>
    bool	      operator!=(const SharedPtr<U> &ptr) const
    {
      return (this->_ptr != ptr.get());
    }

    ptr_type	  *operator->() const
    {
      return (this->_ptr);
    }

    void	      reset()
    {
      if (this->_count)
      {
        ScopedMutex(this->_count->_mutex);
        if (this->_count->_count == 1)
        {
          if (this->_d == NULL)
            delete (this->_ptr);
          else
            this->_d(this->_ptr);
        }
        this->_count->_count -= 1;
        if (this->_count->_count == 0)
          delete (this->_count);
      }
      this->_count = NULL;
      this->_ptr = NULL;
    }

    ptr_type	  *get() const
    {
      return (this->_ptr);
    }

    delete_func	  getDeletor() const
    {
      return (this->_d);
    }

  private:
    class	_Count
    {
    public:
      _Count(T *ptr)
        : _ptr(ptr), _mutex(newMutex()), _count(0)
      {}
      T		  *_ptr;
      IMutex  *_mutex;
      int	  _count;
    }; // _Count

  private:
    _Count	      *_count;
    ptr_type	  *_ptr;
    delete_func	  _d;
    static IMutex *_mutex;
  }; // SharedPtr

  template <typename T> IMutex	*SharedPtr<T>::_mutex = newMutex();

};

#endif // SHAREDPTR_HH_
