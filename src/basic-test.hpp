#pragma once

#include "system/test.hpp"

namespace BasicTest {

  struct GLData;

  struct BasicTest : Test {
    friend struct GLData;

    BasicTest();

    void Start(TestController&);
    void Stop(TestController&);
    void Paint(TestController&);

    std::wstring Name();
    std::wstring Description();

  private:
    string vShaderSrc_;
    string fShaderSrc_;
    Image texture_;

    unique_ptr<GLData> glData_;
  };

}