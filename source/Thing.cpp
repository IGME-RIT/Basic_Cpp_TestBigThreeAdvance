#include "Thing.h"

// define constructor
Thing::Thing(int n) : size(n) { 
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "Basic Constructing..." << (*this) << " via " << __FUNCTION__ << endl;
	data = new int[n];
	fill();
}

// define copy constructor
Thing::Thing(Thing const& other) {
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "Copy Constructing...." << (*this) << " via " << __FUNCTION__ << endl;
	size = other.size;
	// cout << "Testing data in copy constr: " << data[0] << endl; // won't work because data not set yet in current object!
	data = new int[other.size];      // why do we need this?
	for (int i=0;i<size;i++)
		data[i]=other.data[i];
}

// define copy assignment
Thing& Thing::operator=(Thing const& other) {
	cout << "Copying.............." << (*this) << " via " << __FUNCTION__ << endl;

	if (this != &other) {            // ensure we're not wasting time with self-assignment
		size = other.size;           
		data = new int[other.size];  // if use original data, we'd "link" the two objects and their arrays
		for (int i=0;i<size;i++)     // deep copy:
			data[i]=other.data[i];   // need to copy each array element
	}
	return *this;                    // allow for external calls, like a=b=c=...
} 

// define destructor
Thing::~Thing() {
	cout << "Destroying..........." << (*this) << " via " << __FUNCTION__ << endl;
	if (*data) {
		delete[] data;  // need to manage internally allocated memory
	}
	else
		data = nullptr;
}

// define overloaded operator
int& Thing::operator[](int i) {
	return data[i];
}

//define member function for output
void Thing::print() const {
	cout << "[";
	for (int i = 0; i < size; i++) {
		cout << data[i];
		if (i + 1 < size) cout << ',';
	}
	cout << "]" << endl;  // print out all datas in the object
}

// define member function for assignment
void Thing::fill() const {
	for (int i = 0; i < size; i++) {
		data[i] = i;
	}
}

// define member functions for passing objects
void Thing::test1(Thing other) const {
	Thing(1);
}

void Thing::test2(Thing& other) const {
	Thing(2);
}

Thing Thing::test3(Thing& other) const {
	return Thing(3);
}

Thing& Thing::test4(Thing& other) const {
	return Thing(4); // warning C4172: returning address of local variable or temporary
}

Thing& Thing::test5(Thing const& other) const {
	return Thing(5); // warning C4172: returning address of local variable or temporary
}

const Thing& Thing::test6(Thing const& other) const {
	return Thing(6); // warning C4172: returning address of local variable or temporary
}

Thing& Thing::test7(Thing& other) const {
	return other;
}

const Thing& Thing::test8(Thing const& other) const {
	return other;
}

Thing* Thing::test9() const {
	return new Thing(100);
}

// operator overloading
ostream& operator<<(ostream& out, const Thing& t) {
	return out << typeid(t).name() << " " << t.label;  // typeid: see https://msdn.microsoft.com/en-us/library/fyf39xec.aspx
}

int Thing::count = 0;


