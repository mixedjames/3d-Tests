#pragma once

#include <jwt/jwt.hpp>
#include "egl-window.hpp"

struct Display {

  Display(std::function<void (const std::wstring&)> TestSelected, std::function<void()> Paint);

  void AddTestName(const std::wstring&);
  void SetDescription(const std::wstring&);
  void Repaint();

private:
  std::function<void (const std::wstring&)> TestSelected_;
  std::function<void()> Paint_;

  jwt::AppWindow wnd_;
  jwt::Dialog sidebar_;
  jwt::ListBox tests_;
  jwt::Edit description_;
  EGLWindow display_;
};