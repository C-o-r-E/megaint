#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
#include "megaint.h"
using namespace std;

megaint::megaint(const megaint & original)
{
	cout << "called copy constructor." << endl;
	digits = new vector<uint8_t>;
	
	positive = original.positive;

	for(int i=0; i<original.digits->size(); ++i)
	{
		digits->push_back(original.digits->at(i));
	}
}

megaint::megaint(const long l) {
	digits = new vector<uint8_t>;
	
	positive = l >= 0;
	
	long ul = abs(l);

	cout << "constructing megaint from long (" << l << ")" << endl;
	//for each power of 10
	for(int i=9; i>=0; --i) // log(2^32) == 9 
	{
		unsigned long power = (unsigned long)pow(10, i);
		//get digit
		uint8_t d = ul/power;
		cout << (int)d << endl;
		if(d > 0)
			digits->push_back(d);

		ul -= power * d;
	}
	cout << endl;

	
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
	//val /= rhs.val;
	//return this;
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
	//check sizes
	if(digits->size() != other.digits->size())
		return true;

	//otherwise digit by digit comparison
	for(int i=0; i<digits->size(); ++i)
	{
		if(digits->at(i) != other.digits->at(i))
			return true;
	}
	//finally they must be equal
	return false;

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
