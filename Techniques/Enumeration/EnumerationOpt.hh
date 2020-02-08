#ifndef ENUMERATION_OPT_HPP
#define ENUMERATION_OPT_HPP
#include <iostream>

using namespace std;

template <typename Input, typename Output, typename CFtype>
class EnumerationOpt
{
public:
  EnumerationOpt(const Input& in);
  bool Search();
  Output BestSolution() { return best; }
  long long unsigned NumSol() const { return count; }
protected:  
  virtual void First() = 0;
  virtual bool Next() = 0;
  virtual bool Feasible() = 0;
  virtual CFtype Cost() = 0;
  long long unsigned count;
  const Input& in;
  Output out, best;
};

template <typename Input, typename Output, typename CFtype>
EnumerationOpt<Input,Output,CFtype>::EnumerationOpt(const Input& i) 
  : in(i), out(i), best(i) 
{
  count = 0;
}

template <typename Input, typename Output, typename CFtype>
bool EnumerationOpt<Input,Output,CFtype>::Search()
{
  CFtype cost, best_cost = 0;
  bool first_sol_found = false;

  First();
  count = 1;
  do 
    {
      if (Feasible())
        {
          cost = Cost();
          if (!first_sol_found || cost < best_cost)
            {
              first_sol_found = true;
              best = out;              
              best_cost = cost;
              cerr << "New best solution" << endl << best 
                   << " (cost " << best_cost << ") " 
                   << " found after " << count << " iterations" << endl;
            }
        }
      count++;
    }
  while (Next());
  return first_sol_found;      
}
#endif
