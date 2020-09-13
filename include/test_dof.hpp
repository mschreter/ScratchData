#pragma once
#include <iostream>

namespace Dummy
{

template<int dim>
class TestDoF
{
  public:
  TestDoF()
  {
    std::cout << "TestDoF created" << std::endl;
  }

  TestDoF(TestDoF&& ) = default;
  TestDoF(const TestDoF& ) = delete;

  TestDoF &operator=(const TestDoF&) = delete;

  void print() const
  {
    std::cout << "hello from test dof" << std::endl;
  }

};

} // namespace MeltPoolDG
