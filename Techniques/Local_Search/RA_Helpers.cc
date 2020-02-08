// File RA_Helpers.cc
#include "RA_Helpers.hh"
#include "RA_Greedy.hh"
#include <algorithm>
#include <math.h>
#include <iterator>
#include <vector>

#ifdef RA_GREEDY_HH
#define RA_GREEDY true
#else
#define RA_GREEDY false
#endif

int MinimumRefereesCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (!st.HasMinimumReferees(g))
      cost++;
  }

  return cost;
}
          
void MinimumRefereesCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (!st.HasMinimumReferees(g))
      os << "Game " << g << " does not have the minimum number of mandatory referees" << endl;
  }
}

int MaximumRefereesCostComponent::ComputeCost(const RA_State& st) const
{ 
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (!st.LeqThanMaximumReferees(g))
      cost++;
  }

  return cost;
}
 
void MaximumRefereesCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (!st.LeqThanMaximumReferees(g))
      os << "Game " << g << " has a number of referees greater than the maximum allowed" << endl;
  }
}

int FeasibleTravelDistanceCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.FeasibleTravelDistance(r))
      cost++;
  }

  return cost;
}

void FeasibleTravelDistanceCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.FeasibleTravelDistance(r))
      os << "Referee " << r << " does not have a feasible travel distance" << endl;
  }
}

int RefereeAvailabilityCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.RefereeAvailability(r))
      cost++;
  }

  return cost;
}

void RefereeAvailabilityCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.RefereeAvailability(r))
      os << "Referee " << r << " is assigned to a game when she/he is not available" << endl;
  }
}

int MinimumLevelCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.HasMinimumLevel(r))
      cost++;
  }

  return cost;
}

void MinimumLevelCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
  {
    if (!st.HasMinimumLevel(r))
      os << "Referee " << r << " is assigned to a game for which she/he does not have the minimum level required" << endl;
  }
}

int LackOfExperienceCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (st.LackOfExperience(g))
      cost++;
  }

  return cost;
}

void LackOfExperienceCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
  {
    if (st.LackOfExperience(g))
      os << "Game " << g << " does not have the requested experience" << endl;
  }
}

int GamesDistributionCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
    cost += st.GamesDistribution(r);

  return cost;
}

void GamesDistributionCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
    os << "The difference between the number of games assigned to the referee " << r << " and the average value is " << st.GamesDistribution(r) << endl;
}

int TotalDistanceCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
    cost += st.TotalDistance(r);

  return cost;
}

void TotalDistanceCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
    os << "The total travelling distance of referee " << r << " is " << st.TotalDistance(r) << endl;
}

int OptionalRefereeCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
    cost += st.OptionalReferee(g);

  return cost;
}

void OptionalRefereeCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
    os << "The number of absent optional referees in the game " << g << " is " << st.OptionalReferee(g) << endl;
}

int AssignmentFrequencyCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int r = 1; r <= in.NumReferees(); r++)
    for (int t = 1; t <= in.NumTeams(); t++)
      cost += st.AssignmentFrequency(r, t);

  return cost;
}

void AssignmentFrequencyCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int r = 1; r <= in.NumReferees(); r++)
    for (int t = 1; t <= in.NumTeams(); t++)
      os << "The difference between the number of times the referee " << r << " has been assigned to the team " << t << " and the average value is " << st.AssignmentFrequency(r, t) << endl;
}

int RefereeIncompatibilityCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
    cost += st.RefereeIncompatibility(g);

  return cost;
}

void RefereeIncompatibilityCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
    os << "The number of incompatible referees in the game " << g << " is " << st.RefereeIncompatibility(g) << endl;
}

int TeamIncompatibilityCostComponent::ComputeCost(const RA_State& st) const
{
  int cost = 0;

  for (int g = 1; g <= in.NumGames(); g++)
    cost += st.TeamIncompatibility(g);

  return cost;
}

void TeamIncompatibilityCostComponent::PrintViolations(const RA_State& st, ostream& os) const
{
  for (int g = 1; g <= in.NumGames(); g++)
    os << "The number of incompatibilities between teams and referees in the game " << g << " is " << st.TeamIncompatibility(g) << endl;
}

// constructor
RA_StateManager::RA_StateManager(const RA_Input & pin) 
  : StateManager<RA_Input,RA_State>(pin, "RAStateManager")  {} 

