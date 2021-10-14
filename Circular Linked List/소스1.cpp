#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class CircularChain; // 전방 선언

class Node {
	friend class CircularChain;
private:
	int data;
	Node* link;
public:
	Node(int data = 0, Node* next = NULL) {
		this->data = data;
		link = next;
	}
	Node* Link() { return link; }
	~Node() { delete link; }
};

class CircularChain {
private:
	Node* tail;
	Node* head; // 공백리스트 구분 목적
public:
	class CircularChainIterator {
	private:
		Node* current;
	public:
		//생성자
		CircularChainIterator(Node* startNode = NULL) {
			current = startNode;
		}
		//역참조
		int& operator*() const { return current->data; }
		// 증가
		CircularChainIterator& operator++() {
			current = current->link;
			return *this;
		}
		CircularChainIterator& operator++(int) {
			CircularChainIterator old = *this;
			current = current->link;
			return old;
		}
		//Bool
		bool operator!=(const CircularChainIterator i) const {
			return current != i.current;
		}
	};
	CircularChain() {
		tail = new Node();
		tail->link = tail;
		head = tail->link;
	}
	
	int GetNodeNum() const;
	void Insert(Node*);
	void Delete(Node*);
	CircularChain& SumChain(CircularChain& c1, CircularChain& c2);
	void Reverse();
	void CopytoArray(int*&, int&);
	CircularChainIterator begin() { return CircularChainIterator(head->link); }
	CircularChainIterator end() { return CircularChainIterator(tail); }

	friend ostream& operator<<(ostream&, CircularChain&);
};

ostream& operator<<(ostream& os, CircularChain& c) {
	CircularChain::CircularChainIterator iter = c.begin();
	os << "Head -- >";
	while (iter != c.end()) {
		os << *iter << " --> ";
		iter++;
	}
	os << *iter << " --> Head" << '\n';
	return os;
}

int CircularChain::GetNodeNum() const {
	Node* tmp = tail->link; // tmp = head
	int count = 0;
	
	while (tmp != tail) {
		tmp = tmp->link;
		count++;
	}
	return count;
}

void CircularChain::Insert(Node* node) { // node = new Node(item);
	if (GetNodeNum() == 0) {
		cout << "Empty Chain, Put in first : ";
		tail->link = node;
		tail = tail->link;
		tail->link = head;
		return;
	}
	cout << *this << endl;
	cout << "Input Insert Num, except Head : "; 
	int num;
	cin >> num;
	if (num > GetNodeNum() + 1) {
		cout << "Index over" << endl;
		return;
	}
	Node* tmp = tail;
	for (int i = 0; i < num; i++) {
		tmp = tmp->link; // tmp는 삽입할 위치 바로 전 노드
	}
	node->link = tmp->link;
	tmp->link = node;
	if (num == GetNodeNum()) {
		tail = node;
	}
}

void CircularChain::Delete(Node* node) { //노드 번호로 삭제
	if (GetNodeNum() == 0) {
		cout << "Empty Chain" << endl;
		return;
	}
	cout << *this << endl;
	cout << "Input Delete Node num, Except Head : ";
	int num;
	cin >> num;
	Node* pre = tail;
	for (int i = 0; i < num; i++) {
		pre = pre->link;
	}
	node = pre->link;
	pre->link = node->link;
	node->link = NULL;
	delete node;
	if (pre->link == head) {
		tail = pre;
	}
	this->tail = tail;
	this->head = head;
}

CircularChain& CircularChain::SumChain(CircularChain& c1, CircularChain& c2) {
	
	this->tail = new Node();
	this->tail->link = tail;
	this->head = tail;

	int c1num = c1.GetNodeNum();
	int c2num = c2.GetNodeNum();
	Node* c1tmp = c1.tail->link->link;
	Node* c2tmp = c2.tail->link->link;
	Node* thistmp = this->tail;
	while (c1num > 0 && c2num > 0) {
		Insert(new Node(c1tmp->data));
		c1tmp = c1tmp->link;
		Insert(new Node(c2tmp->data));
		c2tmp = c2tmp->link;
		c1num--; c2num--;
	}
	while (c1num > 0) {
		Insert(new Node(c1tmp->data));
		c1tmp = c1tmp->link;
		c1num--;
	}
	while (c2num > 0) {
		Insert(new Node(c2tmp->data));
		c2tmp = c2tmp->link;
		c2num--;
	}
	delete c1.tail;
	delete c1.head;
	delete c2.tail;
	delete c2.head;
	return *this;

}

void CircularChain::Reverse() {
	Node* newnode = new Node();
	Node* current = head->link;
	Node* pre = NULL;
	while (current != head) {
		Node* r = pre;
		pre = current;
		current = current->link;
		pre->link = r;
	}
	tail = head->link;
	newnode->link = pre;
	head = newnode;
	tail->link = head;
}

void CircularChain::CopytoArray(int*& arr, int& len) {
	len = GetNodeNum();
	arr = new int[len];
	CircularChain::CircularChainIterator iter = begin();
	int idx = 0;
	while (iter != end()) {
		arr[idx] = *iter;
		iter++;
		idx++;
	}
	arr[idx] = *iter;
}

int main() {

	CircularChain a;
	CircularChain b;
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	a.Insert(n1);
	a.Insert(n2);
	a.Insert(n3);
	cout << a << endl;
	a.Delete(new Node());
	cout << a << endl;
	
	int* arr;
	int len;
	a.CopytoArray(arr, len);
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	


	return 0;
}