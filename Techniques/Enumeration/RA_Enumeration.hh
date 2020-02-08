// File RA_Enumeration.hh

#include "EnumerationOpt.hh"
#include <RA_Data.hh>
#include <set>

class EnumerationRAOpt : public EnumerationOpt<RA_Input, RA_Output, int> {

public:
	EnumerationRAOpt(const RA_Input& in) : EnumerationOpt(in) {}

protected:
	void First();
	bool Next();
	bool Feasible();
	int Cost();

private:
	bool HasNext(int g);

};
