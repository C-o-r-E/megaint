#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "megaint.h"
#include <cstdio>
using namespace std;

megaint::megaint()
{
	digits = new vector<uint8_t>;
	digits->push_back(0);
	positive = true;
}

megaint::megaint(const megaint & original)
{
	if (DEBUG) cout << "called copy constructor." << endl;
	digits = new vector<uint8_t>;
	
	positive = original.positive;

	for(unsigned int i=0; i<original.digits->size(); ++i)
	{
		digits->push_back(original.digits->at(i));
	}
}

megaint::megaint(const long l) {
	if (DEBUG) cout << "constructing megaint from long (" << l << ")" << endl;
	digits = new vector<uint8_t>;

	positive = l >= 0;

	if(l == 0)
	{
		digits->push_back(0);
		return;
	}

	if(!positive)
		if (DEBUG) cout << "-" << endl;
	
	long ul = abs(l);

	//for each power of 10
	for(int i=9; i>=0; --i) // log(2^32) == 9 
	{
		unsigned long power = (unsigned long)pow(10, i);
		//get digit
		uint8_t d = ul/power;
		if (DEBUG) cout << (int)d << endl;
		if(d > 0)
			digits->push_back(d);
		else
			digits->push_back(0);

		ul -= power * d;
	}
	if (DEBUG) cout << endl;

	
}

megaint::megaint(const vector<uint8_t> & digs, bool positive)
	: positive(positive) {
	digits = new vector<uint8_t>;
	for (vector<uint8_t>::const_iterator it = digs.begin(); it != digs.end(); ++it) {
		digits->push_back(*it);
	}
}

megaint::megaint(const string & num) {
	digits = new vector<uint8_t>;
	for (int i = 0; i != num.size(); ++i) {
		digits->push_back(num.at(i) - 0x30);
	}
}

megaint & megaint::operator=(const megaint & rhs) {
	// TODO I'm sure a more motivated person could remove a bunch of duplicate code here.
	digits = new vector<uint8_t>;
	for (vector<uint8_t>::const_iterator it = rhs.digits->begin();
			it != rhs.digits->end();
			++it) {
		digits->push_back(*it);
	}
	positive = rhs.positive;
}

megaint::~megaint() {
	delete digits;
}

megaint megaint::operator+=(const megaint & rhs) {
	megaint result;
	return result;
}

megaint megaint::operator-=(const megaint & rhs) {
	megaint result;
	return result;
}

megaint megaint::operator*=(const megaint & rhs) {
	megaint result;
	return *this;
}

megaint megaint::operator/=(const megaint & rhs) {
	megaint result;
	return result;
}

const megaint megaint::operator+(const megaint & rhs) const {
	if (DEBUG) cout << *this << " + " << rhs << " = ";

	/*insight:
	  if we have a pos + pos : do the algorithm
	  if we have a pos + neg  or neg + pos : call operator-(neg)
	  if we have a neg + neg : add them and set positve = false;
	*/
	if(!positive)
	{
		//call operator-() ?
	}

	stack<uint8_t> digiStack;
	uint8_t sum, carry, left, right;
	
	//we need to go from lowest to highest
	carry = 0;
	sum = 0;
	vector<uint8_t>::reverse_iterator ilhs = digits->rbegin();
	vector<uint8_t>::reverse_iterator irhs = rhs.digits->rbegin();

	if(ilhs == digits->rend())
	{
		left = 0;
	}
	else
	{
		left = *ilhs;
	}

	if(ilhs == rhs.digits->rend())
	{
		right = 0;
	}
	else
	{
		right = *irhs;
	}

	for(;;)
	{
		sum = 0;
		//first do the calc
		if(carry > 0)
		{
			++sum;
			carry = 0;
		}
		sum = left + right;
		if(sum > 10)
		{
			sum = sum -10;
			carry = 1;
		}

		digiStack.push(sum);
		//now try to increment the iterators
		///////////////////////////LHS
		if(ilhs == digits->rend())
		{	
			left = 0;
		}
		else 
		{
			++ilhs;
			if(ilhs == digits->rend())//need to make the logic less retarded
			{
				left = 0;
			}
			else
			{
				left = *ilhs;
			}
		}

		///////////////////////////RHS
		if(irhs == rhs.digits->rend())
		{	
			right = 0;
		}
		else 
		{
			++irhs;
			if(irhs == rhs.digits->rend())//need to make the logic less retarded
			{
				right = 0;
			}
			else
			{
				right = *irhs;
			}
		}


		//exit condition
		if(ilhs == digits->rend() && irhs == rhs.digits->rend())
		{
			if(carry > 0)
				digiStack.push(1);
			break;
		}
	}
	
	//now our result should be stored in that stack

	megaint result;
	delete result.digits;
	result.digits = new vector<uint8_t>;
	while(!digiStack.empty())
	{
		uint8_t t = digiStack.top();
		result.digits->push_back(t);
		digiStack.pop();
	}
	//cout << "Result" << result << endl;
	if (DEBUG) cout << result << endl;
	return result;
}

