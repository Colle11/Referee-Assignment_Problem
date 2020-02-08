// File RA_Enumeration.cc

#include "RA_Enumeration.hh"

void EnumerationRAOpt::First() {
	for (int g = 1; g <= in.NumGames(); g++) {
		const Division &division = in.GetDivision(in.GetGame(g).Division());

		for (int r = 1; r <= division.MinReferees(); r++)
			out.Assign(r, g);
	}
}

bool EnumerationRAOpt::Next() {
	for (int g = 1; g <= in.NumGames(); g++) {
		if (HasNext(g))
			return true;
		else {
			out.UnassignAll(g);
			const Division &division = in.GetDivision(in.GetGame(g).Division());

			for (int r = 1; r <= division.MinReferees(); r++)
				out.Assign(r, g);
		}
	}

	return false;
}

bool EnumerationRAOpt::Feasible() {
	return !out.HasViolations();
}

int EnumerationRAOpt::Cost() {
	return out.ComputeCost();
}

bool EnumerationRAOpt::HasNext(int g) {
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