// initial state builder (random referees assignment for each game)
/* A random state is generated trying to guarantee that the minimum number of referees is
   assigned to each game. As for the other hard constraints, they must all be satisfied.
*/
void RA_StateManager::RandomState(RA_State& st) 
{
  set<int> referees, diffReferees;
  vector<int> games;
  int numAssignedReferees, refereePosition, optionalReferees;
  set<int>::iterator it;
  set<int>::iterator abeg;
  set<int>::iterator aend;
  set<int>::iterator rbeg;
  set<int>::iterator rend;

  for (int g = 1; g <= in.NumGames(); g++)
    games.push_back(g);

  random_shuffle(games.begin(), games.end());

  st.Reset();
  for (int step = 0; step <= 1; step++)
    for (int g : games)
    {
      for (int r = 1; r <= in.NumReferees(); r++)
        referees.insert(r);

      const Division &division = in.GetDivision(in.GetGame(g).Division());

      if (step)
      {
        optionalReferees = division.MaxReferees() - division.MinReferees();
        numAssignedReferees = Random::Uniform<int>(0, optionalReferees);
        abeg = st.AssignedReferees(g).begin();
        aend = st.AssignedReferees(g).end();
        rbeg = referees.begin();
        rend = referees.end();
        set_difference(make_move_iterator(rbeg), make_move_iterator(rend), abeg, aend, inserter(diffReferees, diffReferees.end()));
        referees.swap(diffReferees);
      }
      else
        numAssignedReferees = division.MinReferees();

      for (int i = 0; i < numAssignedReferees; i++)
      {
        if (referees.empty())
          break;

        refereePosition = Random::Uniform<int>(0, referees.size() - 1);
        it = referees.begin();
        advance(it, refereePosition);
        st.Assign(*it, g);

        if (!st.FeasibleTravelDistance(*it) || !st.RefereeAvailability(*it) || !st.HasMinimumLevel(*it))
        {
          st.Unassign(*it, g);
          i--;
        }

        referees.erase(it);
      }
    }
} 

void RA_StateManager::GreedyState(RA_State& st)
{
  if (RA_GREEDY)
    GreedyRASolver(in, st);
  else
    throw logic_error("RA_StateManager::GreedyState not included");
}

bool RA_StateManager::CheckConsistency(const RA_State& st) const
{
  int game, referee;
  set<int>::iterator itf;

  for (int g = 1; g <= in.NumGames(); g++)
  {
    for (set<int>::iterator it = st.AssignedReferees(g).begin(); it != st.AssignedReferees(g).end(); ++it)
    {
      referee = in.GetReferee(*it).Code();
      itf = st.AssignedGames(referee).find(g);

      if (itf == st.AssignedGames(referee).end())
        return false;
    }
  }

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    for (set<int>::iterator it = st.AssignedGames(r).begin(); it != st.AssignedGames(r).end(); ++it)
    {
      game = *it;
      itf = st.AssignedReferees(game).find(r);

      if (itf == st.AssignedReferees(game).end())
        return false;
    }
  }

  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void RA_OutputManager::InputState(RA_State& st, const RA_Output& out) const 
{
  st.Reset();

  for (int g = 1; g <= in.NumGames(); g++)
  {
    for (set<int>::iterator it = out.AssignedReferees(g).begin(); it != out.AssignedReferees(g).end(); ++it)
      st.Assign(in.GetReferee(*it).Code(), g);
  }
}

void RA_OutputManager::OutputState(const RA_State& st, RA_Output& out) const 
{
  out.Reset();

  for (int g = 1; g <= in.NumGames(); g++)
  {
    for (set<int>::iterator it = st.AssignedReferees(g).begin(); it != st.AssignedReferees(g).end(); ++it)
      out.Assign(in.GetReferee(*it).Code(), g);
  }
}


