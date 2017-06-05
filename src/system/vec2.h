#pragma once

namespace james {

  template<typename Number>
  struct vec2 {
    typedef Number number_t;

    number_t x;
    number_t y;

    vec2() : x(0), y(0) {}
    vec2(number_t x, number_t y) : x(x), y(y) {}

    vec2& operator += (const vec2& b) { x += b.x; y += b.y; return *this; }
    vec2& operator -= (const vec2& b) { x -= b.x; y -= b.y; return *this; }
    vec2& operator *= (number_t b) { x *= b; y *= b; return *this; }
    vec2& operator /= (number_t b) { x /= b; y /= b; return *this; }
    vec2& negate() { x = -1; y = -y; return *this; }
  };

  template<typename Number>
  vec2<Number> operator+ (const vec2<Number>& a, const vec2<Number>& b) { return vec2<Number>(a) += b; }

  template<typename Number>
  vec2<Number> operator- (const vec2<Number>& a, const vec2<Number>& b) { return vec2<Number>(a) -= b; }

  template<typename Number>
  vec2<Number> operator* (const vec2<Number>& a, Number b) { return vec2<Number>(a) *= b; }

  template<typename Number>
  vec2<Number> operator* (Number a, const vec2<Number>& b) { return vec2<Number>(b) *= a; }

  template<typename Number>
  vec2<Number> operator/ (const vec2<Number>& a, Number b) { return vec2<Number>(a) /= b; }

  typedef vec2<float> vec2f;
  typedef vec2<double> vec2d;
  typedef vec2<long double> vec2ld;

}