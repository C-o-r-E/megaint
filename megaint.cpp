#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "megaint.h"
#include <cstdio>
using namespace std;

//this function removes leading 0s
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
//	if (DEBUG) cout << "constructing megaint from long (" << l << ")" << endl;
	digits = new vector<bool>;

	positive = l >= 0;

	if(l == 0)
	{
		digits->push_back(0);
		return;
	}

//	if(!positive)
//		if (DEBUG) cout << "-" << endl;
	
	unsigned long ul = abs(l);

	// int(1 << 31) becomes wacky after conversion to unsigned long,
	// so start with an unsigned long and shift 31.
	unsigned long bit = (unsigned long)1 << 31;//2147483648; //2^31

	//at most 32 bits due to being signed long (on 64 bit machines)
	for(int i=0; i<32; ++i)
	{
//		if(DEBUG) printf("%ld & %ld  = %ld\n", ul, bit, ul & bit);
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

//	if(DEBUG) cout << "\t" << *this << endl;
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
	result = *this - rhs;
	if(DEBUG) cout << *this << "-= " << rhs << " = " << result << endl;
	*this = result;
	return result;
}

megaint megaint::operator*=(const megaint & rhs) {
	megaint result;
	result = *this * rhs;
	*this = result;
	return result;
}

megaint megaint::operator/=(const megaint & rhs) {
	megaint result;
	result = *this / rhs;
	*this = result;
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

//subtraction
//depends on addition
//depends on bool()
megaint megaint::operator-(const megaint & rhs) const {
	megaint result;
	megaint tmp;
	if(!rhs)
	{
		result = *this;
		return result;
	}

	/*
	  need to make sure that for the complement we have 
	  a zero padding so the vector sizes are the same.
	*/
	if(digits->size() > rhs.digits->size())
	{
		long diff = digits->size() - rhs.digits->size();
		for(long i=1; i<diff; ++i)//start at one since tmp has a 0 already
		{
			tmp.digits->push_back(0);
		}
	  
	}

	for(unsigned int i=0; i<rhs.digits->size(); ++i)
	{
		tmp.digits->push_back(rhs.digits->at(i));
	}
		

	//first get the one's complement of the rhs
	megaint rprime = ~tmp;
	
	//then add
	result = *this + rprime;

	//drop the leading one...
	result.digits->erase(result.digits->begin());
	
	result.normalize();

	if(DEBUG) cout << *this << " - " << rhs << " = " << result << endl;

	return result;
}

//multiplication
//depends on addition
//depends on subtraction
megaint megaint::operator*(const megaint & rhs) const {
	megaint result;
	if(!rhs)
	{
		// mult by 0
		return result;
	}

	if(rhs.digits->size() == 1 && rhs.digits->at(0))
	{
		//mult by 1
		result = *this;
		return result;
	}

	megaint tmp = rhs;
	result = *this;

	if(rhs.isEven() == false)
	{
		megaint one(1);
		tmp -= one;
	}
	
	megaint two(2);

	while(tmp)
	{
		result.digits->push_back(0);
		tmp -= 2;
	}

	if(rhs.isEven() == false)
	{
		//add *this one more time
		result += *this;
	}

	//a single negative
	if( (positive && !rhs.positive) || (!positive && rhs.positive) )
	{
		//result negative
		result.positive = false;
	}
	

	if(DEBUG) cout << *this << " * " << rhs << " = " << result << endl;

	return result;
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
//	if(!mi.positive)
//		os << '-';

	for(unsigned int i=0; i<mi.digits->size(); ++i)
	{
		
		os << (unsigned int)mi.digits->at(i);
	}
	
	return os;
}

istream & operator>>(istream & is, megaint & mi) {
	string num;
	is >> num;
	megaint n(num);
	mi = n;
	return is;
}

bool megaint::isEven() const {
	//just need to check if the lowest bit is set
	bool result;
	if(digits->back())
	{
		result = false;
	}
	else
	{
		result = true;
	}
	
	if(DEBUG) cout << *this << " isEven == " << result << endl;
	return result;
}
