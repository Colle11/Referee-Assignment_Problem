// File RA_Data.cc

#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "RA_Data.hh"
#include "Event.hh"
#include "Coordinates2D.hh"

RA_Input::RA_Input(string fileName) {
	ifstream is(fileName);
	if (!is) {
		cerr << "Cannot open file " << fileName << endl;
		exit(1);
	}

	string s;

	is >> s >> s >> numDivisions >> s;
	is >> s >> s >> numReferees >> s;
	is >> s >> s >> numArenas >> s;
	is >> s >> s >> numTeams >> s;
	is >> s >> s >> numGames >> s;
	divisions.resize(numDivisions);
	referees.resize(numReferees);
	arenas.resize(numArenas);
	teams.resize(numTeams);
	games.resize(numGames);

	// DIVISIONS
	is >> s;
	getline(is, s);
	for (int i = 0; i < numDivisions; i++)
		is >> divisions[i];

	// REFEREES
	is >> s;
	getline(is, s);
	for (int i = 0; i < numReferees; i++)
		is >> referees[i];

	// ARENAS
	is >> s;
	getline(is, s);
	for (int i = 0; i < numArenas; i++)
		is >> arenas[i];

	// TEAMS
	is >> s;
	getline(is, s);
	for (int i = 0; i < numTeams; i++)
		is >> teams[i];

	// GAMES
	is >> s;
	getline(is, s);
	for (int i = 0; i < numGames; i++)
		is >> games[i];

	sort(games.begin(), games.end(), less_equal<Game>());
}

ostream& operator<<(ostream& os, const RA_Input& ra) {
	os << "Divisions = " << ra.numDivisions << ";" << endl;
	os << "Referees = " << ra.numReferees << ";" << endl;
	os << "Arenas = " << ra.numArenas << ";" << endl;
	os << "Teams = " << ra.numTeams << ";" << endl;
	os << "Games = " << ra.numGames << ";" << endl;

	// DIVISIONS
	os << endl;
	os << "DIVISIONS % code, min referees, max referees, level, teams" << endl;
	for (int i = 0; i < ra.numDivisions; i++)
		os << ra.divisions[i] << endl;

	// REFEREES
	os << endl;
	os << "REFEREES % code, level, coordinates, experience, incompatible referees, incompatible teams, unavailabilities" << endl;
	for (int i = 0; i < ra.numReferees; i++)
		os << ra.referees[i] << endl;

	// ARENAS
	os << endl;
	os << "ARENAS % code, coordinates" << endl;
	for (int i = 0; i < ra.numArenas; i++)
		os << ra.arenas[i] << endl;

	// TEAMS
	os << endl;
	os << "TEAMS % name, division" << endl;
	for (int i = 0; i < ra.numTeams; i++)
		os << ra.teams[i] << endl;

	// GAMES
	os << endl;
	os << "GAMES % Home team, guest team, division, date, time, arena, experience" << endl;
	for (int i = 0; i < ra.numGames; i++)
		os << ra.games[i] << endl;

	// GAMES (matchweek formatting)
	// os << endl;
	// os << "GAMES % Home team, guest team, division, date, time, arena, experience" << endl;
	// int t;
	// int m;
	// int c = 0;
	// for (int d = 1; d <= ra.numDivisions; d++) {
	// 	t = ra.GetDivision(d).Teams();
	// 	m = (t - 1) * t;
	// 	for (int i = 1; i <= m; i++) {
	// 		os << ra.GetGame(c + i) << endl;
	// 		if (i % (t / 2) == 0)
	// 			cout << endl;
	// 	}
	// 	c += m;
	// }

	return os;
}

RA_Output::RA_Output(const RA_Input& i)
	: in(i), games(in.NumGames(), set<int>()), referees(in.NumReferees(), set<int>())
{}

RA_Output& RA_Output::operator=(const RA_Output& out) {
	games = out.games;
	referees = out.referees;
	return *this;
}

void RA_Output::Reset() {
	for (long unsigned int i = 0; i < games.size(); i++)
		games[i].clear();

	for (long unsigned int i = 0; i < referees.size(); i++)
		referees[i].clear();
}

bool RA_Output::HasMinimumReferees(int g) const {
	int division = in.GetGame(g).Division();
	return static_cast<int>(AssignedReferees(g).size()) >= in.GetDivision(division).MinReferees();
}

bool RA_Output::LeqThanMaximumReferees(int g) const {
	int division = in.GetGame(g).Division();
	return static_cast<int>(AssignedReferees(g).size()) <= in.GetDivision(division).MaxReferees();
}

