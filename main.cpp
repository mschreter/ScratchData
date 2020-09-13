#include <simulationbase.hpp>
#include <dummy_problem.hpp>

namespace Dummy
{
  using namespace dealii;
template<int dim>
class Simulation : public SimulationBase<dim>
{
public:
  Simulation() 
    : SimulationBase<dim>(MPI_COMM_WORLD)
  {
    set_parameters();
  }
  
  void set_parameters()
  {
  }

  void create_spatial_discretization()
  {
  }
  void set_boundary_conditions()
  {
  }

  void set_field_conditions()
  {   
  }
};
}
int main(int argc, char* argv[])
{
  using namespace dealii;
  using namespace Dummy;

  Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv, 1);
  auto sim = std::make_shared<Dummy::Simulation<1>>();
   std::make_shared<Dummy::DummyProblem<1,1>>(sim);
  return 0;
}
