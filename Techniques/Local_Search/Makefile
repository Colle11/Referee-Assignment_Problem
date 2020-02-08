EASYLOCAL = ../../easylocal-3
DATA = ../../Data/
GREEDY = ../Greedy/
RANDOM = ../../Utils/Random_Generator/
FLAGS = -std=c++14 -Wall -O3 # -Wextra -Wfatal-errors # -g
COMPOPTS = -I$(EASYLOCAL)/include -I$(DATA) -I$(GREEDY) $(FLAGS)
LINKOPTS = -lboost_program_options -pthread

SOURCE_FILES = RA_Basics.cc RA_Helpers.cc  RA_Main.cc
OBJECT_FILES = RA_Basics.o RA_Helpers.o RA_Main.o
HEADER_FILES = RA_Basics.hh RA_Helpers.hh  

TestRALocalSearch.exe: $(OBJECT_FILES) Data Greedy
	g++ $(OBJECT_FILES) $(DATA)*.o $(GREEDY)*.o $(RANDOM)*.o $(LINKOPTS) -o TestRALocalSearch.exe

RA_Basics.o: RA_Basics.cc RA_Basics.hh
	g++ -c $(COMPOPTS) RA_Basics.cc

RA_Helpers.o: RA_Helpers.cc RA_Helpers.hh RA_Basics.hh
	g++ -c $(COMPOPTS) RA_Helpers.cc

RA_Main.o: RA_Main.cc RA_Helpers.hh RA_Basics.hh
	g++ -c $(COMPOPTS) RA_Main.cc

Data:
	cd $(DATA) && $(MAKE) && rm -f DriverTest.o DriverTest.exe

Greedy:
	cd $(GREEDY) && $(MAKE) && rm -f RA_Driver.o RA_Driver.exe

clean:
	rm -f $(OBJECT_FILES) TestRALocalSearch.exe && cd $(GREEDY) && $(MAKE) clean && cd $(DATA) && $(MAKE) clean

