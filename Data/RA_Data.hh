// File RA_Data.hh

#ifndef RA_DATA_HH
#define RA_DATA_HH

#include <iostream>
#include <vector>
#include <set>
#include "Division.hh"
#include "Referee.hh"
#include "Arena.hh"
#include "Team.hh"
#include "Game.hh"

using namespace std;

class RA_Input {

	friend ostream& operator<<(ostream& os, const RA_Input& ra);

public:
	RA_Input(string fileName);
	int NumDivisions() const { return numDivisions; }
	int NumReferees() const { return numReferees; }
	int NumArenas() const { return numArenas; }
	int NumTeams() const { return numTeams; }
	int NumGames() const { return numGames; }
	const Division& GetDivision(int d) const { return divisions[d - 1]; }
	const Referee& GetReferee(int r) const { return referees[r - 1]; }
	const Arena& GetArena(int a) const { return arenas[a - 1]; }
	const Team& GetTeam(int t) const { return teams[t - 1]; }
	const Game& GetGame(int g) const { return games[g - 1]; }
	int LackOfExperienceWeight() const { return lackOfExperienceWeight; }
	int GamesDistributionWeight() const { return gamesDistributionWeight; }
	int TotalDistanceWeight() const { return totalDistanceWeight; }
	int OptionalRefereeWeight() const { return optionalRefereeWeight; }
	int AssignmentFrequencyWeight() const { return assignmentFrequencyWeight; }
	int RefereeIncompatibilityWeight() const { return refereeIncompatibilityWeight; }
	int TeamIncompatibilityWeight() const { return teamIncompatibilityWeight; }
	void SetLackOfExperienceWeight(int loe) { lackOfExperienceWeight = loe; }
	void SetGamesDistributionWeight(int gd) { gamesDistributionWeight = gd; }
	void SetTotalDistanceWeight(int td) { totalDistanceWeight = td; }
	void SetOptionalRefereeWeight(int o) { optionalRefereeWeight = o; }
	void SetAssignmentFrequencyWeight(int af) { assignmentFrequencyWeight = af; }
	void SetRefereeIncompatibilityWeight(int ri) { refereeIncompatibilityWeight = ri; }
	void SetTeamIncompatibilityWeight(int ti) { teamIncompatibilityWeight = ti; }

private:
	int numDivisions;
	int numReferees;
	int numArenas;
	int numTeams;
	int numGames;
	vector<Division> divisions;
	vector<Referee> referees;
	vector<Arena> arenas;
	vector<Team> teams;
	vector<Game> games;

	// Soft constraints weights
	int lackOfExperienceWeight = 1;
	int gamesDistributionWeight = 1;
	int totalDistanceWeight = 1;
	int optionalRefereeWeight = 1;
	int assignmentFrequencyWeight = 1;
	int refereeIncompatibilityWeight = 1;
	int teamIncompatibilityWeight = 1;

};

class RA_Output {

	friend ostream& operator<<(ostream& os, const RA_Output& out);
	friend istream& operator>>(istream& is, RA_Output& out);

public:
	RA_Output(const RA_Input& i);
	RA_Output& operator=(const RA_Output& out);
	void Reset();
	void Assign(int r, int g);	// assigns the referee to the game
	void Unassign(int r, int g);	// unassigns the referee to the game
	void UnassignAll(int g);	// unassigns all referees to the game
	int ComputeCost() const;
	unsigned ComputeViolations() const;
	bool HasViolations() const;
	int AverageSpeed() const { return averageSpeed; }
	void SetAverageSpeed(int s) { averageSpeed = s; }
	const set<int>& AssignedReferees(int g) const { return games[g - 1]; }	// returns the set of referees assigned to the game
	const set<int>& AssignedGames(int r) const { return referees[r - 1]; }	// returns the set of games assigned to the referee
	bool OverlappingGames(const Game& previousGame, const Game& nextGame, int r) const;	// returns true if the two games overlap in time; the notion of overlapping considers also the travel time of the referee between the two arenas
	// HARD CONSTRAINTS
	bool HasMinimumReferees(int g) const;	// returns true if the number of mandatory referees is assigned to the game
	bool LeqThanMaximumReferees(int g) const;	// returns true if the number of assigned referees is NOT greater than the maximum
	bool FeasibleTravelDistance(int r) const;	// returns true if the game schedule assigned to the referee is feasible
	bool RefereeAvailability(int r) const;	// returns true if the referee is available in the assigned games
	bool HasMinimumLevel(int r) const;	// returns true if the referee has the minimum level required for the games assigned
	// SOFT CONSTRAINTS
	bool LackOfExperience(int g) const;	// returns true if the sum of the experience of the referees is less than the requested one for the game
	int GamesDistribution(int r) const;	// returns the difference between the number of games assigned to the referee and the average value
	int TotalDistance(int r) const;	// returns the total travelling distance of the referee
	int OptionalReferee(int g) const;	// returns the number of absent optional referees
	int AssignmentFrequency(int r, int t) const;	// returns the difference between the number of times the referee has been assigned to the team (if higher than -->) and the average value
	int RefereeIncompatibility(int g) const;	// returns the number of incompatible referees in the same game
	int TeamIncompatibility(int g) const;	// returns the number of incompatibilities between teams and referees in the same game

protected:
	virtual int TravelTime(Coordinates2D address1, Coordinates2D address2) const;	// calculates the travel time (in minutes) from one address to another

	const RA_Input& in;
	vector<set<int>> games;
	vector<set<int>> referees;
	int averageSpeed = 50; // km/h

};

#endif
