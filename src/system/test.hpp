#pragma once

#define GL_GLEXT_PROTOTYPES

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <james/image-loader.hpp>
#include <GLES2/gl2.h>

#include "read-text-stream.hpp"
#include "unique-gl-resources.hpp"
#include "load-gl-program.hpp"
#include "load-gl-texture.hpp"
#include "mat4x4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

using namespace james;
using namespace std;

struct TestController {

  TestController() {};

  virtual void Repaint() = 0;

protected:
  virtual ~TestController() {}

private:
  TestController(const TestController&) = delete;
  TestController& operator =(const TestController&) = delete;
};

struct Test {

  virtual void Start(TestController&) = 0;
  virtual void Stop(TestController&) = 0;
  virtual void Paint(TestController&) = 0;

  virtual std::wstring Name() = 0;
  virtual std::wstring Description() = 0;

  virtual ~Test() {}

  Test(const Test&) = delete;
  Test& operator =(const Test&) = delete;

protected:
  Test() {}
};
