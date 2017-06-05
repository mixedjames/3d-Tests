#include "system/test-manager.hpp"

#include "basic-test.hpp"

void InstallTests(TestManager& mgr) {

  mgr.AddTest(std::unique_ptr<Test>(new BasicTest::BasicTest()));

}