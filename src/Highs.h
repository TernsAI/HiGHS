#ifndef HIGHS_H_
#define HIGHS_H_

#include "HighsOptions.h"
#include "HighsTimer.h"
#include "HighsLp.h"
#include "HighsStatus.h"
#include "HighsModelBuilder.h"

// Class to set parameters and run HiGHS
class Highs
{
public:
  Highs() {}
  explicit Highs(const HighsOptions &opt) : options_(opt){};

  // The public method run(lp, solution) calls runSolver to solve problem before
  // or after presolve (or crash later?) depending on the specified options.
  HighsStatus run(HighsLp &lp);
  HighsStatus run();

  int HighsAddVariable(double obj=0.0, double lo=0.0, double hi=HIGHS_CONST_INF); // TODO: name

  bool setIntegerOption(const std::string &param, const int value);
  bool setDoubleOption(const std::string &param, const double value);
  bool setStringOption(const std::string &param, const std::string &value);

  bool getIntegerOption(const std::string &param, int &value);
  bool getDoubleOption(const std::string &param, double &value);
  bool getStringOption(const std::string &param, std::string &value);

  // todo: Set warm/hot start methods

  // No getters for LP members because the user has access to the HighsLp.

  // todo: add methods to modify matrix within simplex
  // addRow | add Col | change coeff (int row, int col) | ...
  // ipx (not implemented)

  // todo: getRangingInformation(..)

  double getRowValue(int row);

  double getObjectiveValue();

  HighsSolution getSolution() const { return solution_; }

private:
  HighsSolution solution_;
  // each HighsModelObject holds a const ref to its lp_
  std::vector<HighsModelObject> lps_;

  bool runSuccessful;

  HighsPresolveStatus runPresolve(PresolveInfo &presolve_info);
  HighsPostsolveStatus runPostsolve(PresolveInfo &presolve_info);
  HighsStatus runSolver(HighsModelObject &model);
  HighsTimer timer;

  // Function to call just presolve.
  HighsPresolveStatus presolve(const HighsLp &lp, HighsLp &reduced_lp)
  {
    // todo: implement, from user's side.
    return HighsPresolveStatus::NullError;
  };

  HighsOptions options_;

  HighsModelBuilder builder;
};

#endif