#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
void ChangeSize(T*& arr, const int oldsize, const int newsize) {
	if (newsize < 0) throw "���ο� ũ�Ⱑ 0���� �۽��ϴ�";
	T* temp = new T[newsize];
	int mini = min(oldsize, newsize);
	copy(arr, arr + mini, temp); // copy(v.begin(), v.begin() + n, u.begin()) -> [v.begin() : v.begin() + n) �� u.begin()���� ����
	delete[] arr;
	arr = temp;
}

template<typename T>
void ChangeSize(T& arr, const int oldsize, const int newsize) {
	if (newsize < 0) throw "���ο� ũ�Ⱑ 0���� �۽��ϴ�";
	T* temp = new T[newsize];
	int mini = min(oldsize, newsize);
	copy(arr, arr + mini, temp); // copy(v.begin(), v.begin() + n, u.begin()) -> [v.begin() : v.begin() + n) �� u.begin()���� ����
	delete[] arr;
	arr = temp;
}

template<typename T>
class Stack {
private:
	T* stack; // stack�� ���� ���� �迭
	int top; // top ������ idx
	int cap; // �迭�� ũ��
public:
	Stack(int c = 10);
	~Stack();
	bool IsEmpty() const; // ������ ������� Ȯ��
	T& Top() const; // Top ���� ��ȯ
	void Push(const T& item);
	void Pop(); // ���� ž ���� ����

	// ����
	void Split_Stack(Stack<T>& s); // ������ ������ �и�
	void Mix_Stack(Stack<T>& s); // �� ���� ��ġ��

	template<class T>
	friend ostream& operator<<(ostream& os, const Stack<T>& s); // �������
};

template<typename T>
ostream& operator<<(ostream& os, const Stack<T>& s) {
	for (int i = 0; i <= s.top; i++) {
		os << s.stack[i] << endl;
	}
	return os;
}

template<typename T>
void Stack<T>::Split_Stack(Stack<T>& s) { // this : ���ݺ��� top����, s :  0���� ���ݱ��� ����
	int z_to_m = (s.top / 2) + 1; // 0���� ���ݱ����� ũ��
	int m_to_e = (s.top - z_to_m) + 1; // ���ݺ��� �������� ũ��
	ChangeSize(stack, cap, m_to_e);
	cap = m_to_e;
	for (int i = 0; i < cap; i++) {
		Push(s.stack[i + z_to_m]);
	}
	while (s.top != z_to_m - 1) {
		s.Pop();
	}
}

template<typename T>
void Stack<T>::Mix_Stack(Stack<T>& s) {
	while (!s.IsEmpty()) {
		Push(s.stack[s.top]);
		s.Pop();
	}
}

template<typename T>
Stack<T>::Stack(int c) {
	if (c < 0) throw "�迭�� ũ�Ⱑ 0���� �۽��ϴ�";
	cap = c;
	top = -1;
	stack = new T[cap];
}

template<typename T>
Stack<T>::~Stack() {
	delete[]stack;
}

template<typename T>
bool Stack<T>::IsEmpty() const {
	return (top == -1);
}

template<typename T>
T& Stack<T>::Top() const {
	if (IsEmpty()) throw "������ ������ϴ�";
	return stack[top];
}

template<typename T>
void Stack<T>::Push(const T& item) {
	if (top + 1 == cap) { // ������ �� ����
		ChangeSize(stack, cap, cap * 2);
		cap = cap * 2;
	}
	stack[++top] = item; // top ��������
}


template<typename T>
void Stack<T>::Pop() {
	if (IsEmpty()) throw "������ ������ϴ�";
	stack[top--].~T();
}

int precedence(char c) { // ���ڷ� �켱���� �Ǵ�
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	else if (c == ')') return 0;
}


int main() {
	string s;
	string var1, var2, str; // var2 �� var1
	Stack<string> stack;
	cout << "Input Prefix : ";
	cin >> s;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			bool IsUse1 = false; // var1�� ��ȣ �ʿ�?
			bool IsUse2 = false; // var2�� ��ȣ �ʿ�?
			switch (s[i])
			{
			case '+' :
				var2 = stack.Top();
				stack.Pop();
				var1 = stack.Top();
				stack.Pop();
				str = var1 + "+" + var2;
				stack.Push(str);
				break;
			case '-' :
				var2 = stack.Top();
				stack.Pop();
				var1 = stack.Top();
				stack.Pop();
				str = var1 + "-" + var2;
				stack.Push(str);
				break;
			case '*' :
				var2 = stack.Top();
				stack.Pop();
				var1 = stack.Top();
				stack.Pop();
				for (int i = 0; i < var2.length(); i++) {
					if (var2[i] == '+' || var2[i] == '-') {
						IsUse2 = true;
						break;
					}
				}
				for (int i = 0; i < var1.length(); i++) {
					if (var1[i] == '+' || var1[i] == '-') {
						IsUse1 = true;
						break;
					}
				}

				if (!IsUse1 && !IsUse2) {
					str = var1 + "*" + var2;
					stack.Push(str);
					break;
				}
				else if (IsUse1 && !IsUse2) {
					str = "(" + var1 + ")" + "*" + var2;
					stack.Push(str);
					break;
				}
				else if (!IsUse1 && IsUse2) {
					str = var1 + "*" + "(" + var2 + ")";
					stack.Push(str);
					break;
				}
				else {
					str = "(" + var1 + ")" + "*" + "(" + var2 + ")";
					stack.Push(str);
					break;
				}
				
			case '/' :
				var2 = stack.Top();
				stack.Pop();
				var1 = stack.Top();
				stack.Pop();
				for (int i = 0; i < var2.length(); i++) {
					if (var2[i] == '+' || var2[i] == '-') {
						IsUse2 = true;
						break;
					}
				}
				for (int i = 0; i < var1.length(); i++) {
					if (var1[i] == '+' || var1[i] == '-') {
						IsUse1 = true;
						break;
					}
				}

				if (!IsUse1 && !IsUse2) {
					str = var1 + "-" + var2;
					stack.Push(str);
					break;
				}
				else if (IsUse1 && !IsUse2) {
					str = "(" + var1 + ")" + "-" + var2;
					stack.Push(str);
					break;
				}
				else if (!IsUse1 && IsUse2) {
					str = var1 + "-" + "(" + var2 + ")";
					stack.Push(str);
					break;
				}
				else {
					str = "(" + var1 + ")" + "-" + "(" + var2 + ")";
					stack.Push(str);
					break;
				}
			} 
		}
		else {
			string tmp; // char to string
			tmp += s[i];
			stack.Push(tmp);
		}
	}
	cout << stack << endl;

	return 0;
}