bool RA_Output::FeasibleTravelDistance(int r) const {
	if (!AssignedGames(r).empty()) {
		for (set<int>::iterator it = AssignedGames(r).begin(); it != prev(AssignedGames(r).end()); ++it) {
			const Game &previousGame = in.GetGame(*it);
			const Game &nextGame = in.GetGame(*next(it));

			if (OverlappingGames(previousGame, nextGame, r))
				return false;
		}
	}
	return true;
}

bool RA_Output::OverlappingGames(const Game& previousGame, const Game& nextGame, int r) const {
	if (OverlappingEvents(previousGame.Match(), nextGame.Match())) {
		return true;
	} else if (previousGame.Match().StartDate() != nextGame.Match().StartDate()) {
		Coordinates2D addressPreviousArena = in.GetArena(previousGame.Arena()).Address();
		Coordinates2D addressNextArena = in.GetArena(nextGame.Arena()).Address();
		Coordinates2D refereeHome = in.GetReferee(r).Address();
		int ttPrevToHome = TravelTime(addressPreviousArena, refereeHome);
		int ttHomeToNext = TravelTime(refereeHome, addressNextArena);
		Event travel(previousGame.Match().EndDate(), previousGame.Match().EndTime(), ttPrevToHome + ttHomeToNext);
		if (OverlappingEvents(travel, nextGame.Match()))
			return true;
	} else {
		Coordinates2D addressPreviousArena = in.GetArena(previousGame.Arena()).Address();
		Coordinates2D addressNextArena = in.GetArena(nextGame.Arena()).Address();
		int travelTime = TravelTime(addressPreviousArena, addressNextArena);
		Event travel(previousGame.Match().EndDate(), previousGame.Match().EndTime(), travelTime);
		if (OverlappingEvents(travel, nextGame.Match()))
			return true;
	}

	return false;
}

bool RA_Output::RefereeAvailability(int r) const {
	for (set<int>::iterator it = AssignedGames(r).begin(); it != AssignedGames(r).end(); ++it) {
		const Game &game = in.GetGame(*it);
		if (in.GetReferee(r).Unavailable(game.Match()))
			return false;
	}
	return true;
}

bool RA_Output::HasMinimumLevel(int r) const {
	for (set<int>::iterator it = AssignedGames(r).begin(); it != AssignedGames(r).end(); ++it) {
		const Division &division = in.GetDivision(in.GetGame(*it).Division());
		if (in.GetReferee(r).Level() < division.Level())
			return false;
	}
	return true;
}

bool RA_Output::LackOfExperience(int g) const {
	int totalExperience = 0;

	for (set<int>::iterator it = AssignedReferees(g).begin(); it != AssignedReferees(g).end(); ++it)
		totalExperience += in.GetReferee(*it).Experience();

	return totalExperience < in.GetGame(g).Experience();
}

int RA_Output::GamesDistribution(int r) const {
	int totalAssignedGames = 0;
	double averageAssignedGames;

	for (int ref = 1; ref <= in.NumReferees(); ref++)
		totalAssignedGames += AssignedGames(ref).size();

	averageAssignedGames = static_cast<double>(totalAssignedGames) / in.NumReferees();
	return static_cast<int>(ceil(fabs(averageAssignedGames - AssignedGames(r).size())));
}

int RA_Output::TotalDistance(int r) const {
	int totalDistance = 0;

	if (!AssignedGames(r).empty()) {
		Coordinates2D refereeHome = in.GetReferee(r).Address();
		set<int>::iterator it = AssignedGames(r).begin();
		Coordinates2D firstArena = in.GetArena(in.GetGame(*it).Arena()).Address();
		totalDistance += EuclideanDistance(refereeHome, firstArena);

		for (; it != AssignedGames(r).end(); ++it) {
			Coordinates2D previousArena = in.GetArena(in.GetGame(*it).Arena()).Address();
			if (next(it) == AssignedGames(r).end()) {
				totalDistance += EuclideanDistance(previousArena, refereeHome);
			} else if (in.GetGame(*it).Match().StartDate() != in.GetGame(*next(it)).Match().StartDate()) {
				Coordinates2D nextArena = in.GetArena(in.GetGame(*next(it)).Arena()).Address();
				totalDistance += EuclideanDistance(previousArena, refereeHome);
				totalDistance += EuclideanDistance(refereeHome, nextArena);
			} else {
				Coordinates2D nextArena = in.GetArena(in.GetGame(*next(it)).Arena()).Address();
				totalDistance += EuclideanDistance(previousArena, nextArena);
			}
		}
	}
	return totalDistance;
}

