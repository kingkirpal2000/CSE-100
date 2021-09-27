#include <iostream>
#include <climits>
#include <queue>
using namespace std;

struct Vertex {
  int id;
  int d;
  struct Vertex* parent;
  Vertex(int name) {
    id = name;
    d = INT_MAX;
    parent = NULL;
  }
};

struct compareID {
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

void Relax(int currentD[], int newCurrD[], int posU, int posV, int w, Vertex* v, Vertex* u) {
  if (currentD[posU] != INT_MAX) {
    if (newCurrD[posV] > currentD[posU] + w) {
      newCurrD[posV] = currentD[posU] + w;
      v->parent = u;
    }
  }
}

void Init_Single_Source(Vertex* s) {
  s->d = 0;
}

bool bellman_ford(Vertex* s, int u[], int v[], int w[], int numV, int numE, Vertex* gV[]) {
  Init_Single_Source(s);
  for (int i = 1; i <= numV - 1; i++) {
    int* currentD = (int*)malloc(numV * sizeof(int));
    int* newCurrD = (int*)malloc(numV * sizeof(int));
    for (int k = 0; k < numV; k++) {
      currentD[k] = gV[k]->d;
      newCurrD[k] = gV[k]->d;
    }
    for (int j = 0; j < numE; j++) {
      int findingU = u[j];
      int posU = 0;
      while (gV[posU]->id != findingU) {
        posU++;
      }
      Vertex* u = gV[posU];
      int findingV = v[j];
      int posV = 0;
      while (gV[posV]->id != findingV) {
        posV++;
      }
      Vertex* v = gV[posV];
      Relax(currentD, newCurrD, posU, posV, w[j], v, u);
    }
    for (int k = 0; k < numV; k++) {
      gV[k]->d = newCurrD[k];
    }
  }
  for (int i = 0; i < numE; i++) {
    int findingU = u[i];
    int posU = 0;
    while (gV[posU]->id != findingU) {
      posU++;
    }
    Vertex* u = gV[posU];
    int findingV = v[i];
    int posV = 0;
    while (gV[posV]->id != findingV) {
      posV++;
    }
    Vertex* v = gV[posV];

    if (u->d != INT_MAX && v->d > (u->d + w[i])) return false;
  }
  return true;
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
    struct Vertex* newV = new Vertex(INT_MIN);
    gV[i] = newV;
  }
  for (int i = 0; i < numE; i++) {
    if (!isThere(u[i], gV, numV)) {
      struct Vertex* newV = new Vertex(u[i]);
      gV[gVit] = newV;
      gVit++;
    }
    if (!isThere(v[i], gV, numV)) {
      struct Vertex* newV = new Vertex(v[i]);
      gV[gVit] = newV;
      gVit++;
    }
  }

  int findingZ = 0;
  while (gV[findingZ]->id != 0) {
    findingZ++;
  }
  Vertex* s = gV[findingZ];
  bool cycle = bellman_ford(s, u, v, w, numV, numE, gV);

  if (cycle == true) {
    priority_queue<Vertex*, vector<Vertex*>, compareID> Q;
    for (int i = 0; i < numV; i++) Q.push(gV[i]);
    cout << "TRUE" << endl;
    while (!Q.empty()) {
      Vertex* bf = Q.top();
      Q.pop();
      if (bf->d != INT_MAX) cout << bf->d << endl;
      else cout << "INFINITY" << endl;
    }
  }
  else {
    cout << "FALSE" << endl;
  }


}