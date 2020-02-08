// File RA_Helpers.hh
#ifndef RA_HELPERS_HH
#define RA_HELPERS_HH

#include "RA_Basics.hh"
#include <easylocal.hh>

using namespace EasyLocal::Core;

/***************************************************************************
 * State Manager 
 ***************************************************************************/

class MinimumRefereesCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  MinimumRefereesCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"MinimumRefereesCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class MaximumRefereesCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  MaximumRefereesCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"MaximumRefereesCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class FeasibleTravelDistanceCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  FeasibleTravelDistanceCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"FeasibleTravelDistanceCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class RefereeAvailabilityCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  RefereeAvailabilityCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"RefereeAvailabilityCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class MinimumLevelCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  MinimumLevelCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"MinimumLevelCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class LackOfExperienceCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  LackOfExperienceCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"LackOfExperienceCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class GamesDistributionCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  GamesDistributionCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"GamesDistributionCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class TotalDistanceCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  TotalDistanceCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"TotalDistanceCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class OptionalRefereeCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  OptionalRefereeCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"OptionalRefereeCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class AssignmentFrequencyCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  AssignmentFrequencyCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"AssignmentFrequencyCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class RefereeIncompatibilityCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  RefereeIncompatibilityCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"RefereeIncompatibilityCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class TeamIncompatibilityCostComponent : public CostComponent<RA_Input,RA_State> 
{
public:
  TeamIncompatibilityCostComponent(const RA_Input & in, int w, bool hard) : CostComponent<RA_Input,RA_State>(in,w,hard,"TeamIncompatibilityCostComponent") 
  {}
  int ComputeCost(const RA_State& st) const;
  void PrintViolations(const RA_State& st, ostream& os = cout) const;
};

class RA_StateManager : public StateManager<RA_Input,RA_State> 
{
public:
  RA_StateManager(const RA_Input &);
  void RandomState(RA_State&);   
  void GreedyState(RA_State&);
  bool CheckConsistency(const RA_State& st) const;
}; 

/***************************************************************************
 * ChangeAssignedReferees Neighborhood Explorer:
 ***************************************************************************/

