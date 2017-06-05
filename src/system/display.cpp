#include "display.hpp"
#include "resources.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
  name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace jwt;

Display::Display(std::function<void(const std::wstring&)> TestSelected, std::function<void()> Paint)
  : TestSelected_(TestSelected), Paint_(Paint),
    sidebar_(wnd_, IDD_SIDEBAR), tests_(sidebar_, IDC_TESTLIST), description_(sidebar_, IDC_TESTDESCRIPTION),
    display_(wnd_, Dimension(600, 600))
{
  RemoveStyle(wnd_, WS_MAXIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);
  wnd_.On(Close, []() { PostQuitMessage(0); });

  SetClientSize(wnd_, Dimension(
    GetSize(display_).w + GetSize(sidebar_).w,
    GetSize(display_).h
  ));
  SetPosition(display_, Point(GetSize(sidebar_).w, 0));
  SetSize(sidebar_, Dimension(
    GetSize(sidebar_).w,
    GetClientSize(wnd_).h
  ));

  tests_.On(Change, [this]() {
    int i = SelectedIndex(tests_);

    if (i >= 0) {
      TestSelected_(GetString(tests_, i));
    }
  });

  display_.OnPaint([this]() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (Paint_) {
      Paint_();
    }
  });

  SetVisible(wnd_, true);
}

void Display::AddTestName(const std::wstring& name) {
  AddString(tests_, name);
}

void Display::SetDescription(const std::wstring& txt) {
  SetText(description_, txt);
}

void Display::Repaint() {
  InvalidateRect(display_.TheHWND(), nullptr, false);
  UpdateWindow(display_.TheHWND());
}