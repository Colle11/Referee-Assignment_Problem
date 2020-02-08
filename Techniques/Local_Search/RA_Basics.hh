// File RA_Basics.hh
#ifndef RA_BASICS_HH
#define RA_BASICS_HH

#include "RA_Data.hh"
#include <vector>
#include <set>

class RA_State : public RA_Output
{  
  friend ostream& operator<<(ostream& os, const RA_State& st);
  friend bool operator==(const RA_State& st1, const RA_State& st2);
public:
  RA_State(const RA_Input& in);
  RA_State& operator=(const RA_State& st);
};

/*  Syntax: g: {Ri,...,Rj} -> {Rk,...,Rl}
    where 1 <= g <= number_of_games is a game and
          forall 1 <= i <= number_of_referees Ri is a referee.
    The set to the left of the arrow, i.e. {Ri,...,Rj}, must be equal to that of the currently
    assigned referees to g. Whereas the one on the right, i.e. {Rk,...,Rl}, is the set of new
    assigned referees to g.
*/
class ChangeAssignedReferees
{
  friend bool operator==(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2);
  friend bool operator!=(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2);
  friend bool operator<(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2);
  friend ostream& operator<<(ostream& os, const ChangeAssignedReferees& mv);
  friend istream& operator>>(istream& is, ChangeAssignedReferees& mv);
public:
  ChangeAssignedReferees();
  int game;
  set<int> oldAssignedReferees, newAssignedReferees;
};

/*  Syntax: g: Ri -> Rj
    where 1 <= g <= number_of_games is a game and
          forall 1 <= i <= number_of_referees Ri is a referee.
    The referee on the left of the arrow, i.e. Ri, is the removed one and therefore must belong
    to the set of the currently assigned referees to g. Whereas the referee on the right, i.e.
    Rj, is the assigned one and therefore must NOT belong. 0 in place of Ri means remove no
    referee, while in place of Rj means assign no referee.
*/
class AddRemoveReferee
{
	friend bool operator==(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2);
	friend bool operator!=(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2);
	friend bool operator<(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2);
	friend ostream& operator<<(ostream& os, const AddRemoveReferee& mv);
	friend istream& operator>>(istream& is, AddRemoveReferee& mv);
public:
	AddRemoveReferee();
	int game;
	int remReferee, addReferee;
};
#endif

