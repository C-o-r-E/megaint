#include <iostream>
#include <cassert>
#include "megaint.h"
using namespace std;

int main() {
	cout << "Testing some stuff." << endl;
	megaint a(1);
	cout << "1 =? " << a << endl;
	megaint b(1);
	assert(a == b);
	megaint c(3);
	assert(a != c);

	assert(a*c == b*c);
	assert(a*c/a == c);

	string num("100");
	megaint n(num);
	assert(n == 100);

	string num1("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	string num2("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	megaint n1(num1);
	megaint n2(num2);
	cout << n1 << endl;
	cout << n2 << endl;
	assert(n1 == n2 && n1 != -1);
	return 0;
}
