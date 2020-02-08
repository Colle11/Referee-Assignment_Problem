#include "RA_Helpers.hh"

using namespace EasyLocal::Debug;

int main(int argc, const char* argv[])
{
  ParameterBox main_parameters("main", "Main Program options");

  // The set of arguments added are the following:  
  Parameter<string> instance("instance", "Input instance", main_parameters); 
  Parameter<int> seed("seed", "Random seed", main_parameters);
  Parameter<string> method("method", "Solution method (empty for tester)", main_parameters);   
  Parameter<string> init_state("init_state", "Initial state (to be read from file)", main_parameters);
  Parameter<string> output_file("output_file", "Write the output to a file (filename required)", main_parameters);
  Parameter<int> loe("loe", "LackOfExperience weight", main_parameters);
  Parameter<int> gd("gd", "GamesDistribution weight", main_parameters);
  Parameter<int> td("td", "TotalDistance weight", main_parameters);
  Parameter<int> o("o", "OptionalReferee weight", main_parameters);
  Parameter<int> af("af", "AssignmentFrequency weight", main_parameters);
  Parameter<int> ri("ri", "RefereeIncompatibility weight", main_parameters);
  Parameter<int> ti("ti", "TeamIncompatibility weight", main_parameters);
 
  // 3rd parameter: false = do not check unregistered parameters
  // 4th parameter: true = silent
  CommandLineParameters::Parse(argc, argv, false, true);  

  if (!instance.IsSet())
  {
    cout << "Error: --main::instance=filename option must always be set" << endl;
    return 1;
  }

  // Input object
  RA_Input in(instance);

  if (seed.IsSet())
    Random::SetSeed(seed);

  // Soft constraints weights
  if (loe.IsSet())
    in.SetLackOfExperienceWeight(loe);

  if (gd.IsSet())
    in.SetGamesDistributionWeight(gd);

  if (td.IsSet())
    in.SetTotalDistanceWeight(td);

  if (o.IsSet())
    in.SetOptionalRefereeWeight(o);

  if (af.IsSet())
    in.SetAssignmentFrequencyWeight(af);

  if (ri.IsSet())
    in.SetRefereeIncompatibilityWeight(ri);

  if (ti.IsSet())
    in.SetTeamIncompatibilityWeight(ti);
  
  // cost components: second parameter is the cost, third is the type (true -> hard, false -> soft)
  MinimumRefereesCostComponent cc1(in, 1, true);
  MaximumRefereesCostComponent cc2(in, 1, true);
  FeasibleTravelDistanceCostComponent cc3(in, 1, true);
  RefereeAvailabilityCostComponent cc4(in, 1, true);
  MinimumLevelCostComponent cc5(in, 1, true);
  LackOfExperienceCostComponent cc6(in, in.LackOfExperienceWeight(), false);
  GamesDistributionCostComponent cc7(in, in.GamesDistributionWeight(), false);
  TotalDistanceCostComponent cc8(in, in.TotalDistanceWeight(), false);
  OptionalRefereeCostComponent cc9(in, in.OptionalRefereeWeight(), false);
  AssignmentFrequencyCostComponent cc10(in, in.AssignmentFrequencyWeight(), false);
  RefereeIncompatibilityCostComponent cc11(in, in.RefereeIncompatibilityWeight(), false);
  TeamIncompatibilityCostComponent cc12(in, in.TeamIncompatibilityWeight(), false);
 
  ChangeAssignedRefereesDeltaMinimumReferees car_dcc_1(in, cc1);
  ChangeAssignedRefereesDeltaMaximumReferees car_dcc_2(in, cc2);
  ChangeAssignedRefereesDeltaFeasibleTravelDistance car_dcc_3(in, cc3);
  ChangeAssignedRefereesDeltaRefereeAvailability car_dcc_4(in, cc4);
  ChangeAssignedRefereesDeltaMinimumLevel car_dcc_5(in, cc5);
  ChangeAssignedRefereesDeltaLackOfExperience car_dcc_6(in, cc6);
  ChangeAssignedRefereesDeltaGamesDistribution car_dcc_7(in, cc7);
  ChangeAssignedRefereesDeltaTotalDistance car_dcc_8(in, cc8);
  ChangeAssignedRefereesDeltaOptionalReferee car_dcc_9(in, cc9);
  ChangeAssignedRefereesDeltaAssignmentFrequency car_dcc_10(in, cc10);
  ChangeAssignedRefereesDeltaRefereeIncompatibility car_dcc_11(in, cc11);
  ChangeAssignedRefereesDeltaTeamIncompatibility car_dcc_12(in, cc12);

  AddRemoveDeltaMinimumReferees arr_dcc1(in, cc1);
  AddRemoveDeltaMaximumReferees arr_dcc2(in, cc2);
  AddRemoveDeltaFeasibleTravelDistance arr_dcc3(in, cc3);
  AddRemoveDeltaRefereeAvailability arr_dcc4(in, cc4);
  AddRemoveDeltaMinimumLevel arr_dcc5(in, cc5);
  AddRemoveDeltaLackOfExperience arr_dcc6(in, cc6);
  AddRemoveDeltaGamesDistribution arr_dcc7(in, cc7);
  AddRemoveDeltaTotalDistance arr_dcc8(in, cc8);
  AddRemoveDeltaOptionalReferee arr_dcc9(in, cc9);
  AddRemoveDeltaAssignmentFrequency arr_dcc10(in, cc10);
  AddRemoveDeltaRefereeIncompatibility arr_dcc11(in, cc11);
  AddRemoveDeltaTeamIncompatibility arr_dcc12(in, cc12);

  // helpers
  RA_StateManager RA_sm(in);
  ChangeAssignedRefereesNeighborhoodExplorer RA_car_nhe(in, RA_sm);
  AddRemoveRefereeNeighborhoodExplorer RA_arr_nhe(in, RA_sm);

  RA_OutputManager RA_om(in);
  
  // All cost components must be added to the state manager
  RA_sm.AddCostComponent(cc1);
  RA_sm.AddCostComponent(cc2);
  RA_sm.AddCostComponent(cc3);
  RA_sm.AddCostComponent(cc4);
  RA_sm.AddCostComponent(cc5);
  RA_sm.AddCostComponent(cc6);
  RA_sm.AddCostComponent(cc7);
  RA_sm.AddCostComponent(cc8);
  RA_sm.AddCostComponent(cc9);
  RA_sm.AddCostComponent(cc10);
  RA_sm.AddCostComponent(cc11);
  RA_sm.AddCostComponent(cc12);
  
  // All delta cost components must be added to the neighborhood explorer
  RA_car_nhe.AddDeltaCostComponent(car_dcc_1);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_2);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_3);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_4);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_5);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_6);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_7);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_8);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_9);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_10);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_11);
  RA_car_nhe.AddDeltaCostComponent(car_dcc_12);

  RA_arr_nhe.AddDeltaCostComponent(arr_dcc1);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc2);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc3);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc4);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc5);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc6);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc7);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc8);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc9);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc10);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc11);
  RA_arr_nhe.AddDeltaCostComponent(arr_dcc12);
  
  // runners
  HillClimbing<RA_Input, RA_State, ChangeAssignedReferees> RA_car_hc(in, RA_sm, RA_car_nhe, "ChangeAssignedReferees_HillClimbing");
  SteepestDescent<RA_Input, RA_State, ChangeAssignedReferees> RA_car_sd(in, RA_sm, RA_car_nhe, "ChangeAssignedReferees_SteepestDescent");
  TabuSearch<RA_Input, RA_State, ChangeAssignedReferees> RA_car_ts(in, RA_sm, RA_car_nhe, "ChangeAssignedReferees_TabuSearch",
    [](const ChangeAssignedReferees& m1, const ChangeAssignedReferees& m2)->bool
      { return m1.game == m2.game && m1.oldAssignedReferees == m2.newAssignedReferees && m1.newAssignedReferees == m2.oldAssignedReferees; });
  SimulatedAnnealing<RA_Input, RA_State, ChangeAssignedReferees> RA_car_sa(in, RA_sm, RA_car_nhe, "ChangeAssignedReferees_SimulatedAnnealing");

  HillClimbing<RA_Input, RA_State, AddRemoveReferee> RA_arr_hc(in, RA_sm, RA_arr_nhe, "AddRemoveReferee_HillClimbing");
  SteepestDescent<RA_Input, RA_State, AddRemoveReferee> RA_arr_sd(in, RA_sm, RA_arr_nhe, "AddRemoveReferee_SteepestDescent");
  TabuSearch<RA_Input, RA_State, AddRemoveReferee> RA_arr_ts(in, RA_sm, RA_arr_nhe, "AddRemoveReferee_TabuSearch",
    [](const AddRemoveReferee& m1, const AddRemoveReferee& m2)->bool
      { return m1.game == m2.game && m1.remReferee == m2.addReferee && m1.addReferee == m2.remReferee; });
  SimulatedAnnealing<RA_Input, RA_State, AddRemoveReferee> RA_arr_sa(in, RA_sm, RA_arr_nhe, "AddRemoveReferee_SimulatedAnnealing");

  // tester
  Tester<RA_Input, RA_Output, RA_State> tester(in,RA_sm,RA_om);
  MoveTester<RA_Input, RA_Output, RA_State, ChangeAssignedReferees> car_swap_move_test(in,RA_sm,RA_om,RA_car_nhe, "ChangeAssignedReferees move", tester); 
  MoveTester<RA_Input, RA_Output, RA_State, AddRemoveReferee> arr_swap_move_test(in,RA_sm,RA_om,RA_arr_nhe, "AddRemoveReferee move", tester);

  // solver
  SimpleLocalSearch<RA_Input, RA_Output, RA_State> RA_solver(in, RA_sm, RA_om, "RA solver");

  if (!CommandLineParameters::Parse(argc, argv, true, false))
    return 1;

  if (!method.IsSet())
  { // If no search method is set -> enter in the tester
    if (init_state.IsSet())
      tester.RunMainMenu(init_state);
    else
      tester.RunMainMenu();
  }
  else
  {
    if (method == string("CAR_SA"))
      RA_solver.SetRunner(RA_car_sa);
    else if (method == string("CAR_TS"))
      RA_solver.SetRunner(RA_car_ts);
    else if (method == string("CAR_HC"))
      RA_solver.SetRunner(RA_car_hc);
    else if (method == string("CAR_SD"))
      RA_solver.SetRunner(RA_car_sd);
    else if (method == string("ARR_SA"))
      RA_solver.SetRunner(RA_arr_sa);
    else if (method == string("ARR_TS"))
      RA_solver.SetRunner(RA_arr_ts);
    else if (method == string("ARR_HC"))
      RA_solver.SetRunner(RA_arr_hc);
    else if (method == string("ARR_SD"))
      RA_solver.SetRunner(RA_arr_sd);
    else
    {
      cerr << "unrecognized method " << string(method) << endl;
      exit(1);
    }

    SolverResult<RA_Input,RA_Output,DefaultCostStructure<int>> result = RA_solver.Solve();
    // result is a tuple: 0: solution, 1: number of violations, 2: total cost, 3: computing time
    RA_Output out = result.output;
    if (output_file.IsSet())
    { // write the output on the file passed in the command line
      ofstream os(static_cast<string>(output_file).c_str());
      os << out << endl;
      os << "Cost: " << result.cost.total << endl;
      os << "Violations: " << result.cost.violations << endl;
			os << "Time: " << result.running_time << "s " << endl;
      os.close();
    }
    else
    { // write the solution in the standard output
      cout << out << endl;
      cout << "Cost: " << result.cost.total << endl;
      cout << "Violations: " << result.cost.violations << endl;
			cout << "Time: " << result.running_time << "s " << endl;					
    }
  }
  return 0;
}
