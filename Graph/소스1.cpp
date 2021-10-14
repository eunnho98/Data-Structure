#include <iostream>
#include <vector>
using namespace std;
struct Node {
	Node* link;
	int data;
	Node(int data, Node* next = NULL) : data(data), link(next) {}
};

class Graph { // 인접 행렬 or 인접 리스트
	int n; // 정점의 수
	int e; // 간선의 수
public:
	Graph() { n = 0; e = 0; }
	virtual ~Graph() {}
	bool IsEmpty() const { return n == 0; }
	int NumberofV() const { return n; } // 정점의 수
	int NumberofE() const { return e; } // 간선의 수
	void addV() { n++; }
	void addE() { e++; }
	void subV() { n--; }
	void subE() { e--; }
	virtual int Degree(int u) const = 0; // 정점 u에 인접한 간선의 수 반환
	virtual bool ExistsE(int u, int v) const = 0; // 그래프에 간선(u, v)가 있으면 true반환
	virtual void InsertV(int v) = 0; // 정점 삽입, 인접한 간선이 없음
	virtual void InsertE(int u, int v) = 0; // 간선 (u, v) 삽입
	virtual void DeleteV(int v) = 0; // 정점 v와 인접 간선들 모두 삭제
	virtual void DeleteE(int u, int v) = 0; // 그래프에 간선 (u, v) 삭제
	virtual void Print() = 0;
};

class Mat : public Graph {
private:
	// name의 idx = mat의 idx
	vector<vector<int>> mat; // 2차원 배열
	vector<int> name; // 정점의 이름 저장
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
		for (int i = 0; i < mat.size(); i++) { // 이전의 벡터들도 size만큼 길이 추가
			while (mat[i].size() != size) {
				mat[i].push_back(0);
			}
		}
	}

	virtual void InsertE(int u, int v) {
		int uidx = 0;
		int vidx = 0;
		// 정점들의 idx 찾기
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

		for (int i = 0; i < mat[idx].size(); i++) { // 먼저 0으로 초기화 후 제거
			mat[idx][i] = 0;
			mat[i][idx] = 0;
		}

		mat.erase(mat.begin() + idx); // 행 제거
		for (int i = 0; i < mat.size(); i++) {
			mat[i].erase(mat[i].begin() + idx); // 열 제거
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
		utmp->link = new Node(v); // 끝에 삽입

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
		name.erase(name.begin() + idx); // 정점 목록에서 삭제
		adjlist.erase(adjlist.begin() + idx); // v 삭제
		for (int i = 0; i < adjlist.size(); i++) { // v와 인접해있던 정점에서 v 삭제
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