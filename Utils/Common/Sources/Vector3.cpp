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

#include "Vector3.hh"
#include <math.h>

template <typename T>
Utils::Vector3<T>::Vector3()
  : x(0), y(0), z(0)
{
}

template <typename T>
Utils::Vector3<T>::Vector3(T _x, T _y, T _z)
  : x(_x), y(_y), z(_z)
{
}

template <typename T>
Utils::Vector3<T>::Vector3(T a)
  : x(a), y(a), z(a)
{
}

template <typename T>
Utils::Vector3<T>::Vector3(const Vector3<T> &ref)
  : x(ref.x), y(ref.y), z(ref.z)
{
}

template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator=(const Vector3<T> &ref)
{
  if (this != &ref)
  {
    this->x = ref.x;
    this->y = ref.y;
    this->z = ref.z;
  }
  return (*this);
}

template <typename T>
void			Utils::Vector3<T>::normalize()
{
  T			    d;

  d = static_cast<T>(sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
  this->x /= d;
  this->y /= d;
  this->z /= d;
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::normalize(const Vector3<T> &v)
{
  Vector3<T>		res(v);

  res.normalize();
  return (res);
}

template <typename T>
void			Utils::Vector3<T>::serialize(std::ostream &os) const
{
  os << "{ " << x << ", " << y << ", " << z << " }";
}

// ---------- Add ---------
template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator+=(const Vector3<T> &ref)
{
  this->x += ref.x;
  this->y += ref.y;
  this->z += ref.z;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator+=(const T &n)
{
  this->x += n;
  this->y += n;
  this->z += n;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator+(const Vector3<T> &b) const
{
  Vector3<T>	res(*this);

  res += b;
  return (res);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator+(const T &b) const
{
  Vector3<T>	res(*this);

  res += b;
  return (res);
}

// ---------- Sub ----------
template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator-=(const Vector3<T> &ref)
{
  this->x -= ref.x;
  this->y -= ref.y;
  this->z -= ref.z;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator-=(const T &n)
{
  this->x -= n;
  this->y -= n;
  this->z -= n;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator-(const Vector3<T> &b) const
{
  Vector3<T>	res(*this);

  res -= b;
  return (res);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator-(const T &b) const
{
  Vector3<T>	res(*this);

  res -= b;
  return (res);
}

// ---------- Mult ----------
template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator*=(const Vector3<T> &ref)
{
  this->x *= ref.x;
  this->y *= ref.y;
  this->z *= ref.z;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator*=(const T &n)
{
  this->x *= n;
  this->y *= n;
  this->z *= n;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator*(const Vector3<T> &b) const
{
  Vector3<T>	res(*this);

  res *= b;
  return (res);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator*(const T &b) const
{
  Vector3<T>	res(*this);

  res *= b;
  return (res);
}

// ---------- Div ----------
template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator/=(const Vector3<T> &ref)
{
  this->x /= ref.x;
  this->y /= ref.y;
  this->z /= ref.z;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	&Utils::Vector3<T>::operator/=(const T &n)
{
  this->x /= n;
  this->y /= n;
  this->z /= n;
  return (*this);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator/(const Vector3<T> &b) const
{
  Vector3<T>	res(*this);

  res /= b;
  return (res);
}

template <typename T>
Utils::Vector3<T>	Utils::Vector3<T>::operator/(const T &b) const
{
  Vector3<T>	res(*this);

  res /= b;
  return (res);
}

// ---------- Compare ----------
template <typename T>
bool	Utils::Vector3<T>::operator==(const Vector3 &ref) const
{
  return (x == ref.x && y == ref.y && z == ref.z);
}

template <typename T>
bool	Utils::Vector3<T>::operator!=(const Vector3 &ref) const
{
  return (!(*this == ref));
}

template class Utils::Vector3 < int > ;
template class Utils::Vector3 < float > ;
template class Utils::Vector3 < double > ;
template class Utils::Vector3 < char > ;
template class Utils::Vector3 < unsigned int > ;
template class Utils::Vector3 < unsigned char > ;
