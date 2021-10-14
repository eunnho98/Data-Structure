#include <iostream>
#include"Cpparray.h"
using namespace std;



int main() {
	CppArray arr1(5, 0);
	
	arr1[2] = 3;
	cout << arr1 << endl;

	CppArray arr2 = arr1;
	CppArray arr3 = arr1;
	cin >> arr3;
	cout << arr2 << endl;
	cout << arr3 << endl;
}