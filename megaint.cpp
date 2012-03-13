#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "megaint.h"
using namespace std;

megaint::megaint()
{
	digits = new vector<uint8_t>;
	digits->push_back(0);
	positive = true;
}

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
	cout << "constructing megaint from long (" << l << ")" << endl;
	digits = new vector<uint8_t>;

	positive = l >= 0;

	if(l == 0)
	{
		digits->push_back(0);
		return;
	}

	if(!positive)
		cout << "-" << endl;
	
	long ul = abs(l);

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
	megaint result;
	return result;
}

megaint & megaint::operator-=(const megaint & rhs) {
	megaint result;
	return result;
}

megaint & megaint::operator*=(const megaint & rhs) {
	megaint result;
	return result;
}

megaint & megaint::operator/=(const megaint & rhs) {
	megaint result;
	return result;
}

const megaint megaint::operator+(const megaint & rhs) const {
	cout << *this << " + " << rhs << " = ";

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
	int len;
	
	//we need to go from lowest to highest
	if(digits->size() < rhs.digits->size())
	{
		len = rhs.digits->size();
	}
	else
	{
		len = digits->size();
	}


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
		result.digits->push_back(digiStack.top());
		digiStack.pop();
	}
	cout << result << endl;
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
	//check sign
	if(positive != other.positive)
		return true;
	
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

megaint::operator bool() const {
	if(digits->size() == 1 && digits->at(0) == 0)
		return false;

	return true;
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
