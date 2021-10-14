#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Chain; // ���� ����

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
	~Node() { delete link; }
};

class Chain {
private:
	Node* first; // first ��带 ���� ��� node�� ����
public: // Chain ����
	class ChainIterator {
	private:
		Node* current; // ���� ���
	public:
		// ������
		ChainIterator(Node* startNode = NULL) {
			current = startNode;
		}
		// ������ ������
		int& operator*() const { return current->data; }
		// ����
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
	void Insert_Tail(const int& item);
	void Insert_Mid(const int& after, const int& item); //after ������ �ڿ� item ����
	void Insert_First(const int& item);
	void Delete(const int& item); // ���������� ����
	void Delete(Node*&); // ��� ��ȣ�� ����
	void Insert(Node*&); // ��� ��ȣ�� ����
	int GetNodeNum(); // ��� ���� ��ȯ
	Chain& SumChain(Chain& c1, Chain& c2); // �� ���Ḯ��Ʈ ��ġ��
	Chain& SumChain_Sort(Chain& c1, Chain& c2); // �� ���Ḯ��Ʈ �������� ��ġ��
	void DeleteOddNode(Node*& x); // Ȧ���� ° ��� ����
	void Reverse(); // ���Ḯ��Ʈ ������
	void print();
	int FindMin(); // �ּҰ� ã��
	ChainIterator begin() { return ChainIterator(first); } // first ��带 ����Ű�� iterator ����
	ChainIterator end() { return ChainIterator(NULL); } // ������ ����� link�� ����Ű�� iterator ����
	void CopytoArray(int *&arr, int&); // Chain�� �迭�� ����
	
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

void Chain::Insert_Tail(const int& item) { 
	if (first->link == NULL) { // ���� ����Ʈ�� ����
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
	if (first->link == NULL) { // ���� ����Ʈ�� ����
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
	tmp->link = NULL; // �ٷ� ������Ű�� tmp�ڿ� �����ִ� ���鵵 �� ������, before->link�� NULL�� ����Ű�Ե�
	delete tmp;
}

void Chain::Delete(Node*& x) {
	cout << "�� ��° ��带 ������ ���Դϱ�? : ";
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
	cout << "�� ��° ��� ������ ������ ���Դϱ�? : ";
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
		cout << "�� ����Ʈ�Դϴ�" << endl;
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