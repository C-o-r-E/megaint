#ifndef MEGAINT_H
#define MEGAINT_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class megaint
{
		int val;
		bool positive;
		vector<unsigned int> * digits;
	public:
		megaint(const int x);
		megaint(const string & num);
		~megaint();
		megaint & operator+=(const megaint & rhs);
		megaint & operator-=(const megaint & rhs);
		megaint & operator*=(const megaint & rhs);
		megaint & operator/=(const megaint & rhs);
		const megaint operator+(const megaint & rhs) const;
		const megaint operator-(const megaint & rhs) const;
		const megaint operator*(const megaint & rhs) const;
		const megaint operator/(const megaint & rhs) const;
		bool operator==(const megaint & other) const;
		bool operator!=(const megaint & other) const;
		friend ostream & operator<<(ostream & os, const megaint & mi);
};

//ostream & operator<<(ostream & os, const megaint & mi);
#endif
