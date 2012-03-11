#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
#include "megaint.h"
using namespace std;

megaint::megaint(const long l) {
	digits = new vector<uint8_t>;
	

	positive = l >= 0;

	unsigned long ul = abs(l);

	//for each power of 10
	for(int i=9; i>=0; --i) // log(2^32) == 9 
	{
		unsigned long power = (unsigned long)pow(10, i);
		//get digit
		uint8_t d = ul/power;
		cout << (int)d << endl;
		
		ul -= power * d;
	}
	cout << endl;
//	digits->push_back(abs(x));
	
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
	if(!mi.positive)
		os << '-';

	for(int i=0; i<mi.digits->size(); ++i)
	{
		
		os << (unsigned int)mi.digits->at(i);
	}
	
	return os;
}
