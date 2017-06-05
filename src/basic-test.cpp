#include "basic-test.hpp"
#include <iostream>

using namespace std;

namespace BasicTest {

  namespace {
    float f = 0.5f;

    float mesh[] = {
      -1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f,-1.0f, 1.0f,
      1.0f,-1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f,-1.0f,
      1.0f,-1.0f,-1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f,-1.0f,
      -1.0f, 1.0f,-1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f,-1.0f, 1.0f
    };

    float uv[] = {
      0, 0,
      0, 1,
      1, 1,

      0, 0,
      1, 1,
      1, 0
    };
  }

  struct GLData {
    UniqueGLProgram shader_;
    UniqueGLTexture texture_;

    GLint mvMatrixIndex;
    GLint pMatrixIndex;
    GLint srcPositionIndex;
    GLint srcUVIndex;
    GLint textureIndex;

    GLData(BasicTest& self)
    {
      glViewport(0, 0, 600, 600);
      glActiveTexture(GL_TEXTURE0);

      shader_ = UniqueGLProgram(LoadGLProgram(self.vShaderSrc_, self.fShaderSrc_));
      texture_ = UniqueGLTexture(LoadGLTexture(self.texture_));

      mvMatrixIndex = glGetUniformLocation(shader_.get(), "mv");
      pMatrixIndex = glGetUniformLocation(shader_.get(), "p");

      srcPositionIndex = glGetAttribLocation(shader_.get(), "srcPosition");
      srcUVIndex = glGetAttribLocation(shader_.get(), "srcUV");

      textureIndex = glGetUniformLocation(shader_.get(), "texture");

      assert(
        mvMatrixIndex != -1 && pMatrixIndex != -1
        && srcPositionIndex != -1 && srcUVIndex != -1
        && textureIndex != -1
      );
    }
  };

  BasicTest::BasicTest()
    : texture_(LoadJPEG(ifstream("res/wooden-box.jpg", std::ios::binary))),
      vShaderSrc_(ReadTextStream(ifstream("res/simple-v-shader.shader"))),
      fShaderSrc_(ReadTextStream(ifstream("res/simple-f-shader.shader")))
  {
  }

  void BasicTest::Start(TestController& c) {
    glData_ = unique_ptr<GLData>(new GLData(*this));
    c.Repaint();
  }

  void BasicTest::Stop(TestController&) {
    glData_ = nullptr;
  }

  void BasicTest::Paint(TestController&) {

    glClearColor(0, 0, 0.5f, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4f mv, p;
    toIdentity(mv);
    toIdentity(p);

    toPerspectiveProjection(p, 60 * 3.141568 / 180, 1, 1, 100);

    rotateX(mv, 45 * 3.141568 / 180);
    translate(mv, 0, 0, 50);
    scale(mv, 0.5f, 0.5f, -1);

    glUseProgram(glData_->shader_.get());
    glActiveTexture(GL_TEXTURE0);

    glUniformMatrix4fv(glData_->mvMatrixIndex, 1, GL_FALSE, mv.m);
    glUniformMatrix4fv(glData_->pMatrixIndex, 1, GL_FALSE, p.m);
    glUniform1i(glData_->textureIndex, 0);

    glVertexAttribPointer(glData_->srcPositionIndex, 3, GL_FLOAT, GL_FALSE, 0, mesh);
    glEnableVertexAttribArray(glData_->srcPositionIndex);

    glVertexAttribPointer(glData_->srcUVIndex, 2, GL_FLOAT, GL_FALSE, 0, uv);
    glEnableVertexAttribArray(glData_->srcUVIndex);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(mesh)/sizeof(float));
  }

  std::wstring BasicTest::Name() {
    return L"Basic Test";
  }

  std::wstring BasicTest::Description() {
    return L"Draws a cube, nicely textured with a wooden box image. "
            "Nothing more, nothing less.";
  }
}