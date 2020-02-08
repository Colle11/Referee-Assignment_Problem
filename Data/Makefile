OPTIONS = -std=c++11 -Wall -O3 # -Wextra -Wfatal-errors # -g

DriverTest.exe: DriverTest.o RA_Data.o Referee.o Arena.o Team.o Division.o Game.o Coordinates2D.o Date.o Time.o Event.o
	g++ -o DriverTest.exe DriverTest.o RA_Data.o Referee.o Arena.o Team.o Division.o Game.o Coordinates2D.o Date.o Time.o Event.o

RA_Data.o: RA_Data.cc RA_Data.hh Division.hh Referee.hh Arena.hh Team.hh Game.hh
	g++ $(OPTIONS) -c RA_Data.cc

Referee.o: Referee.cc Referee.hh Coordinates2D.hh Event.hh
	g++ $(OPTIONS) -c Referee.cc

Arena.o: Arena.cc Arena.hh Coordinates2D.hh
	g++ $(OPTIONS) -c Arena.cc

Team.o: Team.cc Team.hh
	g++ $(OPTIONS) -c Team.cc

Division.o: Division.cc Division.hh
	g++ $(OPTIONS) -c Division.cc

Game.o: Game.cc Game.hh Event.hh
	g++ $(OPTIONS) -c Game.cc

Coordinates2D.o: Coordinates2D.cc Coordinates2D.hh
	g++ $(OPTIONS) -c Coordinates2D.cc

Date.o: Date.cc Date.hh
	g++ $(OPTIONS) -c Date.cc

Time.o: Time.cc Time.hh
	g++ $(OPTIONS) -c Time.cc

Event.o: Event.cc Event.hh Date.hh Time.hh
	g++ $(OPTIONS) -c Event.cc

DriverTest.o: DriverTest.cc RA_Data.hh
	g++ $(OPTIONS) -c DriverTest.cc

clean:
	rm -f RA_Data.o Referee.o Arena.o Team.o Division.o Game.o Coordinates2D.o Date.o Time.o Event.o DriverTest.o DriverTest.exe
