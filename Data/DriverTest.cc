// File DriverTest.cc

#include <iostream>
#include "RA_Data.hh"

int main(int argc, char* argv[]) {
	string instance;
	if (argc == 1) {
		cout << "Name of the file containing the instance: ";
		cin >> instance;
	} else if (argc == 2) {
		instance = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " [input_file]" << endl;
		exit(1);
	}

	RA_Input in(instance);
	cout << in << endl;
	RA_Output out(in);
	cout << out << endl;

	return 0;
}
