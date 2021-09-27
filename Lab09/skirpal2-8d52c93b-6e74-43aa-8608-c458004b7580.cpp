#include <iostream>
#include <queue>
using namespace std;

struct Node {
  char letter;
  int freq;
  struct Node* left;
  struct Node* right;
  Node() { // constructor used from https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
    letter = '\0';
    freq = 0;
    left = NULL;
    right = NULL;
  }
};

struct compareFreq {  // Got help from https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
  bool operator()(Node* const& n1, Node* const& n2) {
    return n1->freq > n2->freq;
  }
};

void printOutput(struct Node* root, string code, string codeMap[]) {
  if (root->left == NULL || root->right == NULL) {
    switch (root->letter) {
    case 'A':
      codeMap[0] = code;
      break;
    case 'B':
      codeMap[1] = code;
      break;
    case 'C':
      codeMap[2] = code;
      break;
    case 'D':
      codeMap[3] = code;
      break;
    case 'E':
      codeMap[4] = code;
      break;
    case 'F':
      codeMap[5] = code;
      break;
    }
    return;
  }
  string leftCode = code + "0";
  string rightCode = code + "1";
  printOutput(root->left, leftCode, codeMap);
  printOutput(root->right, rightCode, codeMap);
}

void Huffman(Node* C[]) {
  int n = 6;
  priority_queue<Node*, vector<Node*>, compareFreq> Q;

  for (int i = 0; i < 6; i++) {
    Q.push(C[i]);
  }

  for (int i = 0; i < n - 1; i++) {
    struct Node* z = new Node();
    z->left = Q.top();
    Q.pop();
    z->right = Q.top();
    Q.pop();
    z->freq = z->left->freq + z->right->freq;
    Q.push(z);
  }
  string codeMap[6];
  for (int i = 0; i < 6; i++) {
    codeMap[i] = "";
  }

  printOutput(Q.top(), "", codeMap);
  char setC[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
  for (int i = 0; i < 6; i++) {
    cout << setC[i] << ":" << codeMap[i] << endl;
  }
}

int main(int argc, char** argv) {
  char setC[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
  Node* C[6];
  for (int i = 0; i < 6; i++) {
    int inputFreq;
    cin >> inputFreq;
    struct Node* newC = new Node();
    newC->letter = setC[i];
    newC->freq = inputFreq;
    C[i] = newC;
  }

  Huffman(C);
}