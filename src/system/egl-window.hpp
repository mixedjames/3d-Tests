#define GL_GLEXT_PROTOTYPES

#include <jwt/jwt.hpp>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

struct EGLWindow
  : jwt::CustomWindow<EGLWindow>
{
  friend struct jwt::CustomWindow<EGLWindow>;
  static const wchar_t* CLASS_NAME;

  EGLWindow(jwt::Window& parent, const jwt::Dimension& size, std::function<void()> onPaint = nullptr);
  ~EGLWindow();

  static void Register();

  void OnPaint(std::function<void()> onPaint);

protected:
  EGLWindow(const jwt::defer_create_t&);

  void Create(jwt::Window& parent, const jwt::Dimension& size);

  LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);

private:
  HDC dc_;
  EGLDisplay display_;
  EGLConfig config_;
  EGLContext context_;
  EGLSurface surface_;

  std::function<void()> onPaint_;

  void InitGL();
};