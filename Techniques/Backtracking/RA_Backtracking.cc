// File RA_Backtracking.cc

#include "RA_Backtracking.hh"

void BacktrackingRAOpt::FirstOfLevel() {
	int g = level;
	const Division &division = in.GetDivision(in.GetGame(g).Division());

	for (int r = 1; r <= division.MinReferees(); r++)
		out.Assign(r, g);
}

bool BacktrackingRAOpt::NextOfLevel() {
	int g = level;

	return HasNext(g);
}

bool BacktrackingRAOpt::Feasible() {
	int g = level;
	int referee;

	if (!out.HasMinimumReferees(g))
		return false;

	if (!out.LeqThanMaximumReferees(g))
		return false;

	for (set<int>::iterator it = out.AssignedReferees(g).begin(); it != out.AssignedReferees(g).end(); ++it) {
		referee = in.GetReferee(*it).Code();

		if (!out.FeasibleTravelDistance(referee))
			return false;

		if (!out.RefereeAvailability(referee))
			return false;

		if (!out.HasMinimumLevel(referee))
			return false;
	}

	return true;
}

int BacktrackingRAOpt::Cost() {
	return out.ComputeCost();
}

bool BacktrackingRAOpt::NonImprovingBranch() {
	return false;
	// return out.ComputeCost() >= best_cost;	// NOT (exactly) correct due to the approximations made in the GamesDistribution and AssignmentFrequency soft constraints.
												// There are instances for which the optimal solution is NOT found. As an example, test the Handcrafted_Instances/Backtracking_NIB.txt
												// instance with all weights equal 0 except those for GamesDistribution and AssignmentFrequency.
}

void BacktrackingRAOpt::GoUpOneLevel() {
	int g = level;
	out.UnassignAll(g);
	BacktrackingOpt::GoUpOneLevel();
}

bool BacktrackingRAOpt::HasNext(int g) {
	const Division &division = in.GetDivision(in.GetGame(g).Division());
	set<int>::reverse_iterator rit;
	vector<int> removeReferees;
	int referee;

	for (rit = out.AssignedReferees(g).rbegin(); rit != out.AssignedReferees(g).rend(); ++rit) {
		referee = in.GetReferee(*rit).Code();

		if (referee == in.NumReferees() - static_cast<int>(removeReferees.size()))
			removeReferees.push_back(referee);
		else
			break;
	}

	if (static_cast<int>(removeReferees.size()) == division.MaxReferees())
		return false;

	for (int r : removeReferees)
		out.Unassign(r, g);

	if (out.AssignedReferees(g).empty()) {
		for (int r = 1; r <= static_cast<int>(removeReferees.size()) + 1; r++)
			out.Assign(r, g);
	} else {
		rit = out.AssignedReferees(g).rbegin();
		referee = in.GetReferee(*rit).Code();
		out.Unassign(referee, g);
		referee++;
		out.Assign(referee, g);

		for (int i = 0; i < static_cast<int>(removeReferees.size()); i++) {
			referee++;
			out.Assign(referee, g);
		}
	}

	return true;
}
