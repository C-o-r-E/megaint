#include <iostream>
#include <cassert>
#include "megaint.h"
using namespace std;

void test_addition();
void test_subtraction();
void test_mult();
void test_exp();
void test_x_equals_ops();
void test_streams();

int main() {
	test_x_equals_ops();
	test_addition();
	test_subtraction();
	test_mult();
	test_exp();

	test_streams();

	return 0;
}

// *=, -=, +=, /=
void test_x_equals_ops() {
	cout << "test_x_equals_ops()" << endl;
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

	a -= c;
	assert(a != b);
	assert(a == (b - c));

	megaint k(2);
	megaint j(-3);
	megaint n(-6);
	assert(k*j == n);
	k *= j;
	assert(k == n);
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
	cout << "test_mult()" << endl;
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

void test_exp()
{
	cout << "test_exp()" << endl;
	megaint a(1);
	megaint b(2);
	megaint c(4);

	assert(a ^ b == a);
	assert(b ^ a == b);
	assert(b ^ b == c);

	megaint big(313);

	cout << (big ^ big) << endl;
}

void test_streams() {
	cout << "Sorry to ruin your snappy test run!" << endl;
	cout << "Please enter a number: ";
	megaint a;
	cin >> a;
	cout << "Is this your number?" << endl;
	cout << a << endl;
}