/*****************************************************************************
 * ChangeAssignedReferees Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void ChangeAssignedRefereesNeighborhoodExplorer::RandomMove(const RA_State& st, ChangeAssignedReferees& mv) const
{
  set<int> referees;
  int numAssignedReferees;
  int refereePosition;
  set<int>::iterator it;

  do
  {
    mv.game = Random::Uniform<int>(1, in.NumGames());
    mv.oldAssignedReferees = st.AssignedReferees(mv.game);

    for (int r = 1; r <= in.NumReferees(); r++)
      referees.insert(r);

    mv.newAssignedReferees.clear();
    const Division &division = in.GetDivision(in.GetGame(mv.game).Division());
    numAssignedReferees = Random::Uniform<int>(division.MinReferees(), division.MaxReferees());
    for (int i = 0; i < numAssignedReferees; i++)
    {
      refereePosition = Random::Uniform<int>(0, referees.size() - 1);
      it = referees.begin();
      advance(it, refereePosition);
      mv.newAssignedReferees.insert(*it);
      referees.erase(it);
    }
  } while (!FeasibleMove(st, mv));
} 

// check move feasibility
bool ChangeAssignedRefereesNeighborhoodExplorer::FeasibleMove(const RA_State& st, const ChangeAssignedReferees& mv) const
{
	if (mv.oldAssignedReferees == mv.newAssignedReferees)
		return false;

  if (st.AssignedReferees(mv.game) != mv.oldAssignedReferees)
    return false;

  if (MinimumRefereesDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees) > 0)
    return false;

  if (MaximumRefereesDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees) > 0)
    return false;

  if (FeasibleTravelDistanceDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees) > 0)
    return false;

  if (RefereeAvailabilityDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees) > 0)
    return false;

  if (MinimumLevelDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees) > 0)
    return false;

  return true;
} 

// update the state according to the move 
void ChangeAssignedRefereesNeighborhoodExplorer::MakeMove(RA_State& st, const ChangeAssignedReferees& mv) const
{
  st.UnassignAll(mv.game);

  for (set<int>::iterator it = mv.newAssignedReferees.begin(); it != mv.newAssignedReferees.end(); ++it)
    st.Assign(in.GetReferee(*it).Code(), mv.game);
}  

void ChangeAssignedRefereesNeighborhoodExplorer::FirstMove(const RA_State& st, ChangeAssignedReferees& mv) const
{
  // mv.game = Random::Uniform<int>(1, in.NumGames());
  mv.game = 1;

  const Division &division = in.GetDivision(in.GetGame(mv.game).Division());

  mv.oldAssignedReferees.clear();

  for (set<int>::iterator it = st.AssignedReferees(mv.game).begin(); it != st.AssignedReferees(mv.game).end(); ++it)
    mv.oldAssignedReferees.insert(in.GetReferee(*it).Code());

  mv.newAssignedReferees.clear();

  for (int r = 1; r <= division.MinReferees(); r++)
    mv.newAssignedReferees.insert(r);

  if (mv.oldAssignedReferees == mv.newAssignedReferees)
		NextMove(st, mv);
}

bool ChangeAssignedRefereesNeighborhoodExplorer::NextMove(const RA_State& st, ChangeAssignedReferees& mv) const
{
  do
    if (!AnyNextMove(st, mv))
      return false;
  while (!FeasibleMove(st, mv));

  return true;
}

bool ChangeAssignedRefereesNeighborhoodExplorer::AnyNextMove(const RA_State& st, ChangeAssignedReferees& mv) const
{
  const Division &division = in.GetDivision(in.GetGame(mv.game).Division());
  set<int>::reverse_iterator rit;
  vector<int> removeReferees;
  int referee;

  for (rit = mv.newAssignedReferees.rbegin(); rit != mv.newAssignedReferees.rend(); ++rit)
  {
    referee = in.GetReferee(*rit).Code();

    if (referee == in.NumReferees() - static_cast<int>(removeReferees.size()))
      removeReferees.push_back(referee);
    else
      break;
  }

  if (static_cast<int>(removeReferees.size()) == division.MaxReferees())
  {
    if (mv.game == in.NumGames())
      return false;
    else
    {
      mv.game++;

      const Division &div = in.GetDivision(in.GetGame(mv.game).Division());

      mv.oldAssignedReferees.clear();

      for (set<int>::iterator it = st.AssignedReferees(mv.game).begin(); it != st.AssignedReferees(mv.game).end(); ++it)
        mv.oldAssignedReferees.insert(in.GetReferee(*it).Code());

      mv.newAssignedReferees.clear();

      for (int r = 1; r <= div.MinReferees(); r++)
        mv.newAssignedReferees.insert(r);

      return true;
    }
  }

  for (int r : removeReferees)
    mv.newAssignedReferees.erase(r);

  if (mv.newAssignedReferees.empty())
  {
    for (int r = 1; r <= static_cast<int>(removeReferees.size()) + 1; r++)
      mv.newAssignedReferees.insert(r);
  }
  else
  {
    rit = mv.newAssignedReferees.rbegin();
    referee = in.GetReferee(*rit).Code();
    mv.newAssignedReferees.erase(referee);
    referee++;
    mv.newAssignedReferees.insert(referee);

    for (int i = 0; i < static_cast<int>(removeReferees.size()); i++)
    {
      referee++;
      mv.newAssignedReferees.insert(referee);
    }
  }

  return true;
}

int ChangeAssignedRefereesDeltaMinimumReferees::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return MinimumRefereesDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}
          
int ChangeAssignedRefereesDeltaMaximumReferees::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return MaximumRefereesDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaFeasibleTravelDistance::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return FeasibleTravelDistanceDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaRefereeAvailability::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return RefereeAvailabilityDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaMinimumLevel::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return MinimumLevelDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaLackOfExperience::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return LackOfExperienceDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaGamesDistribution::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return GamesDistributionDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaTotalDistance::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return TotalDistanceDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaOptionalReferee::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return OptionalRefereeDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaAssignmentFrequency::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return AssignmentFrequencyDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaRefereeIncompatibility::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return RefereeIncompatibilityDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

int ChangeAssignedRefereesDeltaTeamIncompatibility::ComputeDeltaCost(const RA_State& st, const ChangeAssignedReferees& mv) const
{
  return TeamIncompatibilityDeltaCost(in, st, mv.game, mv.oldAssignedReferees, mv.newAssignedReferees);
}

/*****************************************************************************
 * AddRemoveReferee Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void AddRemoveRefereeNeighborhoodExplorer::RandomMove(const RA_State& st, AddRemoveReferee& mv) const
{
  set<int> removableReferees;
  set<int>::iterator it;
  int refereePosition;
  int referee;

  do
  {
    mv.game = Random::Uniform<int>(1, in.NumGames());

    removableReferees = st.AssignedReferees(mv.game);
    removableReferees.insert(0);
    refereePosition = Random::Uniform<int>(0, removableReferees.size() - 1);
    it = removableReferees.begin();
    advance(it, refereePosition);
    mv.remReferee = *it;

    do
      referee = Random::Uniform<int>(0, in.NumReferees());
    while (st.AssignedReferees(mv.game).find(referee) != st.AssignedReferees(mv.game).end());
    
    mv.addReferee = referee;
  } while (!FeasibleMove(st, mv));
} 

// check move feasibility
bool AddRemoveRefereeNeighborhoodExplorer::FeasibleMove(const RA_State& st, const AddRemoveReferee& mv) const
{
	if (mv.remReferee == mv.addReferee) // i.e. mv.remReferee = mv.addReferee = 0
		return false;

  if (mv.remReferee != 0 && st.AssignedReferees(mv.game).find(mv.remReferee) == st.AssignedReferees(mv.game).end())
    return false;

  if (mv.addReferee != 0 && st.AssignedReferees(mv.game).find(mv.addReferee) != st.AssignedReferees(mv.game).end())
    return false;

  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  if (MinimumRefereesDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees) > 0)
    return false;

  if (MaximumRefereesDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees) > 0)
    return false;

  if (FeasibleTravelDistanceDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees) > 0)
    return false;

  if (RefereeAvailabilityDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees) > 0)
    return false;

  if (MinimumLevelDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees) > 0)
    return false;

  return true;
} 

// update the state according to the move 
void AddRemoveRefereeNeighborhoodExplorer::MakeMove(RA_State& st, const AddRemoveReferee& mv) const
{
  if (mv.remReferee != 0)
    st.Unassign(mv.remReferee, mv.game);

  if (mv.addReferee != 0)
    st.Assign(mv.addReferee, mv.game);
}  

void AddRemoveRefereeNeighborhoodExplorer::FirstMove(const RA_State& st, AddRemoveReferee& mv) const
{
  // mv.game = Random::Uniform<int>(1, in.NumGames());
  mv.game = 1;
  mv.remReferee = 0;
  mv.addReferee = 0;
  NextMove(st, mv);
}

bool AddRemoveRefereeNeighborhoodExplorer::NextMove(const RA_State& st, AddRemoveReferee& mv) const
{
  do
    if (!AnyNextMove(st, mv))
      return false;
  while (!FeasibleMove(st, mv));

  return true;
}

bool AddRemoveRefereeNeighborhoodExplorer::AnyNextMove(const RA_State& st, AddRemoveReferee& mv) const
{
  int numAssignedReferees = static_cast<int>(st.AssignedReferees(mv.game).size());
  int division = in.GetGame(mv.game).Division();
  int minReferees = in.GetDivision(division).MinReferees();
  int maxReferees = in.GetDivision(division).MaxReferees();
  set<int>::iterator it;
  bool nextGame = false;

  // it holds that: nextRemReferee = nextAddReferee = 0 \/ nextRemReferee != nextAddReferee
  int nextRemReferee = 0;

  if (mv.remReferee == 0 && !st.AssignedReferees(mv.game).empty())
    nextRemReferee = *st.AssignedReferees(mv.game).begin();
  else if (mv.remReferee != 0)
  {
    it = st.AssignedReferees(mv.game).find(mv.remReferee);

    if (next(it) != st.AssignedReferees(mv.game).end())
      nextRemReferee = *next(it);
  }

  int nextAddReferee = 0;

  for (int r = mv.addReferee + 1; r <= in.NumReferees(); r++)
    if (st.AssignedReferees(mv.game).find(r) == st.AssignedReferees(mv.game).end())
    {
      nextAddReferee = r;
      break;
    }

  mv.addReferee = nextAddReferee;

  if (nextRemReferee == nextAddReferee) // i.e. nextRemReferee = nextAddReferee = 0
    nextGame = true;
	else if (mv.addReferee == 0 || (mv.remReferee == 0 && numAssignedReferees == maxReferees))
  {
  	if (nextRemReferee == 0)
      nextGame = true;
    else
    {
    	mv.remReferee = nextRemReferee;
    	mv.addReferee = 0;
    }

    if (numAssignedReferees == minReferees)
    {
      for (int r = 1; r <= in.NumReferees(); r++)
        if (st.AssignedReferees(mv.game).find(r) == st.AssignedReferees(mv.game).end())
        {
          mv.addReferee = r;
          break;
        }

      if (mv.addReferee == 0)
        nextGame = true;
    }
  }

  if (nextGame)
  {
    if (mv.game == in.NumGames())
      return false;
    else
    {
      mv.game++;
      mv.remReferee = 0;
      mv.addReferee = 0;
    }
  }

  return true;
}

int AddRemoveDeltaMinimumReferees::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return MinimumRefereesDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}
          
int AddRemoveDeltaMaximumReferees::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return MaximumRefereesDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaFeasibleTravelDistance::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return FeasibleTravelDistanceDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaRefereeAvailability::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return RefereeAvailabilityDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaMinimumLevel::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return MinimumLevelDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaLackOfExperience::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return LackOfExperienceDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaGamesDistribution::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return GamesDistributionDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaTotalDistance::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return TotalDistanceDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaOptionalReferee::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return OptionalRefereeDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaAssignmentFrequency::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return AssignmentFrequencyDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaRefereeIncompatibility::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return RefereeIncompatibilityDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

int AddRemoveDeltaTeamIncompatibility::ComputeDeltaCost(const RA_State& st, const AddRemoveReferee& mv) const
{
  set<int> oldAssignedReferees(st.AssignedReferees(mv.game));
  set<int> newAssignedReferees(st.AssignedReferees(mv.game));

  if (mv.remReferee != 0)
    newAssignedReferees.erase(mv.remReferee);

  if (mv.addReferee != 0)
    newAssignedReferees.insert(mv.addReferee);

  return TeamIncompatibilityDeltaCost(in, st, mv.game, oldAssignedReferees, newAssignedReferees);
}

/***************************************************************************
 * Delta Cost Support Functions:
 ***************************************************************************/
int MinimumRefereesDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int division = in.GetGame(game).Division();
  int minReferees = in.GetDivision(division).MinReferees();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());

  if (numAssignedReferees < minReferees && numNewAssignedReferees >= minReferees)
    return -1;
  else if (numAssignedReferees >= minReferees && numNewAssignedReferees < minReferees)
    return 1;
  else
    return 0;
}

int MaximumRefereesDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int division = in.GetGame(game).Division();
  int maxReferees = in.GetDivision(division).MaxReferees();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());

  if (numAssignedReferees > maxReferees && numNewAssignedReferees <= maxReferees)
    return -1;
  else if (numAssignedReferees <= maxReferees && numNewAssignedReferees > maxReferees)
    return 1;
  else
    return 0;
}

int FeasibleTravelDistanceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg, itn;
  set<int>::reverse_iterator ritp;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int refereeCode;
  bool oldFeasibleTravelDistance = true, newFeasibleTravelDistance = true, mvgameOverlapping = false;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    refereeCode = in.GetReferee(*it).Code();

    // here AssignedGames(refereeCode) is certainly NOT empty
    for (itg = st.AssignedGames(refereeCode).begin(); itg != prev(st.AssignedGames(refereeCode).end()); ++itg) 
    {
      const Game &previousGame = in.GetGame(*itg);
      const Game &nextGame = in.GetGame(*next(itg));

      if (*itg != game && *next(itg) != game &&
          st.OverlappingGames(previousGame, nextGame, refereeCode))
      {
        oldFeasibleTravelDistance = false;
        break;
      }
      else if ((*itg == game || *next(itg) == game) &&
               st.OverlappingGames(previousGame, nextGame, refereeCode))
      {
        mvgameOverlapping = true;
      }
    }

    itg = st.AssignedGames(refereeCode).find(game);
    ritp = make_reverse_iterator(itg);
    itn = next(itg);
    if (ritp != st.AssignedGames(refereeCode).rend() &&
        itn != st.AssignedGames(refereeCode).end() &&
        st.OverlappingGames(in.GetGame(*ritp), in.GetGame(*itn), refereeCode))
    {
      oldFeasibleTravelDistance = false;
    }

    if (oldFeasibleTravelDistance && mvgameOverlapping)
      cost--;

    oldFeasibleTravelDistance = true;
    mvgameOverlapping = false;
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    refereeCode = in.GetReferee(*it).Code();

    itn = find_if(st.AssignedGames(refereeCode).begin(), st.AssignedGames(refereeCode).end(), [game](const int g)->bool
          {
            return game < g;
          });

    ritp = make_reverse_iterator(itn);

    if (!st.AssignedGames(refereeCode).empty())
    {
      for (itg = st.AssignedGames(refereeCode).begin(); itg != prev(st.AssignedGames(refereeCode).end()); ++itg) {
        const Game &previousGame = in.GetGame(*itg);
        const Game &nextGame = in.GetGame(*next(itg));

        if (st.OverlappingGames(previousGame, nextGame, refereeCode))
          newFeasibleTravelDistance = false;
      }
    }

    if ((itn != st.AssignedGames(refereeCode).end() &&
         st.OverlappingGames(in.GetGame(game), in.GetGame(*itn), refereeCode)) ||
        (ritp != st.AssignedGames(refereeCode).rend() &&
         st.OverlappingGames(in.GetGame(*ritp), in.GetGame(game), refereeCode)))
    {
      mvgameOverlapping = true;
    }

    if (newFeasibleTravelDistance && mvgameOverlapping)
      cost++;

    newFeasibleTravelDistance = true;
    mvgameOverlapping = false;
  }

  return cost;
}

int RefereeAvailabilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  Event mvgameMatch = in.GetGame(game).Match();
  bool oldAvailability = true, newAvailability = true;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Unavailable(mvgameMatch))
    {
      for (itg = st.AssignedGames(*it).begin(); itg != st.AssignedGames(*it).end(); ++itg)
        if (*itg != game)
        {
          const Game &g = in.GetGame(*itg);
          if (in.GetReferee(*it).Unavailable(g.Match()))
          {
            oldAvailability = false;
            break;
          }
        }

      if (oldAvailability)
        cost--;

      oldAvailability = true;
    }


  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Unavailable(mvgameMatch))
    {
      for (itg = st.AssignedGames(*it).begin(); itg != st.AssignedGames(*it).end(); ++itg)
      {
        const Game &g = in.GetGame(*itg);
        if (in.GetReferee(*it).Unavailable(g.Match()))
        {
          newAvailability = false;
          break;
        }
      }

      if (newAvailability)
        cost++;

      newAvailability = true;
    }

  return cost;
}

int MinimumLevelDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int mvgameLevel = in.GetDivision(in.GetGame(game).Division()).Level();
  bool oldMinimumLevel = true, newMinimumLevel = true;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Level() < mvgameLevel)
    {
      for (itg = st.AssignedGames(*it).begin(); itg != st.AssignedGames(*it).end(); ++itg)
        if (*itg != game)
        {
          const Division &division = in.GetDivision(in.GetGame(*itg).Division());
          if (in.GetReferee(*it).Level() < division.Level())
          {
            oldMinimumLevel = false;
            break;
          }
        }

      if (oldMinimumLevel)
        cost--;

      oldMinimumLevel = true;
    }


  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Level() < mvgameLevel)
    {
      for (itg = st.AssignedGames(*it).begin(); itg != st.AssignedGames(*it).end(); ++itg)
      {        
        const Division &division = in.GetDivision(in.GetGame(*itg).Division());
        if (in.GetReferee(*it).Level() < division.Level())
        {
          newMinimumLevel = false;
          break;
        }
      }

      if (newMinimumLevel)
        cost++;

      newMinimumLevel = true;
    }

  return cost;
}

int LackOfExperienceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  set<int> oldDiffReferees, newDiffReferees, stableReferees;
  set<int>::iterator it;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int oldExperience = 0, newExperience = 0, stableExperience = 0;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));
  set_intersection(obeg, oend, nbeg, nend, inserter(stableReferees, stableReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    oldExperience += in.GetReferee(*it).Experience();

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    newExperience += in.GetReferee(*it).Experience();

  for (it = stableReferees.begin(); it != stableReferees.end(); ++it)
    stableExperience += in.GetReferee(*it).Experience();

  if (oldExperience + stableExperience <  in.GetGame(game).Experience() &&
      newExperience + stableExperience >= in.GetGame(game).Experience())
    return -1;
  else if (oldExperience + stableExperience >= in.GetGame(game).Experience() &&
           newExperience + stableExperience < in.GetGame(game).Experience())
    return 1;
  else
    return 0;
}

int GamesDistributionDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());
  int oldTotalAssignedGames = 0, newTotalAssignedGames;
  double oldAverageAssignedGames, newAverageAssignedGames;
  int oldGamesDistribution, newGamesDistribution;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (int r = 1; r <= in.NumReferees(); r++)
    oldTotalAssignedGames += st.AssignedGames(r).size();

  newTotalAssignedGames = oldTotalAssignedGames + (numNewAssignedReferees - numAssignedReferees);
  oldAverageAssignedGames = static_cast<double>(oldTotalAssignedGames) / in.NumReferees();
  newAverageAssignedGames = static_cast<double>(newTotalAssignedGames) / in.NumReferees();

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    oldGamesDistribution = static_cast<int>(ceil(fabs(oldAverageAssignedGames - st.AssignedGames(r).size())));

    if (oldDiffReferees.find(r) != oldDiffReferees.end() &&
        newDiffReferees.find(r) == newDiffReferees.end())
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - (st.AssignedGames(r).size() - 1))));
    else if (newDiffReferees.find(r) != newDiffReferees.end() &&
             oldDiffReferees.find(r) == oldDiffReferees.end())
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - (st.AssignedGames(r).size() + 1))));
    else
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - st.AssignedGames(r).size())));

    cost += newGamesDistribution - oldGamesDistribution;
  }

  return cost;
}

int TotalDistanceDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itf, itn;
  set<int>::reverse_iterator ritp;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  Coordinates2D mvgameArena = in.GetArena(in.GetGame(game).Arena()).Address();
  Coordinates2D refereeHome, prevArena, nextArena;
  int refereeCode;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);
    refereeHome = referee.Address();
    refereeCode = referee.Code();
    itf = st.AssignedGames(refereeCode).find(game);
    ritp = make_reverse_iterator(itf);
    itn = next(itf);

    if ((ritp == st.AssignedGames(refereeCode).rend() ||
         in.GetGame(*itf).Match().StartDate() != in.GetGame(*ritp).Match().StartDate()) &&
        (itn == st.AssignedGames(refereeCode).end() ||
         in.GetGame(*itf).Match().StartDate() != in.GetGame(*itn).Match().StartDate()))
    {
      cost -= EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    }
    else if ((itn == st.AssignedGames(refereeCode).end() ||
              in.GetGame(*itf).Match().StartDate() != in.GetGame(*itn).Match().StartDate()) &&
              in.GetGame(*itf).Match().StartDate() == in.GetGame(*ritp).Match().StartDate()) // redundant condition
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      cost -= EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
      cost += EuclideanDistance(prevArena, refereeHome);
    }
    else if ((ritp == st.AssignedGames(refereeCode).rend() ||
              in.GetGame(*itf).Match().StartDate() != in.GetGame(*ritp).Match().StartDate()) &&
              in.GetGame(*itf).Match().StartDate() == in.GetGame(*itn).Match().StartDate()) // redundant condition
    {
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
      cost += EuclideanDistance(refereeHome, nextArena);
    }
    else  // prev->startDate == mvgame->startDate == next->startDate
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
      cost += EuclideanDistance(prevArena, nextArena);
    }
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);
    refereeHome = referee.Address();
    refereeCode = referee.Code();
    const RA_Input& input(in);

    ritp = find_if(st.AssignedGames(refereeCode).rbegin(), st.AssignedGames(refereeCode).rend(), [&input, game](const int g)->bool
          {
            return g < game &&
                   input.GetGame(g).Match().StartDate() == input.GetGame(game).Match().StartDate() &&
                   input.GetGame(g).Match().StartTime() <= input.GetGame(game).Match().StartTime();
          });

    itn = find_if(st.AssignedGames(refereeCode).begin(), st.AssignedGames(refereeCode).end(), [&input, game](const int g)->bool
          {
            return game < g &&
                   input.GetGame(game).Match().StartDate() == input.GetGame(g).Match().StartDate() &&
                   input.GetGame(game).Match().StartTime() <= input.GetGame(g).Match().StartTime();
          });

    if (ritp == st.AssignedGames(refereeCode).rend() && itn == st.AssignedGames(refereeCode).end())
      cost += EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    else if (ritp != st.AssignedGames(refereeCode).rend() && itn == st.AssignedGames(refereeCode).end())
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      cost -= EuclideanDistance(prevArena, refereeHome);
      cost += EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    } else if (ritp == st.AssignedGames(refereeCode).rend() && itn != st.AssignedGames(refereeCode).end())
    {
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(refereeHome, nextArena);
      cost += EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
    } else
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(prevArena, nextArena);
      cost += EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
    }
  }

  return cost;
}

int OptionalRefereeDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  const Division &division = in.GetDivision(in.GetGame(game).Division());
  int optionalReferee = division.MaxReferees() - division.MinReferees();
  int oldAbsentOptionalReferees = st.OptionalReferee(game);
  
  int newAssignedOptionalReferees = static_cast<int>(newAssignedReferees.size()) - division.MinReferees();

  if (newAssignedOptionalReferees < 0)
    newAssignedOptionalReferees = 0;

  int newAbsentOptionalReferees = optionalReferee - newAssignedOptionalReferees;

  if (newAbsentOptionalReferees < 0)
    newAbsentOptionalReferees = 0;

  return newAbsentOptionalReferees - oldAbsentOptionalReferees;
}

int AssignmentFrequencyDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());
  int mvgHomeTeamCode = in.GetTeam(in.GetGame(game).HomeTeam()).Code();
  int mvgAwayTeamCode = in.GetTeam(in.GetGame(game).AwayTeam()).Code();
  int oldmvgHTTotalAssignedReferees = 0, oldmvgATTotalAssignedReferees = 0;
  int newmvgHTTotalAssignedReferees, newmvgATTotalAssignedReferees;
  int mvgHTAssignedInputReferee = 0, mvgATAssignedInputReferee = 0;
  double oldmvgHTAverageAssignedReferee, newmvgHTAverageAssignedReferee;
  double oldmvgATAverageAssignedReferee, newmvgATAverageAssignedReferee;
  int oldmvgHTAssignmentFrequency, newmvgHTAssignmentFrequency;
  int oldmvgATAssignmentFrequency, newmvgATAssignmentFrequency;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    for (int g = 1; g <= in.NumGames(); g++)
    {
      const Team &homeTeam = in.GetTeam(in.GetGame(g).HomeTeam());
      const Team &awayTeam = in.GetTeam(in.GetGame(g).AwayTeam());

      if (mvgHomeTeamCode == homeTeam.Code() || mvgHomeTeamCode == awayTeam.Code())
      {
        oldmvgHTTotalAssignedReferees += st.AssignedReferees(g).size();
        if (st.AssignedReferees(g).find(r) != st.AssignedReferees(g).end())
          mvgHTAssignedInputReferee++;
      }

      if (mvgAwayTeamCode == homeTeam.Code() || mvgAwayTeamCode == awayTeam.Code())
      {
        oldmvgATTotalAssignedReferees += st.AssignedReferees(g).size();
        if (st.AssignedReferees(g).find(r) != st.AssignedReferees(g).end())
          mvgATAssignedInputReferee++;
      }
    }

    newmvgHTTotalAssignedReferees = oldmvgHTTotalAssignedReferees + (numNewAssignedReferees - numAssignedReferees);
    newmvgATTotalAssignedReferees = oldmvgATTotalAssignedReferees + (numNewAssignedReferees - numAssignedReferees);
    oldmvgHTAverageAssignedReferee = static_cast<double>(oldmvgHTTotalAssignedReferees) / in.NumReferees();
    newmvgHTAverageAssignedReferee = static_cast<double>(newmvgHTTotalAssignedReferees) / in.NumReferees();
    oldmvgATAverageAssignedReferee = static_cast<double>(oldmvgATTotalAssignedReferees) / in.NumReferees();
    newmvgATAverageAssignedReferee = static_cast<double>(newmvgATTotalAssignedReferees) / in.NumReferees();

    if (mvgHTAssignedInputReferee > oldmvgHTAverageAssignedReferee)
      oldmvgHTAssignmentFrequency = static_cast<int>(ceil(mvgHTAssignedInputReferee - oldmvgHTAverageAssignedReferee));
    else
      oldmvgHTAssignmentFrequency = 0;

    if (mvgATAssignedInputReferee > oldmvgATAverageAssignedReferee)
      oldmvgATAssignmentFrequency = static_cast<int>(ceil(mvgATAssignedInputReferee - oldmvgATAverageAssignedReferee));
    else
      oldmvgATAssignmentFrequency = 0;

    if (oldDiffReferees.find(r) != oldDiffReferees.end() &&
        newDiffReferees.find(r) == newDiffReferees.end())
    {
      if (mvgHTAssignedInputReferee - 1 > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil((mvgHTAssignedInputReferee - 1) - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee - 1 > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil((mvgATAssignedInputReferee - 1) - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }
    else if (newDiffReferees.find(r) != newDiffReferees.end() &&
             oldDiffReferees.find(r) == oldDiffReferees.end())
    {
      if (mvgHTAssignedInputReferee + 1 > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil((mvgHTAssignedInputReferee + 1) - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee + 1 > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil((mvgATAssignedInputReferee + 1) - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }
    else
    {
      if (mvgHTAssignedInputReferee > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil(mvgHTAssignedInputReferee - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil(mvgATAssignedInputReferee - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }

    cost += newmvgHTAssignmentFrequency - oldmvgHTAssignmentFrequency;
    cost += newmvgATAssignmentFrequency - oldmvgATAssignmentFrequency;

    oldmvgHTTotalAssignedReferees = 0;
    oldmvgATTotalAssignedReferees = 0;
    mvgHTAssignedInputReferee = 0;
    mvgATAssignedInputReferee = 0;
  }

  return cost;
}

int RefereeIncompatibilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator itI, itJ, itF;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (itI = oldDiffReferees.begin(); itI != oldDiffReferees.end(); ++itI)
  {
    for (itJ = obeg; itJ != oend; ++itJ)
    {
      const Referee &refereeI = in.GetReferee(*itI);
      const Referee &refereeJ = in.GetReferee(*itJ);
        
      if (refereeI.IncompatibleReferee(refereeJ.Code()))
        cost--;

      itF = oldDiffReferees.find(refereeJ.Code());

      if (itF == oldDiffReferees.end() && refereeJ.IncompatibleReferee(refereeI.Code()))
        cost--;
    }
  }

  for (itI = newDiffReferees.begin(); itI != newDiffReferees.end(); ++itI)
  {
    for (itJ = nbeg; itJ != nend; ++itJ)
    {
      const Referee &refereeI = in.GetReferee(*itI);
      const Referee &refereeJ = in.GetReferee(*itJ);
        
      if (refereeI.IncompatibleReferee(refereeJ.Code()))
        cost++;

      itF = newDiffReferees.find(refereeJ.Code());

      if (itF == newDiffReferees.end() && refereeJ.IncompatibleReferee(refereeI.Code()))
        cost++;
    }
  }

  return cost;
}

int TeamIncompatibilityDeltaCost(const RA_Input& in, const RA_State& st, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  const Team &homeTeam = in.GetTeam(in.GetGame(game).HomeTeam());
  const Team &awayTeam = in.GetTeam(in.GetGame(game).AwayTeam());

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);

    if (referee.IncompatibleTeam(homeTeam.Code()))
      cost--;

    if (referee.IncompatibleTeam(awayTeam.Code()))
      cost--;
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);

    if (referee.IncompatibleTeam(homeTeam.Code()))
      cost++;

    if (referee.IncompatibleTeam(awayTeam.Code()))
      cost++;
  }

  return cost;
}

