DATA = ../../Data/
OPTIONS = -std=c++11 -Wall -O3 # -Wextra -Wfatal-errors # -g
COMPOPTS = -I$(DATA) $(OPTIONS)

TestRABacktracking.exe: TestRABacktracking.o RA_Backtracking.o Data
	g++ -o TestRABacktracking.exe TestRABacktracking.o RA_Backtracking.o $(DATA)*.o

TestRABacktracking.o: RA_Backtracking.hh BacktrackingOpt.hh TestRABacktracking.cc
	g++ -c $(COMPOPTS) TestRABacktracking.cc

RA_Backtracking.o: RA_Backtracking.hh RA_Backtracking.cc
	g++ -c $(COMPOPTS) RA_Backtracking.cc

Data:
	cd $(DATA) && $(MAKE) && rm -f DriverTest.o DriverTest.exe

clean:
	rm -f RA_Backtracking.o TestRABacktracking.o TestRABacktracking.exe && cd $(DATA) && $(MAKE) clean
