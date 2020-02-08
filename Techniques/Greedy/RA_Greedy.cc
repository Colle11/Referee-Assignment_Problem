// File RA_Greedy.cc

#include <climits>
#include <algorithm>
#include <iterator>
#include <vector>
#include "RA_Greedy.hh"
#include "Random.hh"

/*	Greedy steps:
	(1)	Randomly choose the first game g to be assigned
	(2)	If the number of referees assigned to g is less than the maximum number of
		assignable referees, then:
		(2.1)	If the number of referees assigned to g is less than the minimum
				number of referees to be assigned, then:
				(2.1.1)	Assign to g the referee that costs less for the current partial solution
				(2.1.2)	Else:	Assign to g the referee that minimizes the current partial
								solution, if such referee exists (breaking ties randomly)
	(3)	Randomly take another game to be assigned and goto (2), until not all the games have been
      processed
	(4)	Repeat the previous steps until at least one referee is assigned to a game

	Required invariant: at each referee assignment hard constraints are NOT violated, except
						for the minimum number of referees, of course.
*/
void GreedyRASolver(const RA_Input& in, RA_Output& out) {
	bool hasAssigned;
	int deltaCost, minDeltaCost, assignReferee, equalMinDeltaNum;
	set<int> oldAssignedReferees, newAssignedReferees, referees, diffReferees;
	set<int>::iterator rbeg, rend, abeg, aend;
	vector<int> games;

	for (int g = 1; g <= in.NumGames(); g++)
		games.push_back(g);

	for (int r = 1; r <= in.NumReferees(); r++)
		referees.insert(r);

	rbeg = referees.begin();
	rend = referees.end();

	out.Reset();

	do {
		hasAssigned = false;
		random_shuffle(games.begin(), games.end());

		for (int game : games) {
			const Division &division = in.GetDivision(in.GetGame(game).Division());

			if (static_cast<int>(out.AssignedReferees(game).size()) < division.MaxReferees()) {
				assignReferee = 0;
				equalMinDeltaNum = 1;

				if (static_cast<int>(out.AssignedReferees(game).size()) < division.MinReferees())
    				minDeltaCost = INT_MAX;
    			else
    				minDeltaCost = 0;

    			diffReferees.clear();
    			abeg = out.AssignedReferees(game).begin();
    			aend = out.AssignedReferees(game).end();
    			set_difference(rbeg, rend, abeg, aend, inserter(diffReferees, diffReferees.end()));

				for (int r : diffReferees) {
					oldAssignedReferees = out.AssignedReferees(game);
					newAssignedReferees = out.AssignedReferees(game);
  					newAssignedReferees.insert(r);

					if (FeasibleTravelDistanceDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees) > 0)
    					continue;

  					if (RefereeAvailabilityDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees) > 0)
    					continue;

  					if (MinimumLevelDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees) > 0)
    					continue;

    				deltaCost = 0;
    				deltaCost += in.LackOfExperienceWeight() * LackOfExperienceDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.GamesDistributionWeight() * GamesDistributionDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.TotalDistanceWeight() * TotalDistanceDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.OptionalRefereeWeight() * OptionalRefereeDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.AssignmentFrequencyWeight() * AssignmentFrequencyDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.RefereeIncompatibilityWeight() * RefereeIncompatibilityDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);
    				deltaCost += in.TeamIncompatibilityWeight() * TeamIncompatibilityDeltaCost(in, out, game, oldAssignedReferees, newAssignedReferees);

    				if (deltaCost < minDeltaCost) {
    					minDeltaCost = deltaCost;
    					assignReferee = r;
    					equalMinDeltaNum = 1;
    				} else if (deltaCost == minDeltaCost) {
    					equalMinDeltaNum++;

    					if (Random(1, equalMinDeltaNum) == 1)
    						assignReferee = r;
    				}
				}

				if (assignReferee != 0) {
					out.Assign(assignReferee, game);
					hasAssigned = true;
				}
			}
		}

	} while (hasAssigned);
}

/***************************************************************************
 * Delta Cost Support Functions:
 ***************************************************************************/
int MinimumRefereesDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int division = in.GetGame(game).Division();
  int minReferees = in.GetDivision(division).MinReferees();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());

  if (numAssignedReferees < minReferees && numNewAssignedReferees >= minReferees)
    return -1;
  else if (numAssignedReferees >= minReferees && numNewAssignedReferees < minReferees)
    return 1;
  else
    return 0;
}

int MaximumRefereesDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int division = in.GetGame(game).Division();
  int maxReferees = in.GetDivision(division).MaxReferees();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());

  if (numAssignedReferees > maxReferees && numNewAssignedReferees <= maxReferees)
    return -1;
  else if (numAssignedReferees <= maxReferees && numNewAssignedReferees > maxReferees)
    return 1;
  else
    return 0;
}

int FeasibleTravelDistanceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg, itn;
  set<int>::reverse_iterator ritp;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int refereeCode;
  bool oldFeasibleTravelDistance = true, newFeasibleTravelDistance = true, mvgameOverlapping = false;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    refereeCode = in.GetReferee(*it).Code();

    // here AssignedGames(refereeCode) is certainly NOT empty
    for (itg = out.AssignedGames(refereeCode).begin(); itg != prev(out.AssignedGames(refereeCode).end()); ++itg) 
    {
      const Game &previousGame = in.GetGame(*itg);
      const Game &nextGame = in.GetGame(*next(itg));

      if (*itg != game && *next(itg) != game &&
          out.OverlappingGames(previousGame, nextGame, refereeCode))
      {
        oldFeasibleTravelDistance = false;
        break;
      }
      else if ((*itg == game || *next(itg) == game) &&
               out.OverlappingGames(previousGame, nextGame, refereeCode))
      {
        mvgameOverlapping = true;
      }
    }

    itg = out.AssignedGames(refereeCode).find(game);
    ritp = make_reverse_iterator(itg);
    itn = next(itg);
    if (ritp != out.AssignedGames(refereeCode).rend() &&
        itn != out.AssignedGames(refereeCode).end() &&
        out.OverlappingGames(in.GetGame(*ritp), in.GetGame(*itn), refereeCode))
    {
      oldFeasibleTravelDistance = false;
    }

    if (oldFeasibleTravelDistance && mvgameOverlapping)
      cost--;

    oldFeasibleTravelDistance = true;
    mvgameOverlapping = false;
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    refereeCode = in.GetReferee(*it).Code();

    itn = find_if(out.AssignedGames(refereeCode).begin(), out.AssignedGames(refereeCode).end(), [game](const int g)->bool
          {
            return game < g;
          });

    ritp = make_reverse_iterator(itn);

    if (!out.AssignedGames(refereeCode).empty())
    {
      for (itg = out.AssignedGames(refereeCode).begin(); itg != prev(out.AssignedGames(refereeCode).end()); ++itg) {
        const Game &previousGame = in.GetGame(*itg);
        const Game &nextGame = in.GetGame(*next(itg));

        if (out.OverlappingGames(previousGame, nextGame, refereeCode))
          newFeasibleTravelDistance = false;
      }
    }

    if ((itn != out.AssignedGames(refereeCode).end() &&
         out.OverlappingGames(in.GetGame(game), in.GetGame(*itn), refereeCode)) ||
        (ritp != out.AssignedGames(refereeCode).rend() &&
         out.OverlappingGames(in.GetGame(*ritp), in.GetGame(game), refereeCode)))
    {
      mvgameOverlapping = true;
    }

    if (newFeasibleTravelDistance && mvgameOverlapping)
      cost++;

    newFeasibleTravelDistance = true;
    mvgameOverlapping = false;
  }

  return cost;
}

int RefereeAvailabilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  Event mvgameMatch = in.GetGame(game).Match();
  bool oldAvailability = true, newAvailability = true;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Unavailable(mvgameMatch))
    {
      for (itg = out.AssignedGames(*it).begin(); itg != out.AssignedGames(*it).end(); ++itg)
        if (*itg != game)
        {
          const Game &g = in.GetGame(*itg);
          if (in.GetReferee(*it).Unavailable(g.Match()))
          {
            oldAvailability = false;
            break;
          }
        }

      if (oldAvailability)
        cost--;

      oldAvailability = true;
    }


  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Unavailable(mvgameMatch))
    {
      for (itg = out.AssignedGames(*it).begin(); itg != out.AssignedGames(*it).end(); ++itg)
      {
        const Game &g = in.GetGame(*itg);
        if (in.GetReferee(*it).Unavailable(g.Match()))
        {
          newAvailability = false;
          break;
        }
      }

      if (newAvailability)
        cost++;

      newAvailability = true;
    }

  return cost;
}

int MinimumLevelDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itg;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int mvgameLevel = in.GetDivision(in.GetGame(game).Division()).Level();
  bool oldMinimumLevel = true, newMinimumLevel = true;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Level() < mvgameLevel)
    {
      for (itg = out.AssignedGames(*it).begin(); itg != out.AssignedGames(*it).end(); ++itg)
        if (*itg != game)
        {
          const Division &division = in.GetDivision(in.GetGame(*itg).Division());
          if (in.GetReferee(*it).Level() < division.Level())
          {
            oldMinimumLevel = false;
            break;
          }
        }

      if (oldMinimumLevel)
        cost--;

      oldMinimumLevel = true;
    }


  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    if (in.GetReferee(*it).Level() < mvgameLevel)
    {
      for (itg = out.AssignedGames(*it).begin(); itg != out.AssignedGames(*it).end(); ++itg)
      {        
        const Division &division = in.GetDivision(in.GetGame(*itg).Division());
        if (in.GetReferee(*it).Level() < division.Level())
        {
          newMinimumLevel = false;
          break;
        }
      }

      if (newMinimumLevel)
        cost++;

      newMinimumLevel = true;
    }

  return cost;
}

int LackOfExperienceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  set<int> oldDiffReferees, newDiffReferees, stableReferees;
  set<int>::iterator it;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int oldExperience = 0, newExperience = 0, stableExperience = 0;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));
  set_intersection(obeg, oend, nbeg, nend, inserter(stableReferees, stableReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
    oldExperience += in.GetReferee(*it).Experience();

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
    newExperience += in.GetReferee(*it).Experience();

  for (it = stableReferees.begin(); it != stableReferees.end(); ++it)
    stableExperience += in.GetReferee(*it).Experience();

  if (oldExperience + stableExperience <  in.GetGame(game).Experience() &&
      newExperience + stableExperience >= in.GetGame(game).Experience())
    return -1;
  else if (oldExperience + stableExperience >= in.GetGame(game).Experience() &&
           newExperience + stableExperience < in.GetGame(game).Experience())
    return 1;
  else
    return 0;
}

int GamesDistributionDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());
  int oldTotalAssignedGames = 0, newTotalAssignedGames;
  double oldAverageAssignedGames, newAverageAssignedGames;
  int oldGamesDistribution, newGamesDistribution;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (int r = 1; r <= in.NumReferees(); r++)
    oldTotalAssignedGames += out.AssignedGames(r).size();

  newTotalAssignedGames = oldTotalAssignedGames + (numNewAssignedReferees - numAssignedReferees);
  oldAverageAssignedGames = static_cast<double>(oldTotalAssignedGames) / in.NumReferees();
  newAverageAssignedGames = static_cast<double>(newTotalAssignedGames) / in.NumReferees();

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    oldGamesDistribution = static_cast<int>(ceil(fabs(oldAverageAssignedGames - out.AssignedGames(r).size())));

    if (oldDiffReferees.find(r) != oldDiffReferees.end() &&
        newDiffReferees.find(r) == newDiffReferees.end())
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - (out.AssignedGames(r).size() - 1))));
    else if (newDiffReferees.find(r) != newDiffReferees.end() &&
             oldDiffReferees.find(r) == oldDiffReferees.end())
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - (out.AssignedGames(r).size() + 1))));
    else
      newGamesDistribution = static_cast<int>(ceil(fabs(newAverageAssignedGames - out.AssignedGames(r).size())));

    cost += newGamesDistribution - oldGamesDistribution;
  }

  return cost;
}

int TotalDistanceDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it, itf, itn;
  set<int>::reverse_iterator ritp;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  Coordinates2D mvgameArena = in.GetArena(in.GetGame(game).Arena()).Address();
  Coordinates2D refereeHome, prevArena, nextArena;
  int refereeCode;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);
    refereeHome = referee.Address();
    refereeCode = referee.Code();
    itf = out.AssignedGames(refereeCode).find(game);
    ritp = make_reverse_iterator(itf);
    itn = next(itf);

    if ((ritp == out.AssignedGames(refereeCode).rend() ||
         in.GetGame(*itf).Match().StartDate() != in.GetGame(*ritp).Match().StartDate()) &&
        (itn == out.AssignedGames(refereeCode).end() ||
         in.GetGame(*itf).Match().StartDate() != in.GetGame(*itn).Match().StartDate()))
    {
      cost -= EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    }
    else if ((itn == out.AssignedGames(refereeCode).end() ||
              in.GetGame(*itf).Match().StartDate() != in.GetGame(*itn).Match().StartDate()) &&
              in.GetGame(*itf).Match().StartDate() == in.GetGame(*ritp).Match().StartDate()) // redundant condition
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      cost -= EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
      cost += EuclideanDistance(prevArena, refereeHome);
    }
    else if ((ritp == out.AssignedGames(refereeCode).rend() ||
              in.GetGame(*itf).Match().StartDate() != in.GetGame(*ritp).Match().StartDate()) &&
              in.GetGame(*itf).Match().StartDate() == in.GetGame(*itn).Match().StartDate()) // redundant condition
    {
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
      cost += EuclideanDistance(refereeHome, nextArena);
    }
    else  // prev->startDate == mvgame->startDate == next->startDate
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
      cost += EuclideanDistance(prevArena, nextArena);
    }
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);
    refereeHome = referee.Address();
    refereeCode = referee.Code();
    const RA_Input& input(in);

    ritp = find_if(out.AssignedGames(refereeCode).rbegin(), out.AssignedGames(refereeCode).rend(), [&input, game](const int g)->bool
          {
            return g < game &&
                   input.GetGame(g).Match().StartDate() == input.GetGame(game).Match().StartDate() &&
                   input.GetGame(g).Match().StartTime() <= input.GetGame(game).Match().StartTime();
          });

    itn = find_if(out.AssignedGames(refereeCode).begin(), out.AssignedGames(refereeCode).end(), [&input, game](const int g)->bool
          {
            return game < g &&
                   input.GetGame(game).Match().StartDate() == input.GetGame(g).Match().StartDate() &&
                   input.GetGame(game).Match().StartTime() <= input.GetGame(g).Match().StartTime();
          });

    if (ritp == out.AssignedGames(refereeCode).rend() && itn == out.AssignedGames(refereeCode).end())
      cost += EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    else if (ritp != out.AssignedGames(refereeCode).rend() && itn == out.AssignedGames(refereeCode).end())
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      cost -= EuclideanDistance(prevArena, refereeHome);
      cost += EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, refereeHome);
    } else if (ritp == out.AssignedGames(refereeCode).rend() && itn != out.AssignedGames(refereeCode).end())
    {
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(refereeHome, nextArena);
      cost += EuclideanDistance(refereeHome, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
    } else
    {
      prevArena = in.GetArena(in.GetGame(*ritp).Arena()).Address();
      nextArena = in.GetArena(in.GetGame(*itn).Arena()).Address();
      cost -= EuclideanDistance(prevArena, nextArena);
      cost += EuclideanDistance(prevArena, mvgameArena) + EuclideanDistance(mvgameArena, nextArena);
    }
  }

  return cost;
}

int OptionalRefereeDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  const Division &division = in.GetDivision(in.GetGame(game).Division());
  int optionalReferee = division.MaxReferees() - division.MinReferees();
  int oldAbsentOptionalReferees = out.OptionalReferee(game);
  
  int newAssignedOptionalReferees = static_cast<int>(newAssignedReferees.size()) - division.MinReferees();

  if (newAssignedOptionalReferees < 0)
    newAssignedOptionalReferees = 0;

  int newAbsentOptionalReferees = optionalReferee - newAssignedOptionalReferees;

  if (newAbsentOptionalReferees < 0)
    newAbsentOptionalReferees = 0;

  return newAbsentOptionalReferees - oldAbsentOptionalReferees;
}

int AssignmentFrequencyDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  int numAssignedReferees = static_cast<int>(oldAssignedReferees.size());
  int numNewAssignedReferees = static_cast<int>(newAssignedReferees.size());
  int mvgHomeTeamCode = in.GetTeam(in.GetGame(game).HomeTeam()).Code();
  int mvgAwayTeamCode = in.GetTeam(in.GetGame(game).AwayTeam()).Code();
  int oldmvgHTTotalAssignedReferees = 0, oldmvgATTotalAssignedReferees = 0;
  int newmvgHTTotalAssignedReferees, newmvgATTotalAssignedReferees;
  int mvgHTAssignedInputReferee = 0, mvgATAssignedInputReferee = 0;
  double oldmvgHTAverageAssignedReferee, newmvgHTAverageAssignedReferee;
  double oldmvgATAverageAssignedReferee, newmvgATAverageAssignedReferee;
  int oldmvgHTAssignmentFrequency, newmvgHTAssignmentFrequency;
  int oldmvgATAssignmentFrequency, newmvgATAssignmentFrequency;

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (int r = 1; r <= in.NumReferees(); r++)
  {
    for (int g = 1; g <= in.NumGames(); g++)
    {
      const Team &homeTeam = in.GetTeam(in.GetGame(g).HomeTeam());
      const Team &awayTeam = in.GetTeam(in.GetGame(g).AwayTeam());

      if (mvgHomeTeamCode == homeTeam.Code() || mvgHomeTeamCode == awayTeam.Code())
      {
        oldmvgHTTotalAssignedReferees += out.AssignedReferees(g).size();
        if (out.AssignedReferees(g).find(r) != out.AssignedReferees(g).end())
          mvgHTAssignedInputReferee++;
      }

      if (mvgAwayTeamCode == homeTeam.Code() || mvgAwayTeamCode == awayTeam.Code())
      {
        oldmvgATTotalAssignedReferees += out.AssignedReferees(g).size();
        if (out.AssignedReferees(g).find(r) != out.AssignedReferees(g).end())
          mvgATAssignedInputReferee++;
      }
    }

    newmvgHTTotalAssignedReferees = oldmvgHTTotalAssignedReferees + (numNewAssignedReferees - numAssignedReferees);
    newmvgATTotalAssignedReferees = oldmvgATTotalAssignedReferees + (numNewAssignedReferees - numAssignedReferees);
    oldmvgHTAverageAssignedReferee = static_cast<double>(oldmvgHTTotalAssignedReferees) / in.NumReferees();
    newmvgHTAverageAssignedReferee = static_cast<double>(newmvgHTTotalAssignedReferees) / in.NumReferees();
    oldmvgATAverageAssignedReferee = static_cast<double>(oldmvgATTotalAssignedReferees) / in.NumReferees();
    newmvgATAverageAssignedReferee = static_cast<double>(newmvgATTotalAssignedReferees) / in.NumReferees();

    if (mvgHTAssignedInputReferee > oldmvgHTAverageAssignedReferee)
      oldmvgHTAssignmentFrequency = static_cast<int>(ceil(mvgHTAssignedInputReferee - oldmvgHTAverageAssignedReferee));
    else
      oldmvgHTAssignmentFrequency = 0;

    if (mvgATAssignedInputReferee > oldmvgATAverageAssignedReferee)
      oldmvgATAssignmentFrequency = static_cast<int>(ceil(mvgATAssignedInputReferee - oldmvgATAverageAssignedReferee));
    else
      oldmvgATAssignmentFrequency = 0;

    if (oldDiffReferees.find(r) != oldDiffReferees.end() &&
        newDiffReferees.find(r) == newDiffReferees.end())
    {
      if (mvgHTAssignedInputReferee - 1 > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil((mvgHTAssignedInputReferee - 1) - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee - 1 > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil((mvgATAssignedInputReferee - 1) - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }
    else if (newDiffReferees.find(r) != newDiffReferees.end() &&
             oldDiffReferees.find(r) == oldDiffReferees.end())
    {
      if (mvgHTAssignedInputReferee + 1 > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil((mvgHTAssignedInputReferee + 1) - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee + 1 > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil((mvgATAssignedInputReferee + 1) - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }
    else
    {
      if (mvgHTAssignedInputReferee > newmvgHTAverageAssignedReferee)
        newmvgHTAssignmentFrequency = static_cast<int>(ceil(mvgHTAssignedInputReferee - newmvgHTAverageAssignedReferee));
      else
        newmvgHTAssignmentFrequency = 0;

      if (mvgATAssignedInputReferee > newmvgATAverageAssignedReferee)
        newmvgATAssignmentFrequency = static_cast<int>(ceil(mvgATAssignedInputReferee - newmvgATAverageAssignedReferee));
      else
        newmvgATAssignmentFrequency = 0;
    }

    cost += newmvgHTAssignmentFrequency - oldmvgHTAssignmentFrequency;
    cost += newmvgATAssignmentFrequency - oldmvgATAssignmentFrequency;

    oldmvgHTTotalAssignedReferees = 0;
    oldmvgATTotalAssignedReferees = 0;
    mvgHTAssignedInputReferee = 0;
    mvgATAssignedInputReferee = 0;
  }

  return cost;
}

int RefereeIncompatibilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator itI, itJ, itF;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (itI = oldDiffReferees.begin(); itI != oldDiffReferees.end(); ++itI)
  {
    for (itJ = obeg; itJ != oend; ++itJ)
    {
      const Referee &refereeI = in.GetReferee(*itI);
      const Referee &refereeJ = in.GetReferee(*itJ);
        
      if (refereeI.IncompatibleReferee(refereeJ.Code()))
        cost--;

      itF = oldDiffReferees.find(refereeJ.Code());

      if (itF == oldDiffReferees.end() && refereeJ.IncompatibleReferee(refereeI.Code()))
        cost--;
    }
  }

  for (itI = newDiffReferees.begin(); itI != newDiffReferees.end(); ++itI)
  {
    for (itJ = nbeg; itJ != nend; ++itJ)
    {
      const Referee &refereeI = in.GetReferee(*itI);
      const Referee &refereeJ = in.GetReferee(*itJ);
        
      if (refereeI.IncompatibleReferee(refereeJ.Code()))
        cost++;

      itF = newDiffReferees.find(refereeJ.Code());

      if (itF == newDiffReferees.end() && refereeJ.IncompatibleReferee(refereeI.Code()))
        cost++;
    }
  }

  return cost;
}

int TeamIncompatibilityDeltaCost(const RA_Input& in, const RA_Output& out, int game, const set<int>& oldAssignedReferees, const set<int>& newAssignedReferees)
{
  int cost = 0;
  set<int> oldDiffReferees, newDiffReferees;
  set<int>::iterator it;
  set<int>::iterator obeg = oldAssignedReferees.begin();
  set<int>::iterator oend = oldAssignedReferees.end();
  set<int>::iterator nbeg = newAssignedReferees.begin();
  set<int>::iterator nend = newAssignedReferees.end();
  const Team &homeTeam = in.GetTeam(in.GetGame(game).HomeTeam());
  const Team &awayTeam = in.GetTeam(in.GetGame(game).AwayTeam());

  set_difference(obeg, oend, nbeg, nend, inserter(oldDiffReferees, oldDiffReferees.end()));
  set_difference(nbeg, nend, obeg, oend, inserter(newDiffReferees, newDiffReferees.end()));

  for (it = oldDiffReferees.begin(); it != oldDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);

    if (referee.IncompatibleTeam(homeTeam.Code()))
      cost--;

    if (referee.IncompatibleTeam(awayTeam.Code()))
      cost--;
  }

  for (it = newDiffReferees.begin(); it != newDiffReferees.end(); ++it)
  {
    const Referee &referee = in.GetReferee(*it);

    if (referee.IncompatibleTeam(homeTeam.Code()))
      cost++;

    if (referee.IncompatibleTeam(awayTeam.Code()))
      cost++;
  }

  return cost;
}
