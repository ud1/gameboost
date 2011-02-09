#include <stdio.h>
#include <stdlib.h>


#include "base/Factory.h"

class Base {

protected:
	
	int value;

public:
	
	Base() {
		value = 0;
	}

	Base(int value_) {
		value = value_;
	}

	virtual ~Base() { }

};

class Foo : public Base {

public:

	Foo() {
		fprintf(stdout, "Foo::Foo()\n", value);
	}

	Foo(int value_) {
		value = value_;
		fprintf(stdout, "Foo::Foo(): value is %d.\n", value);
	}
	
};

class Bar : public Base {

public:

	Bar() {
		fprintf(stdout, "Bar::Bar()\n", value);
	}
	
	Bar(int value_) {
		value = value_;
		fprintf(stdout, "Bar::Bar(): value is %d.\n", value);
	}
	

};


int main() {

	//--------------------------------------------------------------------------
	// test for 0 args
	//--------------------------------------------------------------------------
	
	fprintf(stdout, "Creating gb::base::Factory for 0 constructor parameters\n");
	gb::base::Factory <Base, void> factory0;

	factory0.addType <Foo> ("Foo");
	factory0.addType <Bar> ("Bar");

	fprintf(stdout, "Create types test:\n");
	for (int i=0; i<factory0.getTypesCount(); i++) {
		Base *base = factory0.create(factory0.getTypeName(i).c_str());
		delete base;
	}

	fprintf(stdout, "Remove Foo:\n");
	factory0.removeType("Foo");
	fprintf(stdout, "Foo is %s.\n", (factory0.check("Foo") == true) ? "present" : "absent");

	//--------------------------------------------------------------------------
	// test for 1 args
	//--------------------------------------------------------------------------
	
	fprintf(stdout, "Creating gb::base::Factory for 1 constructor parameters\n");
	gb::base::Factory <Base, int> factory1;

	factory1.addType <Foo> ("Foo");
	factory1.addType <Bar> ("Bar");

	fprintf(stdout, "Create types test:\n");
	for (int i=0; i<factory1.getTypesCount(); i++) {
		Base *base = factory1.create(factory1.getTypeName(i).c_str(), i + 1);
		delete base;
	}

	fprintf(stdout, "Remove Foo:\n");
	factory1.removeType("Foo");
	fprintf(stdout, "Foo is %s.\n", (factory1.check("Foo") == true) ? "present" : "absent");
	
	system("pause");
	return 0;
}