int RA_Output::OptionalReferee(int g) const {
	const Division &division = in.GetDivision(in.GetGame(g).Division());
	int optionalReferee = division.MaxReferees() - division.MinReferees();
	int assignedOptionalReferees = static_cast<int>(AssignedReferees(g).size()) - division.MinReferees();
	
	if (assignedOptionalReferees < 0)
		assignedOptionalReferees = 0;

	optionalReferee -= assignedOptionalReferees;

	if (optionalReferee < 0)
		optionalReferee = 0;

	return optionalReferee;
}

int RA_Output::AssignmentFrequency(int r, int t) const {
	int totalAssignedReferees = 0;
	int assignedInputReferee = 0;
	double averageAssignedReferee;

	for (long unsigned int g = 1; g <= games.size(); g++) {
		const Team &homeTeam = in.GetTeam(in.GetGame(g).HomeTeam());
		const Team &awayTeam = in.GetTeam(in.GetGame(g).AwayTeam());

		if (t == homeTeam.Code() || t == awayTeam.Code()) {
			totalAssignedReferees += AssignedReferees(g).size();
			if (AssignedReferees(g).find(r) != AssignedReferees(g).end())
				assignedInputReferee++;
		}
	}

	averageAssignedReferee = static_cast<double>(totalAssignedReferees) / in.NumReferees();
	if (assignedInputReferee > averageAssignedReferee)
		return static_cast<int>(ceil(assignedInputReferee - averageAssignedReferee));
	else
		return 0;
}

int RA_Output::RefereeIncompatibility(int g) const {
	int refereeIncompatibility = 0;

	if (AssignedReferees(g).size() >= 2) {
		for (set<int>::iterator itI = AssignedReferees(g).begin(); itI != prev(AssignedReferees(g).end()); ++itI)
			for (set<int>::iterator itJ = next(itI); itJ != AssignedReferees(g).end(); ++itJ) {
				const Referee &refereeI = in.GetReferee(*itI);
				const Referee &refereeJ = in.GetReferee(*itJ);
				
				if (refereeI.IncompatibleReferee(refereeJ.Code()))
					refereeIncompatibility++;

				if (refereeJ.IncompatibleReferee(refereeI.Code()))
					refereeIncompatibility++;
			}
	}
	return refereeIncompatibility;
}

int RA_Output::TeamIncompatibility(int g) const {
	int teamIncompatibility = 0;
	const Team &homeTeam = in.GetTeam(in.GetGame(g).HomeTeam());
	const Team &awayTeam = in.GetTeam(in.GetGame(g).AwayTeam());

	for (set<int>::iterator it = AssignedReferees(g).begin(); it != AssignedReferees(g).end(); ++it) {
		const Referee &referee = in.GetReferee(*it);

		if (referee.IncompatibleTeam(homeTeam.Code()))
			teamIncompatibility++;

		if (referee.IncompatibleTeam(awayTeam.Code()))
			teamIncompatibility++;
	}
	return teamIncompatibility;
}

void RA_Output::Assign(int r, int g) {
	referees[r - 1].insert(g);
	games[g - 1].insert(r);
}

void RA_Output::Unassign(int r, int g) {
	referees[r - 1].erase(g);
	games[g - 1].erase(r);
}

void RA_Output::UnassignAll(int g) {
	vector<int> removeReferees;

	for (set<int>::iterator it = AssignedReferees(g).begin(); it != AssignedReferees(g).end(); ++it)
		removeReferees.push_back(in.GetReferee(*it).Code());

	for (int r : removeReferees)
		Unassign(r, g);
}

int RA_Output::ComputeCost() const {
	int lackOfExperience = 0;
	int optionalReferee = 0;
	int refereeIncompatibility = 0;
	int teamIncompatibility = 0;
	int gamesDistribution = 0;
	int totalDistance = 0;
	int assignmentFrequency = 0;
	int cost;

	for (long unsigned int g = 1; g <= games.size(); g++) {
		if (LackOfExperience(g))
			lackOfExperience++;

		optionalReferee += OptionalReferee(g);

		refereeIncompatibility += RefereeIncompatibility(g);

		teamIncompatibility += TeamIncompatibility(g);
	}

	for (long unsigned int r = 1; r <= referees.size(); r++) {
		gamesDistribution += GamesDistribution(r);

		totalDistance += TotalDistance(r);

		for (int t = 1; t <= in.NumTeams(); t++)
			assignmentFrequency += AssignmentFrequency(r, t);
	}

	lackOfExperience *= in.LackOfExperienceWeight();
	optionalReferee *= in.OptionalRefereeWeight();
	refereeIncompatibility *= in.RefereeIncompatibilityWeight();
	teamIncompatibility *= in.TeamIncompatibilityWeight();
	gamesDistribution *= in.GamesDistributionWeight();
	totalDistance *= in.TotalDistanceWeight();
	assignmentFrequency *= in.AssignmentFrequencyWeight();

	cost = lackOfExperience + optionalReferee + refereeIncompatibility + teamIncompatibility + gamesDistribution + totalDistance + assignmentFrequency;

	return cost;
}

