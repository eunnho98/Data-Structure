#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class List {
private:
	T* list;
	int front; // ù ���� �ٷ� ������ ����Ŵ
	int rear; // ������ ���Ҹ� ����Ŵ
	int cap;
public:
	List(int l = 10);
	~List();
	void remove(int idx); // front���� idx�� ° ���� ���� ( front ������ 0��°)
	void add(int idx, const T& item); // front���� idx�� °�� item ����, front �ٷ� ������ 0��°
	T& Get(int idx) const; // idx�� ° ���� ��ȯ
	int Getnum() const; // ���� �� ��ȯ
	bool IsEmpty() const;
	bool IsFull() const;

	template<typename U>
	friend ostream& operator<<(ostream&, List<U>);
};

template<typename U>
ostream& operator<<(ostream& os, List<U> l) {
	int count = l.Getnum();
	int tmp = 1;
	while (count > 0) {
		os << l.list[(l.front + tmp) % l.cap] << " ";
		tmp++;
		count--;
	}
	return os;
}

template<typename T>
List<T>::List(int l) {
	cap = l;
	front = rear = 0;
	list = new T[cap];
}

template<typename T>
List<T>::~List() {
	delete[] list;
}

template<typename T>
void List<T>::remove(int idx) {
	if (idx == 0) {
		front = (front + 1) % cap;
		list[front].~T();
	}
	else if (idx == Getnum() - 1) {
		list[rear].~T();
		if (rear == 0) rear = cap - 1;
		else rear--;
	}
	else {
		int R_idx = (front + idx + 1) % cap;
		int move_num = Getnum() - idx - 1;
		list[R_idx].~T();
		for (int i = 1; i <= move_num; i++) {
			list[R_idx % cap] = list[(R_idx + 1) % cap];
			R_idx++;
		}
		rear = (front + Getnum() - 1) % cap;
	}
}

template<typename T>
void List<T>::add(int idx, const T& item) {
	if (IsFull()) {
		T* newlist = new T[2 * cap];
		int start = (front + 1) % cap; // front == 0 || front == (cap -1)
		if (start < 2) { // �� ���� ���α�
			copy(list + start, list + start + cap - 1, newlist);
		}
		else {
			copy(list + start, list + cap, newlist);
			copy(list, list + rear + 1, newlist + cap + start);
		}
		front = (2 * cap) - 1;
		rear = cap - 2;
		cap = 2 * cap;
		delete[] list;
		list = newlist;
	}

	if (IsEmpty()) {
		rear++;
		list[rear] = item;
	}

	else if (idx == Getnum()) {
		rear = (rear + 1) % cap;
		list[rear] = item;
	}
	else {
		int count = Getnum() - idx;
		int tmp = 1;
		T abc = item;
		while (count > 0) {
			T t_item = list[(front + tmp) % cap];
			list[(front + tmp) % cap] = abc;
			abc = t_item;
			tmp++;
			count--;
		}
		rear = (front + tmp) % cap;
		list[rear] = abc;
	}
}

template<typename T>
T& List<T>::Get(int idx) const {
	return list[front + idx + 1];
}

template<typename T>
int List<T>::Getnum() const {
	if (rear - front > 0) {
		return rear - front;
	}
	else if (IsEmpty()) {
		return 0;
	}
	else {
		return cap - (front - rear);
	}
}

template<typename T>
bool List<T>::IsEmpty() const {
	return (front == rear);
}

template<typename T>
bool List<T>::IsFull() const {
	return((rear + 1) % cap == front);
}

int main() {

	List<int> l(10);
	l.add(0, 1);
	l.add(1, 2);
	l.add(0, 0);
	l.remove(1);
	cout << l << endl;

	return 0;
}