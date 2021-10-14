#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Chain; // 전방 선언

class Node {
	friend class Chain;
private:
	int data;
	Node* link;
public:
	Node(int data = 0, Node* next = NULL) {
		this->data = data;
		link = next;
	}
	Node* Link() { return link; }
};

class Chain {
private:
	Node* first; // first 노드를 통해 모든 node에 접근
public: // Chain 조작
	class ChainIterator {
	private:
		Node* current; // 현재 노드
	public:
		// 생성자
		ChainIterator(Node* startNode = NULL) {
			current = startNode;
		}
		// 역참조 연산자
		int& operator*() const { return current->data; }
		// 증가
		ChainIterator& operator++() {
			current = current->link;
			return *this;
		}
		ChainIterator& operator++(int) {
			ChainIterator old = *this;
			current = current->link;
			return old;
		}
		// Bool
		bool operator!=(const ChainIterator c) const {
			return current != c.current;
		}
		bool operator==(const ChainIterator c) const {
			return current == c.current;
		}

	};
	Chain() { first = new Node(); }
	~Chain();
	void Insert_Tail(const int& item);
	void Insert_Mid(const int& after, const int& item); //after 아이템 뒤에 item 삽입
	void Insert_First(const int& item);
	void Delete(const int& item); // 아이템으로 삭제
	void Delete(Node*&); // 노드 번호로 삭제
	void Insert(Node*&); // 노드 번호로 삽입
	int GetNodeNum(); // 노드 개수 반환
	Chain& SumChain(Chain& c1, Chain& c2); // 두 연결리스트 합치기
	Chain& SumChain_Sort(Chain& c1, Chain& c2); // 두 연결리스트 오름차순 합치기
	void DeleteOddNode(Node*& x); // 홀수번 째 노드 삭제
	void Reverse(); // 연결리스트 뒤집기
	void print();
	int FindMin(); // 최소값 찾기
	ChainIterator begin() { return ChainIterator(first); } // first 노드를 가리키는 iterator 생성
	ChainIterator end() { return ChainIterator(NULL); } // 마지막 노드의 link를 가리키는 iterator 생성
	void CopytoArray(int *&arr, int&); // Chain을 배열에 복사
	
	friend ostream& operator<<(ostream& os, Chain& c);

	
};

ostream& operator<<(ostream& os, Chain& c) {
	Chain::ChainIterator iter = c.begin();
	iter++;
	while (iter != c.end()) {
		os << *iter << " -- > ";
		iter++;
	}
	os << "NULL" << endl;
	return os;
}

Chain::~Chain() {
	while(first != NULL) {
		Node* tmp = first;
		first = first->link;
		delete tmp;
	}
}

void Chain::Insert_Tail(const int& item) { 
	if (first->link == NULL) { // 공백 리스트에 삽입
		first->link = new Node(item);
	}
	else { 
		Node* tmp = new Node(item);
		Node* last = first;
		while (last->link != NULL) {
			last = last->link;
		}
		last->link = tmp;
	}
}

void Chain::Insert_Mid(const int& after, const int& item) {
	Node* tmp = first;
	Node* NewItem = new Node(item);
	while (tmp->data != after) {
		tmp = tmp->link;
	}
	NewItem->link = tmp->link;
	tmp->link = NewItem;
}

void Chain::Insert_First(const int& item) {
	if (first->link == NULL) { // 공백 리스트에 삽입
		first->link = new Node(item);
	}
	else {
		Node* tmp = new Node(item);
		tmp->link = first->link;
		first->link = tmp;
	}
}

void Chain::Delete(const int& item) {
	bool candel = false;
	Node* tmp = first->link;
	while (tmp!= NULL) {
		if (tmp->data == item) {
			candel = true;
			break;
		}
		else tmp = tmp->link;
	}
	if (candel == false) {
		cout << "No Match" << endl;
		return;
	}
	
	Node* before = first;
	while (before->link != tmp) {
		before = before->link;
	}
	before->link = tmp->link;
	tmp->link = NULL; // 바로 해제시키면 tmp뒤에 딸려있는 노드들도 다 해제됨, before->link가 NULL을 가리키게됨
	delete tmp;
}

void Chain::Delete(Node*& x) {
	cout << "몇 번째 노드를 삭제할 것입니까? : ";
	int num;
	cin >> num;
	x = first;
	for (int i = 0; i < num; i++) {	
		x = x->link;
	}
	Node* tmp = first;
	while (tmp->link != x) {
		tmp = tmp->link;
	}
	tmp->link = x->link;
	x->link = NULL;
	delete x;
}