const megaint megaint::operator-(const megaint & rhs) const {
	megaint result = *this;
	result -= rhs;
	return result;
}

const megaint megaint::operator*(const megaint & rhs) const {
	stack<uint8_t> result_digits;
	stack<vector<uint8_t> > result_digits_rows;
	// Imagine these two iterators as going from smallest to lowest digit
	// in each 'row', as you do by hand:
	//     0000034    <- i
	//     x   043    <- j
	//     --------
	vector<uint8_t>::reverse_iterator i = this->digits->rbegin();
	vector<uint8_t>::reverse_iterator j = rhs.digits->rbegin();

	// Cycle through the "bottom" digits
	for (; j != rhs.digits->rend(); ++j) {
		// TODO make this loop through both numbers (right now breaking after first digit)
		int carry = 0;
		int power = 1; // TODO this should increase by a power of ten for each j

		// Now cycle through the "top" digits
		for (; i != this->digits->rend(); ++i) {
			int result = carry + (*i) * (*j);
			int thisdigit = result % 10;
			if (result >= 10) {
				carry = result / 10;
			}
			else {
				carry = 0;
			}
			result_digits.push(thisdigit);
		}
		if (carry) {
			result_digits.push(carry);
		}
		vector<uint8_t> result_digits_vec;
		while (result_digits.size() != 0) {
			result_digits_vec.push_back(result_digits.top());
			result_digits.pop();
		}
		result_digits_rows.push(result_digits_vec);
		break; // FIXME see TODO above
	}
	megaint accum(0);
	// Sum the resulting rows
	while (result_digits_rows.size() != 0) {
		vector<uint8_t> digs = result_digits_rows.top();
		result_digits_rows.pop();
		megaint new_row(digs, true);

		accum = accum + new_row;
	}
	return accum;
}

const megaint megaint::operator/(const megaint & rhs) const {
	megaint result = *this;
	result /= rhs;
	return result;
}


bool megaint::operator==(const megaint & other) const {
	vector<uint8_t>::const_iterator thisit = this->digits->begin();
	vector<uint8_t>::const_iterator otherit = other.digits->begin();
	if ((positive == other.positive)) {
		while (thisit != this->digits->end() && *thisit == 0) {
			++thisit;
		}
		while (otherit != other.digits->end() && *otherit == 0) {
			++otherit;
		}
		while (thisit != this->digits->end() && otherit != other.digits->end()) {
			if (*thisit != *otherit) {
				return false;
			}
			++otherit;
			++thisit;
		}
		return (thisit == this->digits->end()) && (otherit == other.digits->end());

	}
	else {
		return false;
	}
}

bool megaint::operator!=(const megaint & other) const {
	//check sign
	if(positive != other.positive)
		return true;
	
	//check sizes
	if(digits->size() != other.digits->size())
		return true;

	//otherwise digit by digit comparison
	for(unsigned int i=0; i<digits->size(); ++i)
	{
		if(digits->at(i) != other.digits->at(i))
			return true;
	}
	//finally they must be equal
	return false;

}

megaint::operator bool() const {
	if(digits->size() == 1 && digits->at(0) == 0)
		return false;

	return true;
}

ostream & operator<<(ostream & os, const megaint & mi) {
	if(!mi.positive)
		os << '-';

	for(unsigned int i=0; i<mi.digits->size(); ++i)
	{
		
		os << (unsigned int)mi.digits->at(i);
	}
	
	return os;
}
