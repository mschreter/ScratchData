/* ---------------------------------------------------------------------
 *
 * Author: Magdalena Schreter, TUM, September 2020
 *
 * ---------------------------------------------------------------------*/
#pragma once
// for parallelization
#include <deal.II/lac/generic_linear_algebra.h>
// enabling conditional ostreams
#include <deal.II/base/conditional_ostream.h> 
// for index set
#include <deal.II/base/index_set.h>
//// for distributed triangulation
#include <deal.II/distributed/tria_base.h>
// for dof_handler type
#include <deal.II/dofs/dof_handler.h>
// for FE_Q<dim> type
#include <deal.II/fe/fe_q.h>
// for mapping
#include <deal.II/fe/mapping.h>

// MeltPoolDG
#include <test_dof.hpp>
#include <scratch_data.hpp>
#include <simulationbase.hpp>
#include <memory>

namespace Dummy
{
  using namespace dealii; 
 	
  template <int dim, int degree>
  class DummyProblem 
  {

  public:

    DummyProblem( std::shared_ptr<SimulationBase<dim>> base_in )
    : scratch_data(                base_in)
    {
      scratch_data.add_element(TestDoF<dim>());
      scratch_data.add_element(TestDoF<dim>());
      scratch_data.print_components();
    }
    
    ScratchData<dim, degree, double> scratch_data;
    
  };
} // namespace
