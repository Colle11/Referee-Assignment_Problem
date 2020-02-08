#include <ctime>
#include <cstdlib>
#include <random>
#include "Random.hh"
using namespace std;

int Random(int a, int b)
{ 
  static random_device rd;
  static mt19937 gen(rd());
  uniform_int_distribution<int> dis(a,b);
  return dis(gen);
}

