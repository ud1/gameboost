#include <gb/base/Variable.h>
#include <cassert>
#include <functional>
#include <algorithm>

using namespace gb::base::variable;

int main()
{
	int val = 5;
	
	IdentityWithChangeChecking<int> identity_updater(val);
	Variable<int> variable("var", identity_updater);
	
	assert(variable.getValue() == 5);
	assert(variable.getUpdateNumber() == 0);
	assert(variable.getValue() == 5);
	assert(variable.getUpdateNumber() == 0);
	
	val = 6;
	assert(variable.getValue() == 6);
	assert(variable.getUpdateNumber() == 1);
	assert(variable.getValue() == 6);
	assert(variable.getUpdateNumber() == 1);
	
	Function<std::negate<int> > negate_variable_updater(std::negate<int>(), variable);
	Variable<int> neg_variable("minus_var", negate_variable_updater);
	
	assert(neg_variable.getValue() == -6);
	assert(neg_variable.getUpdateNumber() == 0);
	assert(neg_variable.getValue() == -6);
	assert(neg_variable.getUpdateNumber() == 0);
	
	val = 7;
	assert(neg_variable.getValue() == -7);
	assert(neg_variable.getUpdateNumber() == 1);
	assert(neg_variable.getValue() == -7);
	assert(neg_variable.getUpdateNumber() == 1);
	
	Function<std::binder1st<std::plus<int> > > ten_minus_variable_updater(std::bind1st(std::plus<int>(), 10), neg_variable);
	Variable<int> ten_minus_variable("ten_minus_var", ten_minus_variable_updater);
	
	assert(ten_minus_variable.getValue() == 3);
	assert(ten_minus_variable.getUpdateNumber() == 0);
	assert(ten_minus_variable.getValue() == 3);
	assert(ten_minus_variable.getUpdateNumber() == 0);
	
	val = 8;
	assert(ten_minus_variable.getValue() == 2);
	assert(ten_minus_variable.getUpdateNumber() == 1);
	assert(ten_minus_variable.getValue() == 2);
	assert(ten_minus_variable.getUpdateNumber() == 1);
}