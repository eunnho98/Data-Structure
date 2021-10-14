#pragma once
#include <iostream>
using namespace std;

class CppArray {
private:
	int size;
	int* parr;

public:
	CppArray(int s, int default_val); 
	CppArray(const CppArray& copy);
	CppArray& operator=(const CppArray& copy);
	int& operator[](int idx);
	int& operator[](int idx) const;
	int getSize();
	~CppArray();
	friend ostream& operator<<(ostream&, const CppArray&);
	friend istream& operator>>(istream&, CppArray&);
};