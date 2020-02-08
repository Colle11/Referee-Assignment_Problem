// File RA_Greedy.hh

#ifndef RA_GREEDY_HH
#define RA_GREEDY_HH
#include "RA_Data.hh"

void GreedyRASolver(const RA_Input& in, RA_Output& out);

/***************************************************************************
 * Delta Cost Support Functions:
 ***************************************************************************/
int MinimumRefereesDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int MaximumRefereesDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int FeasibleTravelDistanceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int RefereeAvailabilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int MinimumLevelDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int LackOfExperienceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int GamesDistributionDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int TotalDistanceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int OptionalRefereeDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int AssignmentFrequencyDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int RefereeIncompatibilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);
int TeamIncompatibilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees);

#endif
