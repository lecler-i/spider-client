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

#include "Vector4.hh"
#include <math.h>

template <typename T>
Utils::Vector4<T>::Vector4()
  : x(0), y(0), z(0), w(0)
{
}

template <typename T>
Utils::Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
  : x(_x), y(_y), z(_z), w(_w)
{
}

template <typename T>
Utils::Vector4<T>::Vector4(T a)
  : x(a), y(a), z(a), w(a)
{
}

template <typename T>
Utils::Vector4<T>::Vector4(const Vector4<T> &ref)
  : x(ref.x), y(ref.y), z(ref.z), w(ref.w)
{
}

template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator=(const Vector4<T> &ref)
{
  if (this != &ref)
  {
    this->x = ref.x;
    this->y = ref.y;
    this->z = ref.z;
    this->w = ref.w;
  }
  return (*this);
}

template <typename T>
void		Utils::Vector4<T>::normalize()
{
  T			d;

  d = static_cast<T>(sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
  this->x /= d;
  this->y /= d;
  this->z /= d;
  this->w /= d;
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::normalize(const Vector4<T> &v)
{
  Vector4<T>		res(v);

  res.normalize();
  return (res);
}

template <typename T>
void			Utils::Vector4<T>::serialize(std::ostream &os) const
{
  os << "{ " << x << ", " << y << ", " << z << ", " << w << " }";
}

// ---------- Add ---------
template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator+=(const Vector4<T> &ref)
{
  this->x += ref.x;
  this->y += ref.y;
  this->z += ref.z;
  this->w += ref.w;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator+=(const T &n)
{
  this->x += n;
  this->y += n;
  this->z += n;
  this->w += n;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator+(const Vector4<T> &b) const
{
  Vector4<T>	res(*this);

  res += b;
  return (res);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator+(const T &b) const
{
  Vector4<T>	res(*this);

  res += b;
  return (res);
}

// ---------- Sub ----------
template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator-=(const Vector4<T> &ref)
{
  this->x -= ref.x;
  this->y -= ref.y;
  this->z -= ref.z;
  this->w -= ref.w;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator-=(const T &n)
{
  this->x -= n;
  this->y -= n;
  this->z -= n;
  this->w -= n;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator-(const Vector4<T> &b) const
{
  Vector4<T>	res(*this);

  res -= b;
  return (res);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator-(const T &b) const
{
  Vector4<T>	res(*this);

  res -= b;
  return (res);
}

// ---------- Mult ----------
template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator*=(const Vector4<T> &ref)
{
  this->x *= ref.x;
  this->y *= ref.y;
  this->z *= ref.z;
  this->w *= ref.w;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator*=(const T &n)
{
  this->x *= n;
  this->y *= n;
  this->z *= n;
  this->w *= n;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator*(const Vector4<T> &b) const
{
  Vector4<T>	res(*this);

  res *= b;
  return (res);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator*(const T &b) const
{
  Vector4<T>	res(*this);

  res *= b;
  return (res);
}

// ---------- Div ----------
template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator/=(const Vector4<T> &ref)
{
  this->x /= ref.x;
  this->y /= ref.y;
  this->z /= ref.z;
  this->w /= ref.w;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	&Utils::Vector4<T>::operator/=(const T &n)
{
  this->x /= n;
  this->y /= n;
  this->z /= n;
  this->w /= n;
  return (*this);
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator/(const Vector4<T> &b) const
{
  Vector4<T>	res(*this);

  res /= b;
  return (res);
}

// ---------- Compare ----------
template <typename T>
bool	Utils::Vector4<T>::operator==(const Vector4 &ref) const
{
  return (x == ref.x && y == ref.y && z == ref.z && w == ref.w);
}

template <typename T>
bool	Utils::Vector4<T>::operator!=(const Vector4 &ref) const
{
  return (!(*this == ref));
}

template <typename T>
Utils::Vector4<T>	Utils::Vector4<T>::operator/(const T &b) const
{
  Vector4<T>	res(*this);

  res /= b;
  return (res);
}

template class Utils::Vector4 < int > ;
template class Utils::Vector4 < float > ;
template class Utils::Vector4 < double > ;
template class Utils::Vector4 < char > ;
template class Utils::Vector4 < unsigned int > ;
template class Utils::Vector4 < unsigned char > ;
