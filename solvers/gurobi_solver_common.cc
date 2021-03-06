/* clang-format off to disable clang-format-includes */
#include "drake/solvers/gurobi_solver.h"
/* clang-format on */

#include <cstdlib>
#include <cstring>

#include "drake/common/never_destroyed.h"
#include "drake/solvers/mathematical_program.h"

// This file contains implementations that are common to both the available and
// unavailable flavor of this class.

namespace drake {
namespace solvers {

GurobiSolver::GurobiSolver()
    : SolverBase(&id, &is_available, &is_enabled,
                 &ProgramAttributesSatisfied) {}

GurobiSolver::~GurobiSolver() = default;

SolverId GurobiSolver::id() {
  static const never_destroyed<SolverId> singleton{"Gurobi"};
  return singleton.access();
}

bool GurobiSolver::is_enabled() {
  const char* grb_license_file = std::getenv("GRB_LICENSE_FILE");
  return ((grb_license_file != nullptr) &&
          (std::strlen(grb_license_file) > 0));
}

bool GurobiSolver::ProgramAttributesSatisfied(const MathematicalProgram& prog) {
  // TODO(hongkai.dai): Gurobi supports callback. Add callback capability.
  static const never_destroyed<ProgramAttributes> solver_capabilities(
      std::initializer_list<ProgramAttribute>{
          ProgramAttribute::kLinearCost, ProgramAttribute::kQuadraticCost,
          ProgramAttribute::kLinearConstraint,
          ProgramAttribute::kLinearEqualityConstraint,
          ProgramAttribute::kLorentzConeConstraint,
          ProgramAttribute::kRotatedLorentzConeConstraint,
          ProgramAttribute::kBinaryVariable});
  return AreRequiredAttributesSupported(prog.required_capabilities(),
                                        solver_capabilities.access());
}
}  // namespace solvers
}  // namespace drake
