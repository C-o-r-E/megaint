#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "megaint.h"
using namespace std;

megaint::megaint(const int x) {
	digits = new vector<unsigned int>;
	digits->push_back(abs(x));
	positive = x >= 0;
}

megaint::megaint(const string & num) {
	val = atoi(num.c_str());
}

megaint::~megaint() {
	delete digits;
}

megaint & megaint::operator+=(const megaint & rhs) {
	val += rhs.val;
}

megaint & megaint::operator-=(const megaint & rhs) {
	val -= rhs.val;
}

megaint & megaint::operator*=(const megaint & rhs) {
	val *= rhs.val;
}

megaint & megaint::operator/=(const megaint & rhs) {
	val /= rhs.val;
}

const megaint megaint::operator+(const megaint & rhs) const {
	megaint result = *this;
	result += rhs;
	return result;
}

const megaint megaint::operator-(const megaint & rhs) const {
	megaint result = *this;
	result -= rhs;
	return result;
}

const megaint megaint::operator*(const megaint & rhs) const {
	megaint result = *this;
	result *= rhs;
	return result;
}

const megaint megaint::operator/(const megaint & rhs) const {
	megaint result = *this;
	result /= rhs;
	return result;
}

bool megaint::operator==(const megaint & other) const {
	if ((positive == other.positive) &&
		   (digits->size() == other.digits->size())) {
		for (int i = 0; i < digits->size(); ++i) {
			if (digits->at(i) != other.digits->at(i)) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool megaint::operator!=(const megaint & other) const {
	bool equals = *this == other;
	return !equals;
}

ostream & operator<<(ostream & os, const megaint & mi) {
	os << mi.val;
}
