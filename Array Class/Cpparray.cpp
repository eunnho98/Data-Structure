#include "Cpparray.h"

CppArray::CppArray(int s, int default_val) {
		size = s;
		parr = new int[size];
		for (int i = 0; i < size; i++) {
			parr[i] = default_val;
		}
}

CppArray::CppArray(const CppArray& copy) {
	this->size = copy.size;
	parr = new int[size];
	for (int i = 0; i < size; i++) {
		parr[i] = copy.parr[i];
	}
}

CppArray& CppArray::operator=(const CppArray& copy) {
	delete[]parr;
	size = copy.size;
	parr = new int[size];
	for (int i = 0; i < size; i++) {
		parr[i] = copy.parr[i];
	}
	return *this;
}

int& CppArray::operator[](int idx) {
	if (idx < 0 || idx > size) {
		cout << "Out of range" << endl;
		exit(1);
	}
	return parr[idx];
}

int& CppArray::operator[](int idx) const {
	if (idx < 0 || idx > size) {
		cout << "Out of range" << endl;
		exit(1);
	}
	return parr[idx];
}

int CppArray::getSize() {
	return size;
}

CppArray::~CppArray() {
	delete[]parr;
}

ostream& operator<<(ostream& os, const CppArray& arr) {
	for (int i = 0; i < arr.size; i++) {
		os << arr[i] << " ";
	}
	return os;
}

istream& operator>>(istream& is, CppArray& arr) {
	delete[]arr.parr;
	arr.parr = new int[arr.size];
	for (int i = 0; i < arr.size; i++) {
		is >> arr.parr[i];
	}
	return is;
}