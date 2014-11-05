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

#include "Vector2.hh"
#include <math.h>

template <typename T>
Utils::Vector2<T>::Vector2()
  : x(0), y(0)
{
}

template <typename T>
Utils::Vector2<T>::Vector2(T _x, T _y)
  : x(_x), y(_y)
{
}

template <typename T>
Utils::Vector2<T>::Vector2(T a)
  : x(a), y(a)
{
}

template <typename T>
Utils::Vector2<T>::Vector2(const Vector2<T> &ref)
  : x(ref.x), y(ref.y)
{
}

template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator=(const Vector2<T> &ref)
{
  if (this != &ref)
  {
    this->x = ref.x;
    this->y = ref.y;
  }
  return (*this);
}

template <typename T>
void			Utils::Vector2<T>::normalize()
{
  T			    d;

  d = static_cast<T>(sqrt(this->x * this->x + this->y * this->y));
  this->x /= d;
  this->y /= d;
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::normalize(const Vector2<T> &v)
{
  Vector2<T>		res(v);

  res.normalize();
  return (res);
}

template <typename T>
void	Utils::Vector2<T>::serialize(std::ostream &os) const
{
  os << "{ " << x << ", " << y << " }";
}

// ---------- Add ---------
template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator+=(const Vector2<T> &ref)
{
  this->x += ref.x;
  this->y += ref.y;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator+=(const T &n)
{
  this->x += n;
  this->y += n;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator+(const Vector2<T> &b) const
{
  Vector2<T>	res(*this);

  res += b;
  return (res);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator+(const T &b) const
{
  Vector2<T>	res(*this);

  res += b;
  return (res);
}

// ---------- Sub ----------
template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator-=(const Vector2<T> &ref)
{
  this->x -= ref.x;
  this->y -= ref.y;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator-=(const T &n)
{
  this->x -= n;
  this->y -= n;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator-(const Vector2<T> &b) const
{
  Vector2<T>	res(*this);

  res -= b;
  return (res);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator-(const T &b) const
{
  Vector2<T>	res(*this);

  res -= b;
  return (res);
}

// ---------- Mult ----------
template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator*=(const Vector2<T> &ref)
{
  this->x *= ref.x;
  this->y *= ref.y;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator*=(const T &n)
{
  this->x *= n;
  this->y *= n;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator*(const Vector2<T> &b) const
{
  Vector2<T>	res(*this);

  res *= b;
  return (res);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator*(const T &b) const
{
  Vector2<T>	res(*this);

  res *= b;
  return (res);
}

// ---------- Div ----------
template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator/=(const Vector2<T> &ref)
{
  this->x /= ref.x;
  this->y /= ref.y;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	&Utils::Vector2<T>::operator/=(const T &n)
{
  this->x /= n;
  this->y /= n;
  return (*this);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator/(const Vector2<T> &b) const
{
  Vector2<T>	res(*this);

  res /= b;
  return (res);
}

template <typename T>
Utils::Vector2<T>	Utils::Vector2<T>::operator/(const T &b) const
{
  Vector2<T>	res(*this);

  res /= b;
  return (res);
}

// ---------- Compare ----------
template <typename T>
bool	Utils::Vector2<T>::operator==(const Vector2 &ref) const
{
  return (x == ref.x && y == ref.y);
}

template <typename T>
bool	Utils::Vector2<T>::operator!=(const Vector2 &ref) const
{
  return (!(*this == ref));
}

template class Utils::Vector2 < int > ;
template class Utils::Vector2 < float > ;
template class Utils::Vector2 < double > ;
template class Utils::Vector2 < char > ;
template class Utils::Vector2 < unsigned int > ;
template class Utils::Vector2 < unsigned char > ;
