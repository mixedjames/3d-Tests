#include <jwt/jwt.hpp>
#include "test-manager.hpp"

namespace {

  int Start() {
    TestManager mgr;
    return jwt::DefaultPump().Pump();
  }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return Start();
}

int main() {
  return Start();
}