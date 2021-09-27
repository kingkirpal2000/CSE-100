#include <iostream>
#include <queue>
#include <climits>
#include <iterator>
using namespace std;

struct Vertex {
    int id;
    int color;
    struct Vertex* parent;
    int d;
    int f;
    Vertex(int name) {
        id = name;
        color = INT_MIN;
        parent = NULL;
        d = INT_MIN;
        f = INT_MIN;
    }
};

struct compareF {
    bool operator()(Vertex* const& n1, Vertex* const& n2) {
        return n1->f < n2->f;
    }
};
struct compareF1 {
    bool operator()(Vertex* const& n1, Vertex* const& n2) {
        return n1->f > n2->f;
    }
};

void DFSVisit(struct Vertex* U, int u[], int v[], Vertex* gV[], int* time, int numE, int numV) {
    *time = *time + 1;
    U->d = *time;
    U->color = 1;
    for (int i = 0; i < numE; i++) {
        if (u[i] == U->id) {
            int findingV = v[i];
            int posV;
            for (posV = 0; posV < numV; posV++) {
                if (findingV == gV[posV]->id) break;

            }
            struct Vertex* V = gV[posV];
            if (V->color == 0) {
                V->parent = U;
                DFSVisit(V, u, v, gV, time, numE, numV);
            }
        }
    }
    U->color = 2;
    *time = *time + 1;
    U->f = *time;
}


void DFS(int u[], int v[], Vertex* gV[], int numE, int numV) {
    for (int i = 0; i < numV; i++) {
        gV[i]->color = 0;
    }
    int T = 0;
    int* time;
    time = &T;
    for (int i = 0; i < numV; i++) {
        if (gV[i]->color == 0) {
            DFSVisit(gV[i], u, v, gV, time, numE, numV);
        }
    }

}

bool isThere(int id, Vertex* gV[], int numV) {
    for (int i = 0; i < numV; i++) {

        if (gV[i]->id == id) return true;
    }
    return false;
}

int main(int argc, char** argv) {
    int numV, numE;
    cin >> numV;
    cin >> numE;

    // int u[numE];
    // int v[numE];
    int* u = (int*)malloc(numE * sizeof(int));
    int* v = (int*)malloc(numE * sizeof(int));

    for (int i = 0; i < numE; i++) {
        cin >> u[i];
        cin >> v[i];
    }

    Vertex* gV[numV];
    for (int i = 0; i < numV; i++) {
        struct Vertex* newV = new Vertex(INT_MIN);
        gV[i] = newV;
    }
    int myIT = 0;
    for (int i = 0; i < numE; i++) {
        if (isThere(u[i], gV, numV) == false) {
            struct Vertex* newV = new Vertex(u[i]);
            gV[myIT] = newV;
            myIT++;
        }
    }
    for (int i = 0; i < numE; i++) {
        if (isThere(v[i], gV, numV) == false) {
            struct Vertex* newV = new Vertex(v[i]);
            gV[myIT] = newV;
            myIT++;
        }
    }

    DFS(u, v, gV, numE, numV);


    priority_queue<Vertex*, vector<Vertex*>, compareF> Q;
    for (int i = 0; i < numV; i++) {
        Q.push(gV[i]);
    }

    int it = 0;
    Vertex* TgV[numV];
    while (!Q.empty()) {
        Vertex* p = Q.top();
        Q.pop();
        TgV[it++] = p;
    }
    DFS(v, u, TgV, numE, numV);
    priority_queue<Vertex*, vector<Vertex*>, compareF1> Q1;
    for (int i = 0; i < numV; i++) {
        Q1.push(TgV[i]);
    }
    Vertex* answer[numV];
    it = 0;
    while (!Q1.empty()) {
        Vertex* p = Q1.top();
        Q1.pop();
        answer[it] = p;
        it++;
    }
    // int answerPrint[numV];
    int* answerPrint = (int*)malloc(numV * sizeof(int));
    for (int i = 0; i < numV; i++) {
        answerPrint[i] = INT_MIN;
    }

    int i = 0;
    int smallest = answer[i]->id;
    int occ = 1;
    while (i < numV) {
        if (answer[i + 1]->f == answer[i]->f + 1) {
            if (smallest > answer[i + 1]->id) {
                smallest = answer[i + 1]->id;
            }
            occ++;
            i++;
        }
        else {
            int j = i;
            while (occ > 0) {
                answerPrint[answer[j]->id] = smallest;
                j--;
                occ--;
            }
            i++;
            occ = 1;
            smallest = answer[i]->id;
        }

    }


    for (int i = 0; i < numV; i++) {
        cout << answerPrint[i] << endl;
    }

}

// colors will be 0 white 1 grey 2 black