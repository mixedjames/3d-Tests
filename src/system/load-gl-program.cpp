#include "load-gl-program.hpp"
#include "read-text-stream.hpp"
#include <assert.h>

using namespace std;

namespace {

  void CheckShaderCompilation(GLuint shader) {
    GLint ok;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
      assert(false);
      throw runtime_error("Shader failed to compile");
    }
  }
}

UniqueGLProgram LoadGLProgram(std::istream& vShaderSource, std::istream& fShaderSource) {
  string vShaderCode = ReadTextStream(vShaderSource);
  string fShaderCode = ReadTextStream(fShaderSource);

  return LoadGLProgram(vShaderCode, fShaderCode);
}

UniqueGLProgram LoadGLProgram(const std::string& vShaderSource, const std::string& fShaderSource) {

  UniqueGLShader vShader(glCreateShader(GL_VERTEX_SHADER));
  UniqueGLShader fShader(glCreateShader(GL_FRAGMENT_SHADER));
  UniqueGLProgram program(glCreateProgram());

  if (!vShader || !fShader || !program) {
    throw runtime_error("Failed to create shader objects.");
  }

  const GLchar* const strings[] = { vShaderSource.c_str(), fShaderSource.c_str() };
  const GLint lengths[] = { (GLint)vShaderSource.size(), (GLint)fShaderSource.size() };

  glShaderSource(vShader.get(), 1, &strings[0], &lengths[0]);
  glShaderSource(fShader.get(), 1, &strings[1], &lengths[1]);

  glCompileShader(vShader.get());
  CheckShaderCompilation(vShader.get());

  glCompileShader(fShader.get());
  CheckShaderCompilation(fShader.get());

  glAttachShader(program.get(), vShader.get());
  glAttachShader(program.get(), fShader.get());
  glLinkProgram(program.get());

  vShader.release();
  fShader.release();

  return program;
}