#include "test-manager.hpp"

void InstallTests(TestManager& mgr);

TestManager::TestManager()
  : display_(
    [this](const std::wstring& name) { return TestSelected(name); },
    [this]() { OnPaint(); }
  ), currentTest_(nullptr)
{
  InstallTests(*this);
}

void TestManager::AddTest(std::unique_ptr<Test> test) {
  Test* testPtr = test.get();

  tests_.insert(
    std::make_pair(test->Name(), std::move(test)
  ));
  display_.AddTestName(testPtr->Name());
}

void TestManager::Repaint() {
  display_.Repaint();
}

void TestManager::OnPaint() {
  if (currentTest_) {
    currentTest_->Paint(*this);
  }
}

void TestManager::TestSelected(const std::wstring& name) {
  auto test = tests_.find(name);

  if (test != tests_.end() && currentTest_ != test->second.get()) {
    if (currentTest_) {
      currentTest_->Stop(*this);
    }

    display_.SetDescription(test->second->Description());
    currentTest_ = test->second.get();
    currentTest_->Start(*this);
  }
}