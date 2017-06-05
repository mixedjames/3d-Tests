#pragma once

#define GL_GLEXT_PROTOTYPES

#include <memory>
#include <GLES2/gl2.h>
#include "unique-handle.hpp"

namespace hidden {
  inline void glDeleteTextures_adapter(GLuint textureId) {
    glDeleteTextures(1, &textureId);
  }
}

typedef james::unique_handle<GLuint, decltype(glDeleteProgram), glDeleteProgram, 0> UniqueGLProgram;
typedef james::unique_handle<GLuint, decltype(glDeleteShader), glDeleteShader, 0> UniqueGLShader;
typedef james::unique_handle<GLuint, decltype(hidden::glDeleteTextures_adapter), hidden::glDeleteTextures_adapter, 0> UniqueGLTexture;
