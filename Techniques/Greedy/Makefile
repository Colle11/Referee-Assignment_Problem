DATA = ../../Data/
RANDOM = ../../Utils/Random_Generator/
OPTIONS = -std=c++14 -Wall -O3 # -Wextra -Wfatal-errors # -g
COMPOPTS = -I$(DATA) -I$(RANDOM) $(OPTIONS)

RA_Driver.exe: RA_Driver.o RA_Greedy.o Data Random
	g++ -o RA_Driver.exe RA_Driver.o RA_Greedy.o $(DATA)*.o $(RANDOM)*.o

RA_Driver.o: RA_Driver.cc RA_Greedy.hh
	g++ -c $(COMPOPTS) RA_Driver.cc

RA_Greedy.o: RA_Greedy.cc RA_Greedy.hh
	g++ -c $(COMPOPTS) RA_Greedy.cc

Data:
	cd $(DATA) && $(MAKE) && rm -f DriverTest.o DriverTest.exe

Random:
	cd $(RANDOM) && $(MAKE)

clean:
	rm -f RA_Greedy.o RA_Driver.o RA_Driver.exe && cd $(RANDOM) && $(MAKE) clean && cd $(DATA) && $(MAKE) clean
