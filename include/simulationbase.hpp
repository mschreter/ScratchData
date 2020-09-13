#pragma once
// dealii
#include <deal.II/distributed/tria.h>
// MeltPoolDG
//#include <meltpooldg/interface/parameters.hpp>
//#include <meltpooldg/interface/boundaryconditions.hpp>
//#include <meltpooldg/interface/fieldconditions.hpp>
// c++
//
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
#include <memory>

namespace Dummy
{
    using namespace dealii;

    template <int dim>
    class SimulationBase
    {
      public:
        
        //virtual void set_mpi_commun() = 0;
        SimulationBase(MPI_Comm my_communicator)
        : mpi_communicator(my_communicator)
        , pcout(std::cout, Utilities::MPI::this_mpi_process(mpi_communicator) == 0 )
        {
        }

        virtual ~SimulationBase() = default;

        virtual void set_parameters() = 0;
        
        virtual void set_boundary_conditions() = 0;
        
        virtual void set_field_conditions() = 0;

        virtual void create_spatial_discretization() = 0;

        virtual void create()
        { 
          create_spatial_discretization();
          set_boundary_conditions();
          set_field_conditions();
        };

        // getter functions
        
        virtual MPI_Comm get_mpi_communicator() const { return this->mpi_communicator; };
        
        //std::shared_ptr<FieldConditions<dim>>     get_field_conditions() const { return std::make_shared<FieldConditions<dim>>(this->field_conditions); }
        
        //std::shared_ptr<BoundaryConditions<dim>>  get_boundary_conditions() const { return std::make_shared<BoundaryConditions<dim>>(this->boundary_conditions); }

        const MPI_Comm                            mpi_communicator;
        std::shared_ptr<Triangulation<dim>>       triangulation; 
        //Parameters<double>                        parameters;
        const dealii::ConditionalOStream          pcout;
      //protected:
        //FieldConditions<dim>                      field_conditions;
        //BoundaryConditions<dim>                   boundary_conditions;
    };
} // namespace MeltPoolDG
