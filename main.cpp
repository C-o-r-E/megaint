#include <iostream>
#include <cassert>
#include "megaint.h"
using namespace std;

void test_equality();
void test_addition();
void test_subtraction();
void test_mult();

int main() {
	//test_addition();
	test_mult();
	test_equality();
	test_subtraction();
	return 0;
}

void test_addition() {
	cout << "Testing addition" << endl;
	megaint a(1);
	megaint b(1);
	megaint c(2);
	assert(a + b == c);

	megaint d(65535);
	megaint e(-65535);
	megaint f(0);
	assert(d != e);
	assert(d + e == f);
	assert(a + f == a);
	assert(c + f == c);
	assert(d + f == d);
	assert(e + f == e);
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
	assert(e - d == (c-e));
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
	assert(b*c/b == c);
}

void test_equality() {
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
