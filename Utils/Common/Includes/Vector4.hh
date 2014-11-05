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

#ifndef VECTOR4_HH_
#define VECTOR4_HH_

#include <iostream>

namespace       Utils
{
  template <typename T>
  class         Vector4
  {
  public:
    explicit    Vector4();
    explicit    Vector4(T _x, T _y, T _z, T _w);
    explicit    Vector4(T a);
    virtual     ~Vector4() {}
    Vector4(const Vector4 &ref);
    Vector4     &operator=(const Vector4 &ref);

  public:
    // Add
    Vector4     &operator+=(const Vector4 &ref);
    Vector4     &operator+=(const T &n);
    Vector4     operator+(const Vector4<T> &b) const;
    Vector4     operator+(const T &b) const;

    // Sub
    Vector4     &operator-=(const Vector4 &ref);
    Vector4     &operator-=(const T &n);
    Vector4     operator-(const Vector4<T> &b) const;
    Vector4     operator-(const T &b) const;

    // Mult
    Vector4	    &operator*=(const Vector4 &ref);
    Vector4	    &operator*=(const T &n);
    Vector4	    operator*(const Vector4<T> &b) const;
    Vector4	    operator*(const T &b) const;

    // Div
    Vector4	    &operator/=(const Vector4 &ref);
    Vector4	    &operator/=(const T &n);
    Vector4	    operator/(const Vector4<T> &b) const;
    Vector4	    operator/(const T &b) const;

    // Compare
    bool	    operator==(const Vector4 &ref) const;
    bool	    operator!=(const Vector4 &ref) const;

  public:
    void	    normalize();
    void	    serialize(std::ostream &) const;

  public:
    static Vector4	normalize(const Vector4 &v);

  public:
    T	        x;
    T	        y;
    union { T z; T wid; };
    union { T w; T hei; };
  }; // Vector4

  template <typename T>
  std::ostream  &operator<<(std::ostream &str, const Utils::Vector4<T> &v)
  {
    v.serialize(str);
    return (str);
  }

  // Useful typedefs for easier use
  typedef	Vector4<float>	        vec4;
  typedef	Vector4<float>	        fvec4;
  typedef	Vector4<int>	        ivec4;
  typedef	Vector4<double>	        dvec4;
  typedef	Vector4<char>	        cvec4;
  typedef	Vector4<unsigned int>	uivec4;
  typedef	Vector4<unsigned char>	ucvec4;
} // Utils

#endif // VECTOR4_HH_
