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

#ifndef VECTOR3_HH_
#define VECTOR3_HH_

#include <iostream>

namespace	    Utils
{

  template <typename T>
  class		    Vector3
  {
  public:
    explicit	Vector3();
    explicit	Vector3(T _x, T _y, T _z);
    explicit	Vector3(T a);
    virtual	    ~Vector3() {}
    Vector3(const Vector3 &ref);
    Vector3	    &operator=(const Vector3 &ref);

  public:
    // Add
    Vector3	    &operator+=(const Vector3 &ref);
    Vector3	    &operator+=(const T &n);
    Vector3	    operator+(const Vector3<T> &b) const;
    Vector3	    operator+(const T &b) const;

    // Sub
    Vector3	    &operator-=(const Vector3 &ref);
    Vector3	    &operator-=(const T &n);
    Vector3	    operator-(const Vector3<T> &b) const;
    Vector3	    operator-(const T &b) const;

    // Mult
    Vector3	    &operator*=(const Vector3 &ref);
    Vector3	    &operator*=(const T &n);
    Vector3	    operator*(const Vector3<T> &b) const;
    Vector3	    operator*(const T &b) const;

    // Div
    Vector3	    &operator/=(const Vector3 &ref);
    Vector3	    &operator/=(const T &n);
    Vector3	    operator/(const Vector3<T> &b) const;
    Vector3	    operator/(const T &b) const;

    // Compare
    bool	    operator==(const Vector3 &ref) const;
    bool	    operator!=(const Vector3 &ref) const;

  public:
    void	    normalize();
    void	    serialize(std::ostream &os) const;

  public:
    static Vector3	normalize(const Vector3 &v);

  public:
    T	        x;
    T	        y;
    T	        z;
  }; // Vector3

  template <typename T>
  std::ostream	&operator<<(std::ostream &str, const Vector3<T> &v)
  {
    v.serialize(str);
    return (str);
  }

  // Useful typedefs for easier use
  typedef	Vector3<float>          	vec3;
  typedef	Vector3<float>	            fvec3;
  typedef	Vector3<int>	            ivec3;
  typedef	Vector3<double>	            dvec3;
  typedef	Vector3<char>	            cvec3;
  typedef	Vector3<unsigned int>		uivec3;
  typedef	Vector3<unsigned char>		ucvec3;
} // Utils

#endif // VECTOR3_HH_
