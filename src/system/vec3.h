#pragma once

#include "vec4.h"

namespace james {

  template<typename Number>
  struct vec3 {
    typedef Number number_t;

    number_t x;
    number_t y;
    number_t z;

    vec3() : x(0), y(0), z(0) {}
    vec3(number_t x, number_t y, number_t z) : x(x), y(y), z(z) {}

    vec3& operator += (const vec3& b) { x += b.x; y += b.y; z += b.z; return *this; }
    vec3& operator -= (const vec3& b) { x -= b.x; y -= b.y; z -= b.z; return *this; }
    vec3& operator *= (number_t b) { x *= b; y *= b; z *= b; return *this; }
    vec3& operator /= (number_t b) { x /= b; y /= b; z /= b; return *this; }
    vec3& negate() { x = -1; y = -y; z = -z;  return *this; }
    number_t length() { return sqrt(x*x + y*y + z*z); }
  };

  template<typename Number>
  vec3<Number> operator+ (const vec3<Number>& a, const vec3<Number>& b) { return vec3<Number>(a) += b; }

  template<typename Number>
  vec3<Number> operator- (const vec3<Number>& a, const vec3<Number>& b) { return vec3<Number>(a) -= b; }

  template<typename Number>
  vec3<Number> operator* (const vec3<Number>& a, Number b) { return vec3<Number>(a) *= b; }

  template<typename Number>
  vec3<Number> operator* (Number a, const vec3<Number>& b) { return vec3<Number>(b) *= a; }

  template<typename Number>
  vec3<Number> operator/ (const vec3<Number>& a, Number b) { return vec3<Number>(a) /= b; }

  template<typename Number>
  vec3<Number>& normalise(vec3<Number>& a) {
    return a /= a.length();
  }

  template<typename Number>
  vec3<Number> cross3(const vec4<Number>& a, const vec4<Number>& b)
  {
    return vec3<Number>(
      a.y*b.z - a.z*b.y,
      a.z*b.x - a.x*b.z,
      a.x*b.y - a.y*b.x
      );
  }

  template<typename Number>
  Number dot(const vec3<Number>& a, const vec3<Number>& b)
  {
    return a.x*b.x + a.y*b.y + a.z*b.z;
  }

  typedef vec3<float> vec3f;
  typedef vec3<double> vec3d;
  typedef vec3<long double> vec3ld;

}