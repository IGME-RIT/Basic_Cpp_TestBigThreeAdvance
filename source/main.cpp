/*
TestBig3
(c) 2016
original authors: David I. Schwartz
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial illustrates the concept of special member functions
	(constructor, destructor and copy assignment) and different return types of functions.
*	It covers issues such as typeid operator, keyword const and temporary assignment.
*/

// Same example as BIG THREE, except we're now passing objects to functions and returning 
// objects from functions to demo which special member functions get called and when

// http://stackoverflow.com/questions/21778045/c-return-value-reference-const-reference
// http://stackoverflow.com/questions/773599/return-class-pointer-from-a-function
// http://www.bogotobogo.com/cplusplus/object_returning.php

#include "Thing.h"

int main() {

	
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test1: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t1(1);  // output: Basic Constructing...class Thing a via Thing::Thing
	Thing t2(2);  // output: Basic Constructing...class Thing b via Thing::Thing
	t1.test1(t2); // output: Copy Constructing....class Thing c via Thing::Thing
	              // output: Basic Constructing...class Thing d via Thing::Thing
	              // output: Destroying...........class Thing d via Thing::~Thing
				  // output: Destroying...........class Thing c via Thing::~Thing

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test2: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t3(1);  // output: Basic Constructing...class Thing e via Thing::Thing
	Thing t4(2);  // output: Basic Constructing...class Thing f via Thing::Thing
	t4.test2(t3); // output: Basic Constructing...class Thing g via Thing::Thing
	              // output: Destroying...........class Thing g via Thing::~Thing

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test3: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t5(2);  // output: Basic Constructing...class Thing h via Thing::Thing
	Thing t6(2);  // output: Basic Constructing...class Thing i via Thing::Thing
	Thing t7 = t5.test3(t6); // copy-cstr called because using conversion constructor syntax (Thing t7 = ...) | output: Basic Constructing...class Thing j via Thing::Thing
	t7.print();   // output: [0,1,2]
	t5.test3(t6); // output: Basic Constructing...class Thing k via Thing::Thing
	              // output: Destroying...........class Thing k via Thing::~Thing
	t5 = t6;      // output: Copying..............class Thing h via Thing::operator =

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test4: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t8(1);  // output: Basic Constructing...class Thing l via Thing::Thing
	Thing t9(2);  // output: Basic Constructing...class Thing m via Thing::Thing
		
	//Thing t10 = t8.test4(t9); // trying to access temp var from test4 (cause an exception to throw)
	//t10.print();

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test5: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t11(1);  // output: Basic Constructing...class Thing n via Thing::Thing
	Thing t12(2);  // output: Basic Constructing...class Thing o via Thing::Thing
	//Thing t13 = t11.test5(t12);
	//t13.print(); // trying to access temp var from test4 | does not work! read access violation

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test6: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t14(1);  // output: Basic Constructing...class Thing p via Thing::Thing
	Thing t15(2);  // output: Basic Constructing...class Thing q via Thing::Thing
	//Thing t16 = t14.test6(t15);
	//t16.print(); // trying to access temp var from test4 | does not work! cause an exception to throw 

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test7: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t17(5);  // output: Basic Constructing...class Thing r via Thing::Thing
	Thing t18(2);  // output: Basic Constructing...class Thing s via Thing::Thing
	Thing t19 = t18.test7(t17);  // output: Copy Constructing....class Thing t via Thing::Thing
	cout << t17 << endl;  // output: class Thing r
	cout << t19 << endl;  // output: class Thing t
	t17.print();    // output: [0,1,2,3,4]
	t19.print();    // output: [0,1,2,3,4]
	t18.test7(t17); // see test3 for difference -- no copy constructor called

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test8: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t20(3);   // output: Basic Constructing...class Thing u via Thing::Thing
	Thing t21(3);   // output: Basic Constructing...class Thing v via Thing::Thing
	Thing t22 = t21.test8(t20);  // output: Copy Constructing....class Thing w via Thing::Thing
	cout << t20 << endl;  // output: class Thing u
	cout << t22 << endl;  // output: class Thing w
	t20.print();    // output: [0,1,2]
	t22.print();    // output: [0,1,2]
	t21.test8(t17); // see test3 for difference -- no copy constructor called
	t21 = t20;      // output: Copying..............class Thing v via Thing::operator =

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "Test9: " << endl;
	cout << "---------------------------------------------------------------" << endl;

	Thing t23(4);  // output: Basic Constructing...class Thing x via Thing::Thing
	Thing t24(4);  // output: Basic Constructing...class Thing y via Thing::Thing
	Thing* t25 = t23.test9();  // output: Basic Constructing...class Thing z via Thing::Thing
	*t25 = t23;    // output: Copying..............class Thing z via Thing::operator =
	delete t25;    // output: Destroying...........class Thing z via Thing::~Thing
	delete t24.test9();  // output: Basic Constructing...class Thing { via Thing::Thing
	                     //         Destroying...........class Thing { via Thing::Thing

	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\nIt's more clobbering time!" << endl;
	cout << "---------------------------------------------------------------" << endl;
	/*
	Destroying...........class Thing y via Thing::~Thing
	Destroying...........class Thing x via Thing::~Thing
	Destroying...........class Thing w via Thing::~Thing
	Destroying...........class Thing v via Thing::~Thing
	Destroying...........class Thing u via Thing::~Thing
	Destroying...........class Thing t via Thing::~Thing
	Destroying...........class Thing s via Thing::~Thing
	Destroying...........class Thing r via Thing::~Thing
	Destroying...........class Thing q via Thing::~Thing
	Destroying...........class Thing p via Thing::~Thing
	Destroying...........class Thing o via Thing::~Thing
	Destroying...........class Thing n via Thing::~Thing
	Destroying...........class Thing m via Thing::~Thing
	Destroying...........class Thing l via Thing::~Thing
	Destroying...........class Thing j via Thing::~Thing
	Destroying...........class Thing i via Thing::~Thing
	Destroying...........class Thing h via Thing::~Thing
	Destroying...........class Thing f via Thing::~Thing
	Destroying...........class Thing e via Thing::~Thing
	Destroying...........class Thing b via Thing::~Thing
	Destroying...........class Thing a via Thing::~Thing
	*/

}

