#pragma once

#define _USE_MATH_DEFINES

#include "vec3.h"
#include "vec4.h"
#include <math.h>

namespace james {

  template<typename Number>
  struct mat4x4
  {
    typedef Number number_t;
    number_t m[16];

    mat4x4()
      : m()
    {
      m[0] = 1; m[5] = 1; m[10] = 1; m[15] = 1;
    }

    number_t& operator()(unsigned int r, unsigned int c) {
      return m[(r << 2) + c];
    }

    number_t const& operator()(unsigned int r, unsigned int c) const {
      return m[(r << 2) + c];
    }

    mat4x4& operator*= (const mat4x4& a) {
      const mat4x4 b(*this);
      mat4x4& c = *this;

      c(0, 0) = a(0, 0)*b(0, 0) + a(0, 1)*b(1, 0) + a(0, 2)*b(2, 0) + a(0, 3)*b(3, 0);
      c(1, 0) = a(1, 0)*b(0, 0) + a(1, 1)*b(1, 0) + a(1, 2)*b(2, 0) + a(1, 3)*b(3, 0);
      c(2, 0) = a(2, 0)*b(0, 0) + a(2, 1)*b(1, 0) + a(2, 2)*b(2, 0) + a(2, 3)*b(3, 0);
      c(3, 0) = a(3, 0)*b(0, 0) + a(3, 1)*b(1, 0) + a(3, 2)*b(2, 0) + a(3, 3)*b(3, 0);

      c(0, 1) = a(0, 0)*b(0, 1) + a(0, 1)*b(1, 1) + a(0, 2)*b(2, 1) + a(0, 3)*b(3, 1);
      c(1, 1) = a(1, 0)*b(0, 1) + a(1, 1)*b(1, 1) + a(1, 2)*b(2, 1) + a(1, 3)*b(3, 1);
      c(2, 1) = a(2, 0)*b(0, 1) + a(2, 1)*b(1, 1) + a(2, 2)*b(2, 1) + a(2, 3)*b(3, 1);
      c(3, 1) = a(3, 0)*b(0, 1) + a(3, 1)*b(1, 1) + a(3, 2)*b(2, 1) + a(3, 3)*b(3, 1);

      c(0, 2) = a(0, 0)*b(0, 2) + a(0, 1)*b(1, 2) + a(0, 2)*b(2, 2) + a(0, 3)*b(3, 2);
      c(1, 2) = a(1, 0)*b(0, 2) + a(1, 1)*b(1, 2) + a(1, 2)*b(2, 2) + a(1, 3)*b(3, 2);
      c(2, 2) = a(2, 0)*b(0, 2) + a(2, 1)*b(1, 2) + a(2, 2)*b(2, 2) + a(2, 3)*b(3, 2);
      c(3, 2) = a(3, 0)*b(0, 2) + a(3, 1)*b(1, 2) + a(3, 2)*b(2, 2) + a(3, 3)*b(3, 2);

      c(0, 3) = a(0, 0)*b(0, 3) + a(0, 1)*b(1, 3) + a(0, 2)*b(2, 3) + a(0, 3)*b(3, 3);
      c(1, 3) = a(1, 0)*b(0, 3) + a(1, 1)*b(1, 3) + a(1, 2)*b(2, 3) + a(1, 3)*b(3, 3);
      c(2, 3) = a(2, 0)*b(0, 3) + a(2, 1)*b(1, 3) + a(2, 2)*b(2, 3) + a(2, 3)*b(3, 3);
      c(3, 3) = a(3, 0)*b(0, 3) + a(3, 1)*b(1, 3) + a(3, 2)*b(2, 3) + a(3, 3)*b(3, 3);

      return *this;
    }
  };

  typedef mat4x4<float> mat4x4f;
  typedef mat4x4<double> mat4x4d;
  typedef mat4x4<long double> mat4x4ld;

  template<typename Number>
  mat4x4<Number> operator* (const mat4x4<Number>& a, const mat4x4<Number>& b) {
    return mat4x4<Number>(a) *= b;
  }

  template<typename Number>
  vec4<Number> operator* (const mat4x4<Number>& a, const vec4<Number>& b) {
    return vec4<Number>(
      a(0, 0)*b.x + a(0, 1)*b.y + a(0, 2)*b.z + a(0, 3)*b.w,
      a(1, 0)*b.x + a(1, 1)*b.y + a(1, 2)*b.z + a(1, 3)*b.w,
      a(2, 0)*b.x + a(2, 1)*b.y + a(2, 2)*b.z + a(2, 3)*b.w,
      a(3, 0)*b.x + a(3, 1)*b.y + a(3, 2)*b.z + a(3, 3)*b.w
      );
  }

  template<typename Number>
  vec3<Number> operator* (const mat4x4<Number>& a, const vec3<Number>& b) {
    return vec3<Number>(
      a(0, 0)*b.x + a(0, 1)*b.y + a(0, 2)*b.z + a(0, 3),
      a(1, 0)*b.x + a(1, 1)*b.y + a(1, 2)*b.z + a(1, 3),
      a(2, 0)*b.x + a(2, 1)*b.y + a(2, 2)*b.z + a(2, 3)
      );
  }

