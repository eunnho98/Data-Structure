#include <iostream>
#include <algorithm>
using namespace std;

/*
선형 큐 : 원소를 계속 왼쪽으로 옮겨줘야 하는 단점, ㅁㅁㅁㅁ4 일 때 rear이 4를 가리키고 front가 4의 앞을 가리키면 선형 큐에서는 큐가 가득 찼다고 받아들임
원형 큐 : front가 첫 원소로부터 시계 반대방향으로 하나 앞 위치를 가리키도록 변경, 한 칸은 항상 남겨두어 포화상태와 빈 상태를 구분하도록 함
*/

template <typename T>
class Queue {
public:
	Queue(int queue_cap = 10);
	bool IsEmpty() const; // 큐의 원소수가 0이면 T, 아니면 F
	bool IsFull() const;
	T& Front() const; // 큐 제일 앞에있는 원소 반환
	T& Rear() const; // 큐 제일 뒤에있는 원소 반환
	void Push(const T& item); // 새 원소 삽입
	void Pop(); // Front 원소 삭제

	// 번외
	int Getcap() const {return cap; } // 큐의 크기 반환
	int Getnum() const { if (rear - front) > 0 return (rear - front); else return cap - (front - rear); } // 큐의 원소 수 반환
	Queue<T>& MergeQueue(Queue<T> queue1, Queue<T> queue2); // 두 큐의 원소를 하나씩 Push한 새로운 큐 반환

	template<typename U>
	friend ostream& operator<<(ostream&,Queue<U> );
private:
	T* queue;
	int front; // 첫 원소의 시계 반대방향으로 한 칸 앞을 가리킴
	int rear; // 마지막 원소 가리킴
	int cap; // 큐 배열의 크기 = 최대원소 수 + 1

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
// 두 큐의 원소를 하나씩 Push한 새로운 큐 반환
Queue<T>& Queue<T>::MergeQueue(Queue<T> queue1, Queue<T> queue2) {
	Queue<T> tmp;
	while (!queue1.IsEmpty() && !queue2.IsEmpty()) {
		tmp.Push(queue1.Front());
		tmp.Push(queue2.Front());
		queue1.Pop();
		queue2.Pop();
	}
	while (!queue1.IsEmpty()) { // 남는 원소 Push
		tmp.Push(queue1.Front());
		queue1.Pop();
	}
	while (!queue2.IsEmpty()) { // 남는 원소 Push
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
	// rear 시계방향 한 칸 앞에 front가 있는지?
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
		// 큐 사이즈를 두배로 늘리는 코드
		// A B C D ㅁ ㅁ ㅁ ㅁ ㅁ ㅁ 구조로 변경
		T* newqueue = new T[2 * cap];
		int start = (front + 1) % cap; // (front == 0) || (front == (cap -1))
		if (start < 2) { // 한 번에 감싸기, A B C D ㅁ || ㅁ A B C D 
			copy(queue + start, queue + start + cap - 1, newqueue);
		}
		else { // C D ㅁ A B 와 같이 공백이 중간에 있는 경우
			copy(queue + start, queue + cap, newqueue);
			copy(queue, queue + rear + 1/* == queue + front */, newqueue + cap - start);
		}
		front = (2 * cap) - 1;
		rear = cap - 2;
		cap = 2 * cap;
		delete[] queue;
		queue = newqueue;
	}
	rear = (rear + 1) % cap; // rear을 시계 방향으로 한 칸 옮기는 코드
	queue[rear] = item;
}

template<typename T>
void Queue<T>::Pop() {
	if (IsEmpty()) throw "Queue is Empty";
	front = (front + 1) % cap; // front를 시계 방향으로 한 칸 옮기는 코드
	queue[front].~T();
}

int main() {
	Queue<int> q1;
	
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	cout << q1 << endl;
}