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

#ifndef VECTOR2_HH_
#define VECTOR2_HH_

#include <iostream>

namespace	    Utils
{

  template <typename T>
  class		    Vector2
  {
  public:
    explicit	Vector2();
    explicit	Vector2(T _x, T _y);
    explicit	Vector2(T a);
    virtual	    ~Vector2() {}
    Vector2(const Vector2 &ref);
    Vector2	    &operator=(const Vector2 &ref);

  public:
    // Add
    Vector2	    &operator+=(const Vector2 &ref);
    Vector2	    &operator+=(const T &n);
    Vector2	    operator+(const Vector2<T> &b) const;
    Vector2	    operator+(const T &b) const;

    // Sub
    Vector2	    &operator-=(const Vector2 &ref);
    Vector2	    &operator-=(const T &n);
    Vector2	    operator-(const Vector2<T> &b) const;
    Vector2	    operator-(const T &b) const;

    // Mult
    Vector2	    &operator*=(const Vector2 &ref);
    Vector2	    &operator*=(const T &n);
    Vector2	    operator*(const Vector2<T> &b) const;
    Vector2	    operator*(const T &b) const;

    // Div
    Vector2	    &operator/=(const Vector2 &ref);
    Vector2	    &operator/=(const T &n);
    Vector2	    operator/(const Vector2<T> &b) const;
    Vector2	    operator/(const T &b) const;

    // Compare
    bool	    operator==(const Vector2 &ref) const;
    bool	    operator!=(const Vector2 &ref) const;

  public:
    void	    normalize();
    void	    serialize(std::ostream &os) const;

  public:
    static Vector2	normalize(const Vector2 &v);

  public:
    T	        x;
    T	        y;
  }; // Vector2

  template <typename T>
  std::ostream	&operator<<(std::ostream &str, const Vector2<T> &v)
  {
    v.serialize(str);
    return (str);
  }

  typedef	Vector2<float>	            vec2;
  typedef	Vector2<float>	            fvec2;
  typedef	Vector2<int>	            ivec2;
  typedef	Vector2<double>	            dvec2;
  typedef	Vector2<char>	            cvec2;
  typedef	Vector2<unsigned int>		uivec2;
  typedef	Vector2<unsigned char>		ucvec2;
} // Utils

#endif // VECTOR2_HH_
