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

#ifndef WEAKPTR_HH_
#define WEAKPTR_HH_

#include "SharedPtr.hh"

namespace       Utils
{

  template <typename T>
  class         WeakPtr
  {
  public:
    explicit    WeakPtr(const SharedPtr<T> &shared)
      : _ptr(shared.get())
    {
    }

    explicit    WeakPtr()
      : _ptr(NULL)
    {
    }

    ~WeakPtr()
    {
    }

    WeakPtr     &operator=(const SharedPtr<T> &ptr)
    {
      this->_ptr = ptr.get();
      return (*this);
    }

    T           &operator*() const
    {
      return (*this->_ptr);
    }

    template <typename U>
    bool        operator==(SharedPtr<U> ptr) const
    {
      return (this->_ptr == ptr.get());
    }

    template <typename U>
    bool        operator==(WeakPtr<U> ptr) const
    {
      return (this->_ptr == ptr.get());
    }

    T           *operator->() const
    {
      return (this->_ptr);
    }

    T           *get() const
    {
      return (this->_ptr);
    }

    bool        operator==(void *ptr) const
    {
      return (this->_ptr == ptr);
    }

  private:
    T           *_ptr;
    explicit    WeakPtr(const WeakPtr<T> &_ref);
    WeakPtr     &operator=(const WeakPtr<T> &_ref);
  }; // WeakPtr

} // Utils

#endif // WEAKPTR_HH_
