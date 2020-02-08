DATA = ../../Data/
OPTIONS = -std=c++11 -Wall -O3 # -Wextra -Wfatal-errors # -g
COMPOPTS = -I$(DATA) $(OPTIONS)

TestRAEnumeration.exe: TestRAEnumeration.o RA_Enumeration.o Data
	g++ -o TestRAEnumeration.exe TestRAEnumeration.o RA_Enumeration.o $(DATA)*.o

TestRAEnumeration.o: RA_Enumeration.hh EnumerationOpt.hh TestRAEnumeration.cc
	g++ -c $(COMPOPTS) TestRAEnumeration.cc

RA_Enumeration.o: RA_Enumeration.hh RA_Enumeration.cc
	g++ -c $(COMPOPTS) RA_Enumeration.cc

Data:
	cd $(DATA) && $(MAKE) && rm -f DriverTest.o DriverTest.exe

clean:
	rm -f RA_Enumeration.o TestRAEnumeration.o TestRAEnumeration.exe && cd $(DATA) && $(MAKE) clean
