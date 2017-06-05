#include "egl-window.hpp"

using namespace jwt;

const wchar_t* EGLWindow::CLASS_NAME = L"EGLWindow_Class";

EGLWindow::EGLWindow(Window& parent, const jwt::Dimension& size, std::function<void()> onPaint)
  : onPaint_(onPaint)
{
  Create(parent, size);
}

EGLWindow::EGLWindow(const defer_create_t&) {
}

EGLWindow::~EGLWindow() {
  if (display_) {
    eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(display_);
  }
}

void EGLWindow::Register() {
  WNDCLASSEX wc = {};

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.lpszClassName = CLASS_NAME;
  wc.style = CS_OWNDC;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

  CustomWindow<EGLWindow>::Register(wc);
}

void EGLWindow::OnPaint(std::function<void()> onPaint) {
  onPaint_ = onPaint;
}

void EGLWindow::Create(Window& parent, const jwt::Dimension& size) {
  Register();

  CreateWindow(
    CLASS_NAME, L"",
    WS_VISIBLE | WS_CHILD,
    0, 0, size.w, size.h,
    parent.TheHWND(), nullptr, GetModuleHandle(nullptr), (void*)this
  );
  DefaultPump().RaiseReportedException();
  assert(hWnd_ != nullptr);
}

LRESULT EGLWindow::WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
  switch (m) {
  case WM_CREATE:
    InitGL();
    break;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    BeginPaint(hWnd_, &ps);
    if (onPaint_) {
      onPaint_();
      eglSwapBuffers(display_, surface_);
    }
    EndPaint(hWnd_, &ps);
    break;
  }

  case WM_ERASEBKGND:
    return true;
  }

  return DefWindowProc(h, m, w, l);
}

void EGLWindow::InitGL() {
  dc_ = GetDC(hWnd_);
  display_ = eglGetDisplay(dc_);

  if (!display_) {
    assert(false);
    throw std::runtime_error("eglGetDisplay failed");
  }

  int maj, min;
  if (!eglInitialize(display_, &maj, &min)) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglInitialize failed");
  }

  if (!eglBindAPI(EGL_OPENGL_ES_API)) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglBindAPI failed");
  }

  EGLint attribs[] =
  {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 0,
    EGL_STENCIL_SIZE, 0,
    EGL_NONE
  };
  EGLint nCfgs = 0;

  if (!eglChooseConfig(display_, attribs, &config_, 1, &nCfgs)) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglChooseConfig failed");
  }

  EGLint attribs2[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
  };

  context_ = eglCreateContext(display_, config_, EGL_NO_CONTEXT, attribs2);
  if (!context_) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglCreateContext failed");
  }

  surface_ = eglCreateWindowSurface(display_, config_, hWnd_, nullptr);
  if (!surface_) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglCreateWindowSurface failed");
  }

  if (!eglMakeCurrent(display_, surface_, surface_, context_)) {
    eglTerminate(display_);
    display_ = nullptr;
    assert(false);
    throw std::runtime_error("eglMakeCurrent failed");
  }

  glClearColor(0, 0, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  eglSwapBuffers(display_, surface_);
}