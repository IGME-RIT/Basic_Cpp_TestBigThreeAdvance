#pragma once
#include "stuff.h"
static const char BASE_LABEL = 'a';

class Thing {
public:

	// Constructor:
	Thing(int size);
	
	// Copy constructor:
	Thing(const Thing& other);

	// Copy assignment overload:
	Thing& operator=(const Thing& other);

	// Destructor:
	~Thing();

	// Handy overload of [] for accessing internal array:
	int& operator[](int i);

	// Output:
	void print() const;
	friend std::ostream& operator<<(std::ostream&, const Thing&);

	// Testing object passing:
	void test1(Thing other) const;
	void test2(Thing& other) const;
	Thing test3(Thing& other) const;
	Thing& test4(Thing& other) const;
	Thing& test5(Thing const& other) const;
	const Thing& test6(Thing const& other) const;
	Thing& test7(Thing& other) const;
	const Thing& test8(Thing const& other) const;
	Thing* Thing::test9() const;

private:
	int size;          // size of array
	int* data;         // array of data
	char label;        // "name" of object
	static int count;  // current object count
	void fill() const; // fill array with values for testing

};


