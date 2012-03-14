#include <iostream>
#include <cassert>
#include "megaint.h"
using namespace std;

void test_addition();
void test_subtraction();
void test_mult();
void test_division();
void test_x_equals_ops();

int main() {
	test_x_equals_ops();
	test_addition();
	test_subtraction();
	test_mult();
	test_division();
	
	return 0;
}

// *=, -=, +=, /=
void test_x_equals_ops() {
	megaint a(34234);
	long bla = 34234 + 343;
	megaint b(bla);
	megaint c(343);

	assert(a + c == b);
	a += c;
	assert(a == b);

	megaint d(0);
	d += 1;
	megaint e(1);
	assert(d == e);
}

void test_addition() {
	cout << "Testing addition" << endl;
	megaint a(1);
	megaint b(1);
	megaint c(2);
	assert(a + b == c);
	assert(a == b);

	megaint z(0);	
	megaint d(65535);
   
	
	assert(d != c);
	assert(d + d == d + d);
	assert(a + z == a);
	assert(c + z == c);
	assert(d + z == d);

	megaint g(3);
	megaint h(5);
	
	g += c;
	assert(g == h);
}

void test_subtraction() {
	cout << "Testing subtraction" << endl;
	megaint a(1);
	megaint b(1);
	megaint c(0);
	assert(a - b == c);
	megaint d(10);
	megaint e(5);
	assert(d - e == e);
	assert(d - c == d);

}

void test_mult() {
	megaint a(1);
	megaint b(2);
	megaint c(3);
	megaint d(6);
	megaint e(-3);
	megaint f(0);
	megaint g(-6);
	assert(a*b == b);
	assert(b*c == d);
	assert(b*e != d);
	assert(b*e == g);
}

void test_division() {
	megaint a(1);
	megaint b(1);
	megaint c;
	megaint e(10);
	megaint f(100);
	//c = c + e;
	//c = c + f; these are broken
	megaint d(110);
	//assert(a == b);
	//assert(c == d);
}
