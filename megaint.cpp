#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "megaint.h"
#include <cstdio>
using namespace std;

void megaint::normalize()
{
	vector<bool> * tmp =  new vector<bool>;
	for(unsigned int i=0; i<digits->size(); ++i)
	{
		//first time we find a 1
		if(digits->at(i))
		{
			//copy all
			for(unsigned int j=i; j<digits->size(); ++j)
			{
				tmp->push_back(digits->at(j));
			}
			break;
		}
	} 
	
	if(tmp->size() == 0)
	{
		tmp->push_back(0);
	}
	
	delete digits;
	digits = tmp;
}

megaint::megaint()
{
	digits = new vector<bool>;
	digits->push_back(0);
	positive = true;
}

megaint::megaint(const megaint & original)
{
	if (DEBUG) cout << "called copy constructor." << endl;
	digits = new vector<bool>;
	
	positive = original.positive;

	for(unsigned int i=0; i<original.digits->size(); ++i)
	{
		digits->push_back(original.digits->at(i));
	}
}

megaint::megaint(const long l) {
	if (DEBUG) cout << "constructing megaint from long (" << l << ")" << endl;
	digits = new vector<bool>;

	positive = l >= 0;

	if(l == 0)
	{
		digits->push_back(0);
		return;
	}

	if(!positive)
		if (DEBUG) cout << "-" << endl;
	
	long ul = abs(l);
	unsigned long bit = 1 << 31;//2147483648; //2^31
	//at most 32 bits due to being signed long (on 64 bit machines)
	for(int i=0; i<32; ++i)
	{
		if(DEBUG) printf("%ld & %ld  = %ld\n", ul, bit, ul & bit);
		if(ul & bit)
		{
			//
			digits->push_back(1);
		}
		else
		{
			digits->push_back(0);
		}
		bit = bit >> 1;
	}

	normalize();

	if(DEBUG) cout << "\t" << *this << endl;
}

/*
megaint::megaint(const vector<uint8_t> & digs, bool positive)
	: positive(positive) {
	digits = new vector<uint8_t>;
	for (vector<uint8_t>::const_iterator it = digs.begin(); it != digs.end(); ++it) {
		digits->push_back(*it);
	}
}
*/

megaint::megaint(const string & num) {
	digits = new vector<bool>;
	for (int i = num.size(); i >= 0; --i) 
	{
		if(num.at(i) == '1')
		{
			digits->push_back(1);
		}
		else if(num.at(i) == '0')
		{
			digits->push_back(0);
		}
		else
			continue;
	}
}

megaint & megaint::operator=(const megaint & rhs) {
	// TODO I'm sure a more motivated person could remove a bunch of duplicate code here.
	digits = new vector<bool>;
	for (vector<bool>::const_iterator it = rhs.digits->begin();
			it != rhs.digits->end();
			++it) {
		digits->push_back(*it);
	}
	positive = rhs.positive;
	return *this;
}

megaint::~megaint() {
	delete digits;
}

megaint megaint::operator+=(const megaint & rhs) {
	megaint result;
	result = *this + rhs;
	if(DEBUG) cout << *this << " += " << rhs << " = " << result << endl;
	*this = result;
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

megaint megaint::operator+(const megaint & rhs) const {
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

	stack<bool> digiStack;
	bool sum, carry, left, right;
	
	//we need to go from lowest to highest
	carry = 0;
	sum = 0;
	vector<bool>::reverse_iterator ilhs = digits->rbegin();
	vector<bool>::reverse_iterator irhs = rhs.digits->rbegin();

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
		sum = left ^ right ^ carry;
		carry = (left & right) | (left & carry) | (right & carry);
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
			if(carry)
				digiStack.push(1);
			break;
		}
	}
	
	//now our result should be stored in that stack

	megaint result;
	delete result.digits;
	result.digits = new vector<bool>;
	while(!digiStack.empty())
	{
		result.digits->push_back(digiStack.top());
		digiStack.pop();
	}
	if (DEBUG) cout << result << endl;
	return result;
}

megaint megaint::operator-(const megaint & rhs) const {
	megaint result = *this;
	result -= rhs;
	return result;
}

megaint megaint::operator*(const megaint & rhs) const {
	megaint accum(0);
/*	stack<bool> result_digits;
	stack<vector<bool>> result_digits_rows;

	vector<bool>::reverse_iterator i = this->digits->rbegin();
	vector<bool>::reverse_iterator j = rhs.digits->rbegin();
	for (; j != rhs.digits->rend(); ++j) {
		// TODO make this loop through both numbers (right now breaking after first digit)
		int carry = 0;
		int power = 1;
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
		vector<bool> result_digits_vec;
		while (result_digits.size() != 0) {
			result_digits_vec.push_back(result_digits.top());
			result_digits.pop();
		}
		result_digits_rows.push(result_digits_vec);
		break; // FIXME see TODO above
	}
	while (result_digits_rows.size() != 0) {
		vector<bool> digs = result_digits_rows.top();
		result_digits_rows.pop();
		megaint new_row(digs, true);
		accum = accum + new_row;
	}
*/
	return accum;

}

megaint megaint::operator/(const megaint & rhs) const {
	megaint result = *this;
	result /= rhs;
	return result;
}

bool megaint::operator==(const megaint & other) const {
	if(DEBUG) cout << *this << " == " << other << endl;
	vector<bool>::const_iterator thisit = this->digits->begin();
	vector<bool>::const_iterator otherit = other.digits->begin();
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

//complement: invert all bits and add 1
//depends on addition
megaint megaint::operator~() const {
	megaint result;

	for(unsigned int i=0; i<digits->size(); ++i)
	{
		result.digits->push_back(!digits->at(i));
	}

	result.normalize();

	megaint one(1);
	result += 1;

	return result;
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
