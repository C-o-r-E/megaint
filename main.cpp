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
void test_lt();

int main() {
	test_lt();
	test_x_equals_ops();
	test_addition();
	test_subtraction();
	test_mult();
	test_exp();

	test_streams();

	return 0;
}

void test_lt() {
	megaint a(101);
	megaint b(102);
	assert(a < b);
	assert(a <= a);
	assert(a <= b);
	assert(!(a < a));
	assert(!(a > a));
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

	megaint four(4);
	megaint five(5);
	megaint twenty(20);

	megaint h(32);
	megaint I(1024);

	assert(a*b == b);
	assert(b*c == d);
	assert(b*e != d);
	assert(b*e == g);
	assert(four*five == twenty);
	assert(h*h == I);
}

void test_exp()
{
	cout << "test_exp()" << endl;
	megaint a(1);
	megaint b(2);
	megaint c(4);

	assert((a ^ b) == a);
	assert((b ^ a) == b);
	assert((b ^ b) == c);

	megaint t(8);
	megaint u(256);
	assert((b ^ t) == u);


	megaint derp(313);
	megaint herp(312);
	megaint mcgerp;
	mcgerp = (derp ^ derp);

	assert((derp ^ herp) * derp == mcgerp);

}

void test_streams() {
	megaint _a(1);
	megaint _b(5);
	megaint _c(10);
	cout << _a << endl;
	cout << _b << endl;
	cout << _c << endl;
	cout << "Sorry to ruin your snappy test run!" << endl;
	cout << "Please enter a number: ";
	megaint a;
	cin >> a;
	cout << "Is this your number?" << endl;
	cout << a << endl;
}

