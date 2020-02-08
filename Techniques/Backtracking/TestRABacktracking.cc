// File TestRABacktracking.cc

#include "RA_Backtracking.hh"
#include <iostream>
#include <chrono>
#include <string>

using namespace std::chrono;

int main(int argc, char* argv[]) {
	string instance;
	int loe, gd, td, o, af, ri, ti;	// soft constraints weights

	if (argc == 1) {
		cout << "Name of the file containing the instance: ";
    	cin >> instance;
    	cout << "LackOfExperience weight: ";
  		cin >> loe;
  		cout << "GamesDistribution weight: ";
  		cin >> gd;
  		cout << "TotalDistance weight: ";
  		cin >> td;
  		cout << "OptionalReferee weight: ";
  		cin >> o;
  		cout << "AssignmentFrequency weight: ";
  		cin >> af;
  		cout << "RefereeIncompatibility weight: ";
  		cin >> ri;
  		cout << "TeamIncompatibility weight: ";
  		cin >> ti;
	} else if (argc == 2) {
		instance = argv[1];
		cout << "LackOfExperience weight: ";
  		cin >> loe;
  		cout << "GamesDistribution weight: ";
  		cin >> gd;
  		cout << "TotalDistance weight: ";
  		cin >> td;
  		cout << "OptionalReferee weight: ";
  		cin >> o;
  		cout << "AssignmentFrequency weight: ";
  		cin >> af;
  		cout << "RefereeIncompatibility weight: ";
  		cin >> ri;
  		cout << "TeamIncompatibility weight: ";
  		cin >> ti;
  	} else if (argc == 9) {
  		instance = argv[1];
  		loe = stoi(argv[2]);
  		gd = stoi(argv[3]);
  		td = stoi(argv[4]);
  		o = stoi(argv[5]);
  		af = stoi(argv[6]);
  		ri = stoi(argv[7]);
  		ti = stoi(argv[8]);
	} else {
		cerr << "Usage: " << argv[0] << " [input_file [loe gd td o af ri ti]]" << endl;
      	exit(1);
	}

	RA_Input in(instance);

  	in.SetLackOfExperienceWeight(loe);
	in.SetGamesDistributionWeight(gd);
	in.SetTotalDistanceWeight(td);
	in.SetOptionalRefereeWeight(o);
	in.SetAssignmentFrequencyWeight(af);
	in.SetRefereeIncompatibilityWeight(ri);
	in.SetTeamIncompatibilityWeight(ti);

	BacktrackingRAOpt solver(in, in.NumGames());

	auto start = high_resolution_clock::now();
	bool hasSolution = solver.Search();
	auto stop = high_resolution_clock::now();
	auto duration = stop - start;
	if (hasSolution)
		cout << "Best solution found " << endl << solver.BestSolution()
			 <<   " (" << solver.NumNodes() << " nodes visited)" << endl;
	else
		cout << "No solution exists" << endl;
	cout << "Elapsed time: " << duration_cast<milliseconds>(duration).count() / 1000.0 << " s" << endl;
	return 0;
}
