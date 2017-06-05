#pragma once

#pragma once

namespace james {

  template<typename Number>
  struct vec4 {
    typedef Number number_t;

    number_t x;
    number_t y;
    number_t z;
    number_t w;

    vec4() : x(0), y(0), z(0), w(1) {}
    vec4(number_t x, number_t y, number_t z, number_t w = 1) : x(x), y(y), z(z), w(w) {}

    vec4& operator += (const vec4& b) { x += b.x; y += b.y; z += b.z; w += b.w; return *this; }
    vec4& operator -= (const vec4& b) { x -= b.x; y -= b.y; z -= b.z; w -= b.w; return *this; }
    vec4& operator *= (number_t b) { x *= b; y *= b; z *= b; w *= b; return *this; }
    vec4& operator /= (number_t b) { x /= b; y /= b; z /= b; w /= b; return *this; }
    vec4& negate() { x = -1; y = -y; z = -z; w = -w; return *this; }
    number_t length() { return sqrt(x*x + y*y + z*z + w*w); }
  };

  template<typename Number>
  vec4<Number> operator+ (const vec4<Number>& a, const vec4<Number>& b) { return vec4<Number>(a) += b; }

  template<typename Number>
  vec4<Number> operator- (const vec4<Number>& a, const vec4<Number>& b) { return vec4<Number>(a) -= b; }

  template<typename Number>
  vec4<Number> operator* (const vec4<Number>& a, Number b) { return vec4<Number>(a) *= b; }

  template<typename Number>
  vec4<Number> operator* (Number a, const vec4<Number>& b) { return vec4<Number>(b) *= a; }

  template<typename Number>
  vec4<Number> operator/ (const vec4<Number>& a, Number b) { return vec4<Number>(a) /= b; }

  template<typename Number>
  vec4<Number>& normalise(vec4<Number>& a) {
    a /= a.length();
    return a;
  }

  typedef vec4<float> vec4f;
  typedef vec4<double> vec4d;
  typedef vec4<long double> vec4ld;

}
