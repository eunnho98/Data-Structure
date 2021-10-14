#include <iostream>
#include <vector>
using namespace std;
struct Node {
	Node* link;
	int data;
	Node(int data, Node* next = NULL) : data(data), link(next) {}
};

class Graph { // ���� ��� or ���� ����Ʈ
	int n; // ������ ��
	int e; // ������ ��
public:
	Graph() { n = 0; e = 0; }
	virtual ~Graph() {}
	bool IsEmpty() const { return n == 0; }
	int NumberofV() const { return n; } // ������ ��
	int NumberofE() const { return e; } // ������ ��
	void addV() { n++; }
	void addE() { e++; }
	void subV() { n--; }
	void subE() { e--; }
	virtual int Degree(int u) const = 0; // ���� u�� ������ ������ �� ��ȯ
	virtual bool ExistsE(int u, int v) const = 0; // �׷����� ����(u, v)�� ������ true��ȯ
	virtual void InsertV(int v) = 0; // ���� ����, ������ ������ ����
	virtual void InsertE(int u, int v) = 0; // ���� (u, v) ����
	virtual void DeleteV(int v) = 0; // ���� v�� ���� ������ ��� ����
	virtual void DeleteE(int u, int v) = 0; // �׷����� ���� (u, v) ����
	virtual void Print() = 0;
};

class Mat : public Graph {
private:
	// name�� idx = mat�� idx
	vector<vector<int>> mat; // 2���� �迭
	vector<int> name; // ������ �̸� ����
	int size;
public:
	Mat() : Graph() {
		size = 0;
	}
	virtual int Degree(int u) const {
		int sum = 0;
		for (int i = 0; i < mat[u].size(); i++) {
			sum += mat[u][i];
		}
		return sum;
	}
	virtual bool ExistsE(int u, int v) const { return mat[u][v] == 1; }

	virtual void InsertV(int v) {
		addV();
		name.push_back(v);
		vector<int> temp(++size);
		mat.push_back(temp);
		for (int i = 0; i < mat.size(); i++) { // ������ ���͵鵵 size��ŭ ���� �߰�
			while (mat[i].size() != size) {
				mat[i].push_back(0);
			}
		}
	}

	virtual void InsertE(int u, int v) {
		int uidx = 0;
		int vidx = 0;
		// �������� idx ã��
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				uidx = i;
				break;
			}
		}
		for (int i = 0; i < name.size(); i++) {
			if (v == name[i]) {
				vidx = i;
				break;
			}
		}
		mat[vidx][uidx] = 1;
		mat[uidx][vidx] = 1;

		addE(); addE();
	}
	virtual void DeleteV(int v) {
		size--;
		subV();
		int idx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == v) {
				idx = i;
				break;
			}
		}
		name.erase(name.begin() + idx);

		for (int i = 0; i < mat[idx].size(); i++) { // ���� 0���� �ʱ�ȭ �� ����
			mat[idx][i] = 0;
			mat[i][idx] = 0;
		}

		mat.erase(mat.begin() + idx); // �� ����
		for (int i = 0; i < mat.size(); i++) {
			mat[i].erase(mat[i].begin() + idx); // �� ����
		}
	}
	virtual void DeleteE(int u, int v) {
		int uidx = 0;
		int vidx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				uidx = i;
				break;
			}
		}
		for (int i = 0; i < name.size(); i++) {
			if (v == name[i]) {
				vidx = i;
				break;
			}
		}
		mat[vidx][uidx] = 0;
		mat[uidx][vidx] = 0;

		addE(); addE();
		subE(); subE();
	}
	virtual void Print() {
		cout << "  ";
		for (int i = 0; i < name.size(); i++) {
			cout << name[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < name.size(); i++) {
			cout << name[i] << " ";
			for (int j = 0; j < mat[i].size(); j++) {
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
	}
};

class adjList : public Graph {
	vector<Node*> adjlist;
	vector<int> name;

public :
	adjList() : Graph() {}
	virtual int Degree(int u) const {
		int idx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				idx = i;
				break;
			}
		}
		int sum = 0;
		Node* tmp = adjlist[idx];
		while (tmp->link != NULL) {
			tmp = tmp->link;
			sum++;
		}
		return sum;
	}

	virtual bool ExistsE(int u, int v) const {
		int idx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				idx = i;
				break;
			}
		}
		Node* tmp = adjlist[idx];
		while (tmp != NULL) {
			if (tmp->data == v) return true;
			else tmp = tmp->link;
		}
		return false;
	}
	virtual void InsertV(int v) {
		name.push_back(v);
		adjlist.push_back(new Node(v));
		addV();
	}

	virtual void InsertE(int u, int v) {
		int uidx = 0; int vidx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				uidx = i;
				break;
			}
		}
		for (int i = 0; i < name.size(); i++) {
			if (v == name[i]) {
				vidx = i;
				break;
			}
		}
		
		Node* utmp = adjlist[uidx];
		Node* vtmp = adjlist[vidx];

		while (utmp->link != NULL) {
			utmp = utmp->link;
		}
		utmp->link = new Node(v); // ���� ����

		while (vtmp->link != NULL) {
			vtmp = vtmp->link;
		}
		vtmp->link = new Node(u);
		addE(); addE();
	}

	virtual void DeleteV(int v) {
		int idx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (v == name[i]) {
				idx = i;
				break;
			}
		}
		name.erase(name.begin() + idx); // ���� ��Ͽ��� ����
		adjlist.erase(adjlist.begin() + idx); // v ����
		for (int i = 0; i < adjlist.size(); i++) { // v�� �������ִ� �������� v ����
			Node* pre = adjlist[i];
			while (pre->link->data != v) {
				pre = pre->link;
			}
			Node* del = pre->link;
			pre->link = del->link;
			del->link = NULL;
			delete del;
		}
		subV();
	}

	virtual void DeleteE(int u, int v) {
		int uidx = 0; int vidx = 0;
		for (int i = 0; i < name.size(); i++) {
			if (u == name[i]) {
				uidx = i;
				break;
			}
		}
		for (int i = 0; i < name.size(); i++) {
			if (v == name[i]) {
				vidx = i;
				break;
			}
		}
		Node* utmp = adjlist[uidx];
		while (utmp->link->data != v) {
			utmp = utmp->link;
		}
		Node* udel = utmp->link;
		utmp->link = udel->link;
		udel->link = NULL;
		delete udel;

		Node* vtmp = adjlist[vidx];
		while (vtmp->link->data != u) {
			vtmp = vtmp->link;
		}
		Node* vdel = vtmp->link;
		vtmp->link = vdel->link;
		vdel->link = NULL;
		delete vdel;

		subE(); subE();

	}
	virtual void Print() {
		for (int i = 0; i < adjlist.size(); i++) {
			Node* tmp = adjlist[i];
			while (tmp != NULL) {
				cout << tmp->data << " --> ";
				tmp = tmp->link;
			}
			cout << "NULL" << endl;
		}
	}
	~adjList() {
		for (int i = 0; i < adjlist.size(); i++) {
			Node* del = adjlist[i];
			while (del != NULL) {
				Node* tmp = del;
				del = del->link;
				delete tmp;
			}
		}
	}
};
int main() {
	Graph* g = new adjList();
	g->InsertV(2);
	g->InsertV(4);
	g->InsertV(5);
	g->InsertV(6);

	g->InsertE(2, 4);
	g->InsertE(4, 5);
	g->InsertE(2, 6);
	g->InsertE(5, 6);
	g->Print();

	g->DeleteE(5, 6);
	g->Print();
	return 0;
}