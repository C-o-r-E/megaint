#ifndef MEGAINT_H
#define MEGAINT_H
#include <string>
#include <vector>
#include <iostream>
#include <stdint.h>

using namespace std;
class megaint
{
		static const bool DEBUG=false;
		int val;
		bool positive;
		vector<bool> * digits;
		//megaint(const vector<uint8_t> & digs, bool positive);
		void normalize();
	public:
		megaint();
		megaint(const megaint & original);
		megaint(const long l);
		megaint(const string & num);
		~megaint();
		megaint & operator=(const megaint & rhs);
		megaint operator+=(const megaint & rhs);
		megaint operator-=(const megaint & rhs);
		megaint operator*=(const megaint & rhs);
		megaint operator/=(const megaint & rhs);
		megaint operator+(const megaint & rhs) const;
		megaint operator-(const megaint & rhs) const;
		megaint operator*(const megaint & rhs) const;
		megaint operator/(const megaint & rhs) const;
		bool operator==(const megaint & other) const;
		bool operator!=(const megaint & other) const;
		megaint operator~() const;
		operator bool() const;
		bool isEven() const;
		
		friend ostream & operator<<(ostream & os, const megaint & mi);
};

//ostream & operator<<(ostream & os, const megaint & mi);
#endif
