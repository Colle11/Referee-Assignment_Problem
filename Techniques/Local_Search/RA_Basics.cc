// File RA_Basics.cc
#include "RA_Basics.hh"

RA_State::RA_State(const RA_Input& i) 
  : RA_Output(i) {}

RA_State& RA_State::operator=(const RA_State& st)
{
  games = st.games;
  referees = st.referees;
  return *this;
}
  
bool operator==(const RA_State& st1, const RA_State& st2)
{
  for (int g = 1; g <= st1.in.NumGames(); g++)
    if (st1.AssignedReferees(g) != st2.AssignedReferees(g))
      return false;

  // for (int r = 1; r <= st1.in.NumReferees(); r++)
  //   if (st1.AssignedGames(r) != st2.AssignedGames(r))
  //     return false;

  return true;
}

ostream& operator<<(ostream& os, const RA_State& st)
{
  os << "Games (with the assigned referees):" << endl;
  int digitsGame = 1;
  int games = st.in.NumGames();
  while (games /= 10)
    digitsGame++;

  int digitsTeam = 1;
  int teams = st.in.NumTeams();
  while (teams /= 10)
    digitsTeam++;

  int digitsAssignedReferees = 1;
  int maxAssignedReferees = 0;
  for (int g = 1; g <= st.in.NumGames(); g++)
  {
    if (static_cast<int>(st.AssignedReferees(g).size()) > maxAssignedReferees)
      maxAssignedReferees = st.AssignedReferees(g).size();
  }
  while (maxAssignedReferees /= 10)
    digitsAssignedReferees++;

  int digitsReferee = 1;
  int referees = st.in.NumReferees();
  while (referees /= 10)
    digitsReferee++;

  for (int g = 1; g <= st.in.NumGames(); g++)
  {
  	os.width(digitsGame); os.fill(' ');
  	os << right << g << ": ";
    os.width(digitsTeam + 1); os.fill(' ');
    os << right << "T" + to_string(st.in.GetTeam(st.in.GetGame(g).HomeTeam()).Code()) << " ";
    os.width(digitsTeam + 1); os.fill(' ');
    os << right << "T" + to_string(st.in.GetTeam(st.in.GetGame(g).AwayTeam()).Code()) << " ";
    os.width(digitsAssignedReferees); os.fill(' ');
    os << right << st.AssignedReferees(g).size() << " ";

    for (set<int>::iterator it = st.AssignedReferees(g).begin(); it != st.AssignedReferees(g).end(); ++it)
    {
      os.width(digitsReferee + 1); os.fill(' ');
      os << right << "R" + to_string(st.in.GetReferee(*it).Code()) << " ";
    }

    os << endl;
  }

  os << endl << "Referees (with the assigned games):" << endl;
  int digitsAssignedGames = 1;
  int maxAssignedGames = 0;
  for (int r = 1; r <= st.in.NumReferees(); r++)
  {
    if (static_cast<int>(st.AssignedGames(r).size()) > maxAssignedGames)
      maxAssignedGames = st.AssignedGames(r).size();
  }
  while (maxAssignedGames /= 10)
    digitsAssignedGames++;

  for (int r = 1; r <= st.in.NumReferees(); r++)
  {
    os.width(digitsReferee + 1); os.fill(' ');
    os << right << "R" + to_string(st.in.GetReferee(r).Code()) << " ";
    os.width(digitsAssignedGames); os.fill(' ');
    os << right << st.AssignedGames(r).size() << " ";

    for (set<int>::iterator it = st.AssignedGames(r).begin(); it != st.AssignedGames(r).end(); ++it)
    {
      os << "<";
      os.width(digitsTeam + 1); os.fill(' ');
      os << right << "T" + to_string(st.in.GetTeam(st.in.GetGame(*it).HomeTeam()).Code()) << " ";
      os.width(digitsTeam + 1); os.fill(' ');
      os << right << "T" + to_string(st.in.GetTeam(st.in.GetGame(*it).AwayTeam()).Code());
      os << "> ";
    }

    os << endl << endl;
  }

  return os;
}

ChangeAssignedReferees::ChangeAssignedReferees()
{
  game = 1;
  oldAssignedReferees = set<int>();
  newAssignedReferees = set<int>();
}

bool operator==(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2)
{
  return mv1.game == mv2.game && mv1.oldAssignedReferees == mv2.oldAssignedReferees && mv1.newAssignedReferees == mv2.newAssignedReferees;
}