class ChangeAssignedRefereesDeltaMinimumReferees
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaMinimumReferees(const RA_Input & in, MinimumRefereesCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaMinimumReferees") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaMaximumReferees
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaMaximumReferees(const RA_Input & in, MaximumRefereesCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaMaximumReferees") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaFeasibleTravelDistance
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaFeasibleTravelDistance(const RA_Input & in, FeasibleTravelDistanceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaFeasibleTravelDistance") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaRefereeAvailability
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaRefereeAvailability(const RA_Input & in, RefereeAvailabilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaRefereeAvailability") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaMinimumLevel
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaMinimumLevel(const RA_Input & in, MinimumLevelCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaMinimumLevel") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaLackOfExperience
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaLackOfExperience(const RA_Input & in, LackOfExperienceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaLackOfExperience") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaGamesDistribution
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaGamesDistribution(const RA_Input & in, GamesDistributionCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaGamesDistribution") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaTotalDistance
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaTotalDistance(const RA_Input & in, TotalDistanceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaTotalDistance") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaOptionalReferee
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaOptionalReferee(const RA_Input & in, OptionalRefereeCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaOptionalReferee") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaAssignmentFrequency
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaAssignmentFrequency(const RA_Input & in, AssignmentFrequencyCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaAssignmentFrequency") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaRefereeIncompatibility
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaRefereeIncompatibility(const RA_Input & in, RefereeIncompatibilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaRefereeIncompatibility") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesDeltaTeamIncompatibility
  : public DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>
{
public:
  ChangeAssignedRefereesDeltaTeamIncompatibility(const RA_Input & in, TeamIncompatibilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,ChangeAssignedReferees>(in,cc,"ChangeAssignedRefereesDeltaTeamIncompatibility") 
  {}
  int ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const;
};

class ChangeAssignedRefereesNeighborhoodExplorer
  : public NeighborhoodExplorer<RA_Input,RA_State,ChangeAssignedReferees> 
{
public:
  ChangeAssignedRefereesNeighborhoodExplorer(const RA_Input & pin, StateManager<RA_Input,RA_State>& psm)  
    : NeighborhoodExplorer<RA_Input,RA_State,ChangeAssignedReferees>(pin, psm, "ChangeAssignedRefereesNeighborhoodExplorer") {} 
  void RandomMove(const RA_State&, ChangeAssignedReferees&) const;          
  bool FeasibleMove(const RA_State&, const ChangeAssignedReferees&) const;  
  void MakeMove(RA_State&, const ChangeAssignedReferees&) const;             
  void FirstMove(const RA_State&, ChangeAssignedReferees&) const;  
  bool NextMove(const RA_State&, ChangeAssignedReferees&) const;   
  bool AnyNextMove(const RA_State&, ChangeAssignedReferees&) const;
};

/***************************************************************************
 * AddRemoveReferee Neighborhood Explorer:
 ***************************************************************************/

class AddRemoveDeltaMinimumReferees
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaMinimumReferees(const RA_Input & in, MinimumRefereesCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaMinimumReferees") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaMaximumReferees
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaMaximumReferees(const RA_Input & in, MaximumRefereesCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaMaximumReferees") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaFeasibleTravelDistance
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaFeasibleTravelDistance(const RA_Input & in, FeasibleTravelDistanceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaFeasibleTravelDistance") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaRefereeAvailability
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaRefereeAvailability(const RA_Input & in, RefereeAvailabilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaRefereeAvailability") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaMinimumLevel
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaMinimumLevel(const RA_Input & in, MinimumLevelCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaMinimumLevel") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaLackOfExperience
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaLackOfExperience(const RA_Input & in, LackOfExperienceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaLackOfExperience") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaGamesDistribution
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaGamesDistribution(const RA_Input & in, GamesDistributionCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaGamesDistribution") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaTotalDistance
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaTotalDistance(const RA_Input & in, TotalDistanceCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaTotalDistance") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaOptionalReferee
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaOptionalReferee(const RA_Input & in, OptionalRefereeCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaOptionalReferee") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaAssignmentFrequency
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaAssignmentFrequency(const RA_Input & in, AssignmentFrequencyCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaAssignmentFrequency") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaRefereeIncompatibility
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaRefereeIncompatibility(const RA_Input & in, RefereeIncompatibilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaRefereeIncompatibility") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveDeltaTeamIncompatibility
  : public DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>
{
public:
  AddRemoveDeltaTeamIncompatibility(const RA_Input & in, TeamIncompatibilityCostComponent& cc) 
    : DeltaCostComponent<RA_Input,RA_State,AddRemoveReferee>(in,cc,"AddRemoveDeltaTeamIncompatibility") 
  {}
  int ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const;
};

class AddRemoveRefereeNeighborhoodExplorer
  : public NeighborhoodExplorer<RA_Input,RA_State,AddRemoveReferee> 
{
public:
  AddRemoveRefereeNeighborhoodExplorer(const RA_Input & pin, StateManager<RA_Input,RA_State>& psm)  
    : NeighborhoodExplorer<RA_Input,RA_State,AddRemoveReferee>(pin, psm, "AddRemoveRefereeNeighborhoodExplorer") {} 
  void RandomMove(const RA_State&, AddRemoveReferee&) const;          
  bool FeasibleMove(const RA_State&, const AddRemoveReferee&) const;  
  void MakeMove(RA_State&, const AddRemoveReferee&) const;             
  void FirstMove(const RA_State&, AddRemoveReferee&) const;  
  bool NextMove(const RA_State&, AddRemoveReferee&) const;   
  bool AnyNextMove(const RA_State&, AddRemoveReferee&) const;
};

/***************************************************************************
 * Output Manager:
 ***************************************************************************/
class RA_OutputManager
  : public OutputManager<RA_Input,RA_Output,RA_State> 
{
public:
  RA_OutputManager(const RA_Input & pin)
    : OutputManager<RA_Input,RA_Output,RA_State>(pin,"RAOutputManager") {}
  void InputState(RA_State&, const RA_Output&) const;  
  void OutputState(const RA_State&, RA_Output&) const; 
}; 

/***************************************************************************
 * Delta Cost Support Functions:
 ***************************************************************************/
int MinimumRefereesDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int MaximumRefereesDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int FeasibleTravelDistanceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int RefereeAvailabilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int MinimumLevelDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int LackOfExperienceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int GamesDistributionDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int TotalDistanceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int OptionalRefereeDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int AssignmentFrequencyDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int RefereeIncompatibilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int TeamIncompatibilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
#endif
