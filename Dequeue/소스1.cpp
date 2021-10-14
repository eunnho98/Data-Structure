#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
class Dequeue {
private:
	T* dequeue;
	int front;
	int rear;
	int cap;
public:
	Dequeue(int cap = 10);
	bool IsEmpty() const;
	bool IsFull() const;
	T& Front() const;
	T& Rear() const;
	void Push_to_Rear(const T& item);
	void Push_to_Front(const T& item);
	void Pop_to_Rear();
	void Pop_to_Front();

	template<typename U>
	friend ostream& operator<<(ostream&, Dequeue<U>);
};

template<typename U>
ostream& operator<<(ostream& os, Dequeue<U> de) {
	while (!de.IsEmpty()) {
		os << de.Front() << " ";
		de.Pop_to_Front();
	}
	return os;
}

template<typename T>
Dequeue<T>::Dequeue(int cap) : cap(cap) {
	dequeue = new T[cap];
	front = rear = 0;
}

template<typename T>
bool Dequeue<T>::IsEmpty() const {
	return(front == rear);
}

template<typename T>
bool Dequeue<T>::IsFull() const {
	return((rear + 1) % cap == front);
}

template<typename T>
T& Dequeue<T>::Front() const {
	if (IsEmpty()) throw "Empty";
	return dequeue[(front + 1) % cap];
}

template<typename T>
T& Dequeue<T>::Rear() const {
	if (IsEmpty()) throw "Empty";
	return dequeue[rear];
}

template<typename T>
void Dequeue<T>::Push_to_Front(const T& item) {
	if (IsFull()) {
		// 큐 사이즈를 두배로 늘리는 코드
		T* newqueue = new T[2 * cap];
		int start = (front + 1) % cap; // front == 0 || front == (cap -1)
		if (start < 2) { // 한 번에 감싸기
			copy(dequeue + start, dequeue + start + cap - 1, newqueue);
		}
		else {
			copy(dequeue + start, dequeue + cap, newqueue);
			copy(dequeue, dequeue + rear + 1/* == queue + front */, newqueue + cap - start);
		}
		front = (2 * cap) - 1;
		rear = cap - 2;
		cap = 2 * cap;
		delete[] dequeue;
		dequeue = newqueue;
	}
	if (front == 0) front = cap - 1;
	else front--;
	dequeue[front] = item;
}

template<typename T>
void Dequeue<T>::Push_to_Rear(const T& item) {
	if (IsFull()) {
		// 큐 사이즈를 두배로 늘리는 코드
		T* newqueue = new T[2 * cap];
		int start = (front + 1) % cap; // front == 0 || front == (cap -1)
		if (start < 2) { // 한 번에 감싸기
			copy(dequeue + start, dequeue + start + cap - 1, newqueue);
		}
		else {
			copy(dequeue + start, dequeue + cap, newqueue);
			copy(dequeue, dequeue + rear + 1/* == queue + front */, newqueue + cap - start);
		}
		front = (2 * cap) - 1;
		rear = cap - 2;
		cap = 2 * cap;
		delete[] dequeue;
		dequeue = newqueue;
	}
	rear = (rear + 1) % cap; // rear을 시계 방향으로 한 칸 옮기는 코드
	dequeue[rear] = item;
}

template<typename T>
void Dequeue<T>::Pop_to_Rear() {
	if (IsEmpty()) throw "empty";
	else {
		dequeue[rear].~T();
		if (rear == 0) rear = cap - 1;
		else rear--;
	}
}

template<typename T>
void Dequeue<T>::Pop_to_Front() {
	if (IsEmpty()) throw "empty";
	front = (front + 1) & cap;
	dequeue[front].~T();

}

int main() {
	Dequeue<int> d;
	d.Push_to_Rear(1);
	d.Push_to_Rear(2);
	d.Push_to_Rear(3);
	try {
		cout << d << endl;
	}
	catch (string s) {
		cout << s << endl;
	}


}