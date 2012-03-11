#ifndef MEGAINT_H
#define MEGAINT_H
#include <string>
#include <vector>
#include <iostream>
#include <stdint.h>

using namespace std;
class megaint
{  
		int val;
		bool positive;
		vector<uint8_t> * digits;
	public:
		megaint(const long l);
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
