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
#include <simulationbase.hpp>

#include <test_dof.hpp>

namespace Dummy
{
  using namespace dealii;
template<int dim, int degree, typename number=double>
class ScratchData
{
  public:
    ScratchData( std::shared_ptr<SimulationBase<dim>> base_in )
    : triangulation(       base_in->triangulation)
    , min_cell_size(       0.0 )
    , mpi_communicator(    base_in->get_mpi_communicator())
    , pcout(               base_in->pcout.get_stream() )
    {
    }
  
    /* unfortunately does not compile because copy constructor of dof_ is deleted; 
     * it would work if the move constructor is explicitly set to default
     *  DoFHandler(DoFHandler&& ) = default;
     *
    void add_component(DoFHandler<dim>&& dof_)
    {
      dof_handler.emplace_back(std::move(dof_));
    }
    
    std::vector<DoFHandler<dim>>               dof_handler; 

    * This way, from the main function add_component could be called, which automatically
    * moves the dof_handler obect to the scratch_data class;
    *
    * ScratchData<dim,degree> scratch_data;
    * scratch_data.add_component(DoFHandler<dim>(triangulation));
     */
    void add_element(TestDoF<dim>&& dof)
    {
      test.emplace_back(std::make_shared<TestDoF<dim>>(std::move(dof)));
    }

    void print_components()
    {
      for (size_t i = 0; i<test.size(); ++i)
        test[i]->print();
    }

    //const Parameters<double>                   parameters;
    //std::shared_ptr<FieldConditions<dim>>      field_conditions;
    //std::shared_ptr<BoundaryConditions<dim>>   boundary_conditions;
    std::shared_ptr<Triangulation<dim>>        triangulation;
    const double                               min_cell_size;     
    const MPI_Comm                             mpi_communicator;
    const ConditionalOStream                   pcout;

    //std::vector<FiniteElement<dim>>            fe;
    //std::vector<const mapping<dim>>                      mapping;
    //std::vector<AffineConstraints<number>>               constraints;
    //std::vector<const QGauss<1>>                               quadrature; 
    std::vector<std::shared_ptr<TestDoF<dim>>>           test; 

    //std::vector<const AffineConstraints<double>*>        constraints_comp; 
    //MatrixFree<dim, double, VectorizedArray<double>>     matrix_free;
};
} // namespace Dummy