bool operator!=(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2)
{
  return mv1.game != mv2.game || mv1.oldAssignedReferees != mv2.oldAssignedReferees || mv1.newAssignedReferees != mv2.newAssignedReferees;
}

bool operator<(const ChangeAssignedReferees& mv1, const ChangeAssignedReferees& mv2)
{
  if (mv1.game < mv2.game)
    return true;
  else if (mv1.game > mv2.game)
    return false;
  else
  {
    if (mv1.oldAssignedReferees.size() < mv2.oldAssignedReferees.size())
      return true;
    else if (mv1.oldAssignedReferees.size() > mv2.oldAssignedReferees.size())
      return false;
    else if (mv1.oldAssignedReferees < mv2.oldAssignedReferees)
      return true;
    else if (mv1.oldAssignedReferees > mv2.oldAssignedReferees)
      return false;
    else
    {
      if (mv1.newAssignedReferees.size() < mv2.newAssignedReferees.size())
        return true;
      else if (mv1.newAssignedReferees.size() > mv2.newAssignedReferees.size())
        return false;
      else if (mv1.newAssignedReferees < mv2.newAssignedReferees)
        return true;
      else if (mv1.newAssignedReferees > mv2.newAssignedReferees)
        return false;
      else
        return false;
    }
  }
}

istream& operator>>(istream& is, ChangeAssignedReferees& mv)
{
  char ch;
  int referee;

  is >> mv.game >> ch >> ch;
  while ((ch = is.peek()) == ' ')
  	is.get(ch);

  while (ch != '}')
  {
    is >> ch >> referee;

    while ((ch = is.peek()) == ' ')
      is.get(ch);
    if (ch != '}')
      is >> ch;

    mv.oldAssignedReferees.insert(referee);
  }

  is >> ch >> ch >> ch >> ch;
  while ((ch = is.peek()) == ' ')
  	is.get(ch);

  while (ch != '}')
  {
    is >> ch >> referee;

    while ((ch = is.peek()) == ' ')
      is.get(ch);
    if (ch != '}')
      is >> ch;

    mv.newAssignedReferees.insert(referee);
  }

  is >> ch;

  return is;
}

ostream& operator<<(ostream& os, const ChangeAssignedReferees& mv)
{
  set<int>::iterator it;

  os << mv.game << ": " << "{";

  if (!mv.oldAssignedReferees.empty())
  {
    for (it = mv.oldAssignedReferees.begin(); it != prev(mv.oldAssignedReferees.end()); ++it)
      os << "R" << *it << ",";
  
    os << "R" << *it;
  }
  os << "} -> {";

  if (!mv.newAssignedReferees.empty())
  {
    for (it = mv.newAssignedReferees.begin(); it != prev(mv.newAssignedReferees.end()); ++it)
      os << "R" << *it << ",";
  
    os << "R" << *it;
  }
  os << "}";

  return os;
}

AddRemoveReferee::AddRemoveReferee()
{
  game = 1;
  remReferee = 0;
  addReferee = 0;
}

bool operator==(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2)
{
  return mv1.game == mv2.game && mv1.remReferee == mv2.remReferee && mv1.addReferee == mv2.addReferee;
}

bool operator!=(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2)
{
  return mv1.game != mv2.game || mv1.remReferee != mv2.remReferee || mv1.addReferee != mv2.addReferee;
}

bool operator<(const AddRemoveReferee& mv1, const AddRemoveReferee& mv2)
{
  if (mv1.game < mv2.game)
    return true;
  else if (mv1.game > mv2.game)
    return false;
  else
  {
    return mv1.remReferee < mv2.remReferee || (mv1.remReferee == mv2.remReferee && mv1.addReferee < mv2.addReferee);
  }
}

istream& operator>>(istream& is, AddRemoveReferee& mv)
{
  char ch;

  is >> mv.game >> ch;
  while ((ch = is.peek()) == ' ')
  	is.get(ch);

  if (ch != '0')
    is >> ch;

  is >> mv.remReferee >> ch >> ch;
  while ((ch = is.peek()) == ' ')
  	is.get(ch);

  if (ch != '0')
    is >> ch;

  is >> mv.addReferee;

  return is;
}

ostream& operator<<(ostream& os, const AddRemoveReferee& mv)
{
  os << mv.game << ": ";

  if (mv.remReferee != 0)
    os << "R";

  os << mv.remReferee << " -> ";

  if (mv.addReferee != 0)
    os << "R";

  os << mv.addReferee;

  return os;
}
