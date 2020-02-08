// File RA_Backtracking.hh

#ifndef RA_BACKTRACKING_HH
#define RA_BACKTRACKING_HH

#include "BacktrackingOpt.hh"
#include <RA_Data.hh>

class BacktrackingRAOpt : public BacktrackingOpt<RA_Input, RA_Output, int> {

public:
	BacktrackingRAOpt(const RA_Input& in, unsigned fl) : BacktrackingOpt(in, fl) {}

protected:
	// hot-spots
	void FirstOfLevel();
	bool NextOfLevel();
	bool Feasible();
	int Cost();
	// cold-spots
	bool NonImprovingBranch();
	void GoUpOneLevel();

private:
	bool HasNext(int g);

};

#endif
