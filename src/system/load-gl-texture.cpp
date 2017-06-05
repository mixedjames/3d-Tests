#include "load-gl-texture.hpp"

UniqueGLTexture LoadGLTexture(const james::Image& src) {
  GLuint id;
  glGenTextures(1, &id);

  UniqueGLTexture textureWrapper(id);

  GLenum type = (src.BitsPerPixel() == 32) ? GL_RGBA : GL_RGB;

  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, src.Width(), src.Height(), 0, type, GL_UNSIGNED_BYTE, src.Pixels());

  return textureWrapper;
}