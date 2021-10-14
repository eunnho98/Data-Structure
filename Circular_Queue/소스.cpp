#include <iostream>
#include <algorithm>
using namespace std;

/*
���� ť : ���Ҹ� ��� �������� �Ű���� �ϴ� ����, ��������4 �� �� rear�� 4�� ����Ű�� front�� 4�� ���� ����Ű�� ���� ť������ ť�� ���� á�ٰ� �޾Ƶ���
���� ť : front�� ù ���ҷκ��� �ð� �ݴ�������� �ϳ� �� ��ġ�� ����Ű���� ����, �� ĭ�� �׻� ���ܵξ� ��ȭ���¿� �� ���¸� �����ϵ��� ��
*/

template <typename T>
class Queue {
public:
	Queue(int queue_cap = 10);
	bool IsEmpty() const; // ť�� ���Ҽ��� 0�̸� T, �ƴϸ� F
	bool IsFull() const;
	T& Front() const; // ť ���� �տ��ִ� ���� ��ȯ
	T& Rear() const; // ť ���� �ڿ��ִ� ���� ��ȯ
	void Push(const T& item); // �� ���� ����
	void Pop(); // Front ���� ����

	// ����
	int Getcap() const {return cap; } // ť�� ũ�� ��ȯ
	int Getnum() const { if (rear - front) > 0 return (rear - front); else return cap - (front - rear); } // ť�� ���� �� ��ȯ
	Queue<T>& MergeQueue(Queue<T> queue1, Queue<T> queue2); // �� ť�� ���Ҹ� �ϳ��� Push�� ���ο� ť ��ȯ

	template<typename U>
	friend ostream& operator<<(ostream&,Queue<U> );
private:
	T* queue;
	int front; // ù ������ �ð� �ݴ�������� �� ĭ ���� ����Ŵ
	int rear; // ������ ���� ����Ŵ
	int cap; // ť �迭�� ũ�� = �ִ���� �� + 1

};

template<typename U>
ostream& operator<<(ostream& os, Queue<U> qu ) {
	while (!qu.IsEmpty()) {
		os << qu.Front() << " ";
		qu.Pop();
	}
	return os;
}

template<typename T>
// �� ť�� ���Ҹ� �ϳ��� Push�� ���ο� ť ��ȯ
Queue<T>& Queue<T>::MergeQueue(Queue<T> queue1, Queue<T> queue2) {
	Queue<T> tmp;
	while (!queue1.IsEmpty() && !queue2.IsEmpty()) {
		tmp.Push(queue1.Front());
		tmp.Push(queue2.Front());
		queue1.Pop();
		queue2.Pop();
	}
	while (!queue1.IsEmpty()) { // ���� ���� Push
		tmp.Push(queue1.Front());
		queue1.Pop();
	}
	while (!queue2.IsEmpty()) { // ���� ���� Push
		tmp.Push(queue2.Front());
		queue2.Pop();
	}
	delete[]queue;
	*this = tmp;
	return *this;
}

template <class T>
Queue<T>::Queue(int qu) : cap(qu) {
	queue = new T[cap];
	front = rear = 0;
}

template <class T>
bool Queue<T>::IsEmpty() const {
	return (front == rear);
}

template<typename T>
bool Queue<T>::IsFull() const {
	// rear �ð���� �� ĭ �տ� front�� �ִ���?
	return((rear + 1) % cap == front); // (rear + 1) % cap == if(rear = cap - 1) rear = 0;, else rear++;
}

template<typename T>
T& Queue<T>::Front() const {
	if (IsEmpty()) throw "Queue is Empty";
	return queue[(front + 1) % cap];
}

template<typename T>
T& Queue<T>::Rear() const {
	if (IsEmpty()) throw "Queue is Empty";
	return queue[rear];
}

template<typename T>
void Queue<T>::Push(const T& item) {
	if (IsFull()) {
		// ť ����� �ι�� �ø��� �ڵ�
		// A B C D �� �� �� �� �� �� ������ ����
		T* newqueue = new T[2 * cap];
		int start = (front + 1) % cap; // (front == 0) || (front == (cap -1))
		if (start < 2) { // �� ���� ���α�, A B C D �� || �� A B C D 
			copy(queue + start, queue + start + cap - 1, newqueue);
		}
		else { // C D �� A B �� ���� ������ �߰��� �ִ� ���
			copy(queue + start, queue + cap, newqueue);
			copy(queue, queue + rear + 1/* == queue + front */, newqueue + cap - start);
		}
		front = (2 * cap) - 1;
		rear = cap - 2;
		cap = 2 * cap;
		delete[] queue;
		queue = newqueue;
	}
	rear = (rear + 1) % cap; // rear�� �ð� �������� �� ĭ �ű�� �ڵ�
	queue[rear] = item;
}

template<typename T>
void Queue<T>::Pop() {
	if (IsEmpty()) throw "Queue is Empty";
	front = (front + 1) % cap; // front�� �ð� �������� �� ĭ �ű�� �ڵ�
	queue[front].~T();
}

int main() {
	Queue<int> q1;
	
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	cout << q1 << endl;
}