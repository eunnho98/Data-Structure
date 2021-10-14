#include <iostream>
#include <algorithm>
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
	int z_to_m = (s.top/2) + 1; // 0���� ���ݱ����� ũ��
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
int main() {

	Stack<int> S(10);
	Stack<int> S2(10);
	try {
		S.Push(1);
		S.Push(2);
		S.Push(3);
		S.Push(4);
		S.Push(5);
	}
	catch (const char* exp)
	{
		cout << exp << endl;
	}
	cout << "���� ����" << endl;
	cout << S << endl;
	cout << "���� ���� : 0 to mid" << endl;
	S2.Split_Stack(S);
	cout << S << endl;
	cout << "mid to end" << endl;
	cout << S2 << endl;
	cout << "��ġ��" << endl;
	S2.Mix_Stack(S);
	cout << S2 << endl;

	
	return 0;
}