void Chain::Insert(Node*& x) {
	cout << "몇 번째 노드 다음에 삽입할 것입니까? : ";
	int num;
	cin >> num;
	Node* tmp = first;
	for (int i = 0; i < num; i++) {
		tmp = tmp->link;
	}
	
	x->link = tmp->link;
	tmp->link = x;
}

void Chain::DeleteOddNode(Node*& x) {
	int num = GetNodeNum();
	x = first;
	if (num % 2 == 0) num = num / 2;
	else num = (num / 2) + 1;
	for (int i = 0; i < num; i++) {
		Node* tmp = x->link;
		x->link = x->link->link;
		x = x->link;
		tmp->link = NULL;
		delete tmp;
	}
}

int Chain::GetNodeNum() {
	int count = 0;
	Node* tmp = first;
	while (tmp->link != NULL) {
		count++;
		tmp = tmp->link;
	}
	return count;
}

Chain& Chain::SumChain(Chain& c1, Chain& c2) {
	delete this->first;
	this->first = new Node();
	int c1num = c1.GetNodeNum();
	int c2num = c2.GetNodeNum();
	Node* c1tmp = c1.first->link;
	Node* c2tmp = c2.first->link;
	Node* thistmp = this->first;
	while (c1num > 0 && c2num > 0) {
		thistmp->link = new Node(c1tmp->data);
		thistmp = thistmp->link;
		c1tmp = c1tmp->link;
		thistmp->link = new Node(c2tmp->data);
		thistmp = thistmp->link;
		c2tmp = c2tmp->link;
		c1num--; c2num--;
	}
	while (c1num > 0) {
		thistmp->link = new Node(c1tmp->data);
		c1tmp = c1tmp->link;
		thistmp = thistmp->link;
		c1num--;
	}
	while (c2num > 0) {
		thistmp->link = new Node(c2tmp->data);
		c2tmp = c2tmp->link;
		thistmp = thistmp->link;
		c2num--;
	}
	delete c1.first;
	delete c2.first;
	c1.first = new Node();
	c2.first = new Node();
	return *this;
}

Chain& Chain::SumChain_Sort(Chain& c1, Chain& c2) {
	delete this->first;
	this->first = new Node();
	int c1num = c1.GetNodeNum();
	int c2num = c2.GetNodeNum();
	Node* c1tmp = c1.first->link;
	Node* c2tmp = c2.first->link;
	Node* thistmp = this->first;
	while (c1num > 0 && c2num > 0) {
		if (c1tmp->data < c2tmp->data) {
			thistmp->link = new Node(c1tmp->data);
			thistmp = thistmp->link;
			c1tmp = c1tmp->link;
			c1num--;
		}
		else {
			thistmp->link = new Node(c2tmp->data);
			thistmp = thistmp->link;
			c2tmp = c2tmp->link;
			c2num--;
		}
	}
	while (c1num > 0) {
		thistmp->link = new Node(c1tmp->data);
		c1tmp = c1tmp->link;
		thistmp = thistmp->link;
		c1num--;
	}
	while (c2num > 0) {
		thistmp->link = new Node(c2tmp->data);
		c2tmp = c2tmp->link;
		thistmp = thistmp->link;
		c2num--;
	}
	delete c1.first;
	delete c2.first;
	c1.first = new Node();
	c2.first = new Node();
	return *this;
}

void Chain::Reverse() {
	Node* current = first->link;
	Node* pre = NULL;

	while (current != NULL) {
		Node* r = pre;
		pre = current;
		current = current->link;
		pre->link = r;
	}
	first->link = pre;
}

int Chain::FindMin() {
	Chain::ChainIterator iter = begin();
	iter++;
	int minnum = *iter;
	while (iter != end()) {
		if (*iter <= minnum) minnum = *iter;
		iter++;
	}
	return minnum;
}

void Chain::print() {
	if (first->link == NULL || first == NULL) {
		cout << "빈 리스트입니다" << endl;
	}
	else {
		Node* tmp = first->link;
		while (tmp != NULL) {
			cout << tmp->data << " --> ";
			tmp = tmp->link;
		}
		cout << "NULL" << endl;
	}
	
	
}

void Chain::CopytoArray(int*& arr, int& len) {
	len = GetNodeNum();
	arr = new int[len];
	int idx = 0;
	Chain::ChainIterator iter = begin();
	
	while (iter != end()) {
		arr[idx] = *iter;
		iter++;
		idx++;
	}
}



int main() {

	Chain a;
	Chain b;
	Chain c;
	
	a.Insert_First(3);
	a.Insert_Tail(2);
	a.Insert_Tail(5);
	a.Insert_Tail(6);
	
	int* k;
	int len;
	a.CopytoArray(k, len);
	
	for (int i = 0; i < len; i++) {
		cout << k[i] << " ";
	}
	cout << endl;
	return 0;
}
