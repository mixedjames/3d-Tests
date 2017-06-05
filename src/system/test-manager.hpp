#pragma once

#include <memory>
#include <map>
#include "display.hpp"
#include "test.hpp"

struct TestManager
  : private TestController
{

  TestManager();

  void AddTest(std::unique_ptr<Test>);

private:
  Display display_;
  std::map<std::wstring, std::unique_ptr<Test>> tests_;
  Test* currentTest_;

  void Repaint();
  void OnPaint();
  void TestSelected(const std::wstring& name);
};