#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
void ChangeSize(T*& arr, const int oldsize, const int newsize) {
	if (newsize < 0) throw "새로운 크기가 0보다 작습니다";
	T* temp = new T[newsize];
	int mini = min(oldsize, newsize);
	copy(arr, arr + mini, temp); // copy(v.begin(), v.begin() + n, u.begin()) -> [v.begin() : v.begin() + n) 을 u.begin()부터 복사
	delete[] arr;
	arr = temp;
}

template<typename T>
void ChangeSize(T& arr, const int oldsize, const int newsize) {
	if (newsize < 0) throw "새로운 크기가 0보다 작습니다";
	T* temp = new T[newsize];
	int mini = min(oldsize, newsize);
	copy(arr, arr + mini, temp); // copy(v.begin(), v.begin() + n, u.begin()) -> [v.begin() : v.begin() + n) 을 u.begin()부터 복사
	delete[] arr;
	arr = temp;
}

template<typename T>
class Stack {
private:
	T* stack; // stack을 위한 원소 배열
	int top; // top 원소의 idx
	int cap; // 배열의 크기
public:
	Stack(int c = 10);
	~Stack();
	bool IsEmpty() const; // 스택이 비었는지 확인
	T& Top() const; // Top 원소 반환
	void Push(const T& item);
	void Pop(); // 스택 탑 원소 삭제

	// 번외
	void Split_Stack(Stack<T>& s); // 스택을 반으로 분리
	void Mix_Stack(Stack<T>& s); // 두 스택 합치기

	template<class T>
	friend ostream& operator<<(ostream& os, const Stack<T>& s); // 스택출력
};

template<typename T>
ostream& operator<<(ostream& os, const Stack<T>& s) {
	for (int i = 0; i <= s.top; i++) {
		os << s.stack[i] << endl;
	}
	return os;
}

template<typename T>
void Stack<T>::Split_Stack(Stack<T>& s) { // this : 절반부터 top까지, s :  0부터 절반까지 분할
	int z_to_m = (s.top / 2) + 1; // 0부터 절반까지의 크기
	int m_to_e = (s.top - z_to_m) + 1; // 절반부터 끝까지의 크기
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
	if (c < 0) throw "배열의 크기가 0보다 작습니다";
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
	if (IsEmpty()) throw "스택이 비었습니다";
	return stack[top];
}

template<typename T>
void Stack<T>::Push(const T& item) {
	if (top + 1 == cap) { // 스택이 꽉 차면
		ChangeSize(stack, cap, cap * 2);
		cap = cap * 2;
	}
	stack[++top] = item; // top 전위증가
}


template<typename T>
void Stack<T>::Pop() {
	if (IsEmpty()) throw "스택이 비었습니다";
	stack[top--].~T();
}

int precedence(char c) { // 숫자로 우선순위 판단
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	else if (c == ')') return 0;
}


int main() {
	// 입력한 수식 뒤에서부터 infix -> postfix와 같은 방식으로 
	// 마지막에 result를 뒤집기
	string s;
	cout << "수식을 입력하세요 : ";
	cin >> s;
	int len = s.length();
	Stack<char> stack;
	string result = "";

	for (int i = len - 1; i >= 0; i--) {
		if (s[i] == ')') stack.Push(s[i]);

		else if (s[i] == '(') {
			while (!stack.IsEmpty()) {
				if (stack.Top() == ')') {
					stack.Pop();
					break;
				}
				else {
					result += stack.Top();
					stack.Pop();
				}
			}
		}

		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (stack.IsEmpty()) {
				stack.Push(s[i]);
			}
			else {
				while (!stack.IsEmpty()) {
					if (precedence(stack.Top()) < precedence(s[i])) {
						// 들어온 것이 우선순위가 더 높으면
						stack.Push(s[i]);
						break;
					}
					else { // Top에 있는 연산자가 우선순위가 높거나 같으면
						result += stack.Top();
						stack.Pop();
					}
				}
				if (stack.IsEmpty()) {
					stack.Push(s[i]);
				}
			}
		}

		else { // 피연산자
			result += s[i];
		}

	}
	
	while (!stack.IsEmpty()) {
		result += stack.Top();
		stack.Pop();
	}

	for (int i = result.length() - 1; i >= 0; i--) {
		cout << result[i];
	}
	cout << endl;

	return 0;
}