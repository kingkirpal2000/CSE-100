#include <iostream>
#include <climits>
#include <queue>
using namespace std;

struct Vertex {
  int id;
  int key;
  int extracted;
  struct Vertex* parent;
  int adjSize;
  int* wUV;
  Vertex* adjList[100];

  Vertex(int name, int numE) {
    id = name;
    key = INT_MAX;
    parent = NULL;
    extracted = 0;
    // adjList = (Vertex*)malloc(numE * sizeof(Vertex*));
    wUV = (int*)malloc(numE * sizeof(int));
    adjSize = 0;
  }

  void fillADJ(int numE, int numV, int u[], int v[], int w[], Vertex* gV[]) {
    for (int i = 0; i < numE; i++) {
      if (u[i] == id) {
        int findingV = v[i];
        int posV;
        for (posV = 0; posV < numV; posV++) {
          if (findingV == gV[posV]->id) {
            adjList[adjSize] = gV[posV];
            wUV[adjSize] = w[i];
            adjSize++;
          }
        }
      }
    }
    for (int i = 0; i < numE; i++) {
      if (v[i] == id) {
        int posU = 0;
        while (gV[posU]->id != u[i]) {
          posU++;
        }
        adjList[adjSize] = gV[posU];
        wUV[adjSize] = w[i];
        adjSize++;
      }
    }
  }
};

struct compareK {
  bool operator()(Vertex* n1, Vertex* n2) {
    return n1->id > n2->id;
  }
};

bool isThere(int id, Vertex* gV[], int numV) {
  for (int i = 0; i < numV; i++) {

    if (gV[i]->id == id) return true;
  }
  return false;
}
bool QEmpty(Vertex* gV[], int numV) {
  for (int i = 0; i < numV; i++) {
    if (gV[i]->extracted == 0) return false;
  }
  return true;
}

void MSTPrim(Vertex* gV[], int numV) {
  Vertex* mstAnswer[numV];
  int ait = 0;
  Vertex* root = gV[0];
  root->key = 0;
  while (!QEmpty(gV, numV)) {

    Vertex* min = new Vertex(INT_MAX, 0);
    for (int i = 0; i < numV; i++) {
      if (gV[i]->extracted == 0) {
        if (min->key > gV[i]->key) {
          min = gV[i];
        }
      }
    }
    min->extracted = 1;

    for (int i = 0; i < min->adjSize; i++) {
      Vertex* v = min->adjList[i];
      if (v->extracted == 0 && min->wUV[i] < v->key) {
        v->parent = min;
        v->key = min->wUV[i];
      }
    }
  }

}

int main(int argc, char** argv) {
  int numV, numE;
  cin >> numV;
  cin >> numE;

  int* u = (int*)malloc(numE * sizeof(int));
  int* v = (int*)malloc(numE * sizeof(int));
  int* w = (int*)malloc(numE * sizeof(int));

  for (int i = 0; i < numE; i++) {
    cin >> u[i];
    cin >> v[i];
    cin >> w[i];
  }
  Vertex* gV[numV];
  int gVit = 0;
  for (int i = 0; i < numV; i++) {
    struct Vertex* newV = new Vertex(INT_MIN, numE);
    gV[i] = newV;
  }
  for (int i = 0; i < numE; i++) {
    if (!isThere(u[i], gV, numV)) {
      struct Vertex* newV = new Vertex(u[i], numE);
      gV[gVit] = newV;
      gVit++;
    }
    if (!isThere(v[i], gV, numV)) {
      struct Vertex* newV = new Vertex(v[i], numE);
      gV[gVit] = newV;
      gVit++;
    }
  }

  for (int i = 0; i < numV; i++) {
    gV[i]->fillADJ(numE, numV, u, v, w, gV);
  }

  MSTPrim(gV, numV);

  priority_queue<Vertex*, vector<Vertex*>, compareK> Q;
  for (int i = 0; i < numV; i++) {
    Q.push(gV[i]);
  }
  Q.pop();
  while (!Q.empty()) {
    Vertex* p = Q.top();
    Q.pop();
    cout << p->parent->id << endl;
  }
}

// Vertex 0 is root r