unsigned RA_Output::ComputeViolations() const {
	unsigned violations = 0;

	for (long unsigned int i = 1; i <= games.size(); i++) {
		if (!HasMinimumReferees(i))
			violations++;

		if (!LeqThanMaximumReferees(i))
			violations++;
	}

	for (long unsigned int i = 1; i <= referees.size(); i++) {
		if (!FeasibleTravelDistance(i))
			violations++;

		if (!RefereeAvailability(i))
			violations++;

		if (!HasMinimumLevel(i))
			violations++;
	}

	return violations;
}

bool RA_Output::HasViolations() const {
	for (long unsigned int i = 1; i <= games.size(); i++) {
		if (!HasMinimumReferees(i))
			return true;

		if (!LeqThanMaximumReferees(i))
			return true;
	}

	for (long unsigned int i = 1; i <= referees.size(); i++) {
		if (!FeasibleTravelDistance(i))
			return true;

		if (!RefereeAvailability(i))
			return true;

		if (!HasMinimumLevel(i))
			return true;
	}

	return false;
}

int RA_Output::TravelTime(Coordinates2D address1, Coordinates2D address2) const {
	int distance = EuclideanDistance(address1, address2);	// km
	return static_cast<int>(ceil((distance / averageSpeed) * 60));
}

ostream& operator<<(ostream& os, const RA_Output& out) {
	int digitsTeam = 1;
	int teams = out.in.NumTeams();
	while (teams /= 10)
		digitsTeam++;

	int digitsAssignedReferees = 1;
	int maxAssignedReferees = 0;
	for (long unsigned int g = 1; g <= out.games.size(); g++) {
		if (static_cast<int>(out.AssignedReferees(g).size()) > maxAssignedReferees)
			maxAssignedReferees = out.AssignedReferees(g).size();
	}
	while (maxAssignedReferees /= 10)
		digitsAssignedReferees++;

	int digitsReferee = 1;
	int referees = out.in.NumReferees();
	while (referees /= 10)
		digitsReferee++;

	for (long unsigned int g = 1; g <= out.games.size(); g++) {
		os.width(digitsTeam + 1); os.fill(' ');
		os << right << "T" + to_string(out.in.GetTeam(out.in.GetGame(g).HomeTeam()).Code()) << " ";
		os.width(digitsTeam + 1); os.fill(' ');
		os << right << "T" + to_string(out.in.GetTeam(out.in.GetGame(g).AwayTeam()).Code()) << " ";
		os.width(digitsAssignedReferees); os.fill(' ');
		os << right << out.AssignedReferees(g).size() << " ";

		for (set<int>::iterator it = out.AssignedReferees(g).begin(); it != out.AssignedReferees(g).end(); ++it) {
			os.width(digitsReferee + 1); os.fill(' ');
			os << right << "R" + to_string(out.in.GetReferee(*it).Code()) << " ";
		}

		os << endl;
	}

	return os;
}

istream& operator>>(istream& is, RA_Output& out) {
	int homeTeam, awayTeam, assignedReferees, referee, i, hT, aT;
	char ch;

	out.Reset();

	for (long unsigned int g = 1; g <= out.games.size(); g++) {
		is >> ch >> homeTeam >> ch >> awayTeam;

		for (i = 1; i <= out.in.NumGames(); i++) {
			const Game &game = out.in.GetGame(i);
			hT = out.in.GetTeam(game.HomeTeam()).Code();
			aT = out.in.GetTeam(game.AwayTeam()).Code();

			if (homeTeam == hT && awayTeam == aT)
				break;
		}

		is >> assignedReferees;

		for (int j = 0; j < assignedReferees; j++) {
			is >> ch >> referee;
			out.Assign(referee, i);
		}
	}

	return is;
}
