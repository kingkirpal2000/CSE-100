#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > CountingSort(vector< vector<int> > A, int k, int d){
    vector<int> C;
    for(int i = 0; i < d; i++){
        C.push_back(0);
    }
    vector<vector<int> > B;
    for(int i = 0; i < A.size(); i++){
        vector<int> temp(d);
        B.push_back(temp);
    }
    vector<int> DP;
    for(int i = 0; i < A.size(); i++){
        DP.push_back(0);
    }

    for(int i = 0; i < A.size(); i++){
        DP[i] = A[i][k];
    }
    for(int j = 0; j < DP.size(); j++){
        C[DP[j]] += 1;
    }
    for(int i = 1; i < d; i++){
        C[i] += C[i-1];
    }
    for(int j = A.size()-1; j>=0; j--) {
        B[C[DP[j]]-1] = A[j];
        C[DP[j]] += -1;
    }
    
    return B;

}

void RadixSort(vector < vector<int> > &nVector, int d){
    for(int i = d; i > 0; i--){
        nVector = CountingSort(nVector, i-1, d);
    }
    for(int i = 0; i < nVector.size(); i++){
        for(int j = 0; j < nVector[i].size(); j++){
            cout << nVector[i][j] << ";";
        }
        cout << endl;
    }

}
int main(int argc, char** argv){
    int n;
    cin >> n;
    
    vector< vector<int> > nVector;

    for(int i = 0; i < n; i++){
        vector<int> temp;
        for(int j = 0; j < 10; j++){
            int inputValue;
            cin >> inputValue;
            temp.push_back(inputValue);
        }
        nVector.push_back(temp);
    }
    RadixSort(nVector, 10);
    
}