  template<typename Number>
  mat4x4<Number>& toIdentity(mat4x4<Number>& m) {
    for (int i = 0; i < 16; ++i) {
      m.m[i] = 0;
    }
    m(0, 0) = m(1, 1) = m(2, 2) = m(3, 3) = 1;
    return m;
  }

  template<typename Number>
  mat4x4<Number>& toScale(
    mat4x4<Number>& m,
    typename mat4x4<Number>::number_t sx,
    typename mat4x4<Number>::number_t sy,
    typename mat4x4<Number>::number_t sz
  ) {
    toIdentity(m);
    m(0, 0) = sx;
    m(1, 1) = sy;
    m(2, 2) = sz;
    return m;
  }

  template<typename Number>
  mat4x4<Number>& toOrthographicProjection(
    mat4x4<Number>& m,
    typename mat4x4<Number>::number_t l, typename mat4x4<Number>::number_t r,
    typename mat4x4<Number>::number_t b, typename mat4x4<Number>::number_t t,
    typename mat4x4<Number>::number_t n, typename mat4x4<Number>::number_t f
  ) {
    toIdentity(m);

    m(0, 0) = 2 / (r - l);
    m(1, 1) = 2 / (b - t);
    m(2, 2) = -2 / (f - n);

    m(0, 3) = -(r + l) / (r - l);
    m(1, 3) = -(t + b) / (b - t);
    m(2, 3) = -(f + n) / (f - n);

    return m;
  }

  template<typename Number>
  mat4x4<Number>& toPerspectiveProjection(
    mat4x4<Number>& m,
    typename mat4x4<Number>::number_t l, typename mat4x4<Number>::number_t r,
    typename mat4x4<Number>::number_t b, typename mat4x4<Number>::number_t t,
    typename mat4x4<Number>::number_t n, typename mat4x4<Number>::number_t f
  ) {
    toIdentity(m);

    float A = (r + l) / (r - l);
    float B = (b + t) / (t - b);
    float C = -(f + n) / (f - n);
    float D = -2 * f*n / (f - n);

    m(0, 0) = 2 * n / (r - l);
    m(1, 1) = 2 * n / (t - b);
    m(0, 2) = A;
    m(1, 2) = B;
    m(2, 2) = C;
    m(2, 3) = D;
    m(3, 2) = -1;
    m(3, 3) = 0;

    return m;
  }

  template<typename Number>
  mat4x4<Number>& toPerspectiveProjection(
    mat4x4<Number>& m,
    typename mat4x4<Number>::number_t fovDegrees,
    typename mat4x4<Number>::number_t aspectRatio,
    typename mat4x4<Number>::number_t zNear, typename mat4x4<Number>::number_t zFar
  ) {
    float yMax = zNear * tanf(fovDegrees * (float)M_PI / 360);
    float xMax = yMax * aspectRatio;
    toPerspectiveProjection(m, -xMax, xMax, -yMax, yMax, zNear, zFar);
    return m;
  }

  template<typename Number>
  mat4x4<Number>& translate(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t x, typename mat4x4<Number>::number_t y, typename mat4x4<Number>::number_t z)
  {
    mat4x4<Number> tm;
    tm(0, 3) = x;
    tm(1, 3) = y;
    tm(2, 3) = z;

    return m *= tm;
  }

  template<typename Number>
  mat4x4<Number>& scale(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t s)
  {
    scale(m, s, s, s);
    return m;
  }

  template<typename Number>
  mat4x4<Number>& scale(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t sx, typename mat4x4<Number>::number_t sy, typename mat4x4<Number>::number_t sz)
  {
    mat4x4<Number> sm;
    sm(0, 0) = sx;
    sm(1, 1) = sy;
    sm(2, 2) = sz;

    return m *= sm;
  }

  template<typename Number>
  mat4x4<Number>& rotateX(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t angle)
  {
    mat4x4<Number> r;
    typename mat4x4<Number>::number_t cosA = cos(angle);
    typename mat4x4<Number>::number_t sinA = sin(angle);

    r(1, 1) = cosA;
    r(1, 2) = -sinA;
    r(2, 1) = sinA;
    r(2, 2) = cosA;

    return m *= r;
  }

  template<typename Number>
  mat4x4<Number>& rotateY(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t angle)
  {
    mat4x4<Number> r;
    typename mat4x4<Number>::number_t cosA = cos(angle);
    typename mat4x4<Number>::number_t sinA = sin(angle);

    r(0, 0) = cosA;
    r(0, 2) = sinA;
    r(2, 0) = -sinA;
    r(2, 2) = cosA;

    return m *= r;
  }

  template<typename Number>
  mat4x4<Number>& rotateZ(
    mat4x4<Number>& m, typename mat4x4<Number>::number_t angle)
  {
    mat4x4<Number> r;
    typename mat4x4<Number>::number_t cosA = cos(angle);
    typename mat4x4<Number>::number_t sinA = sin(angle);

    r(0, 0) = cosA;
    r(0, 1) = -sinA;
    r(1, 0) = sinA;
    r(1, 1) = cosA;

    return m *= r;
  }

  template<typename Number>
  mat4x4<Number>& rotate(
    mat4x4<Number>& m,
    typename mat4x4<Number>::number_t ax, typename mat4x4<Number>::number_t ay, typename mat4x4<Number>::number_t az)
  {
    rotateX(m, ax);
    rotateY(m, ay);
    rotateZ(m, az);
    return m;
  }
}