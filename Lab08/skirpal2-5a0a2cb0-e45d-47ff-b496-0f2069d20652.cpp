//
//  skirpal2.cpp
//  
//
//  Created by Sabir Kirpal on 3/17/21.
//
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;


void PrintOptimalParens(int** s, int i, int j){
    if(i == j){
        cout << "A" << i-1;
        return;
    } else {
        cout << "(";
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j]+1, j);
        cout << ")";
    }
}

void MatrixChainOrder(int *p, int n){
    int m[n+1][n+1];
    int **s;
    s = (int**) malloc((n+1)*sizeof(int*)); //new int *[n];
    for(int i = 0; i <= n-1; i++){
       s[i] = (int*) malloc((n+1)*sizeof(int));//new int[n-1];
    }
    for(int i = 0; i <= n; i++){
        m[i][i] = 0;
    }
    for(int l = 2; l <= n; l++){
        for(int i = 1; i <= (n-l+1); i++){
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j-1; k++){
                int q = m[i][k]+m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    cout << m[1][n] << endl;
    PrintOptimalParens(s, 1, n);
}

int main(int argc, char** argv){
    int n;
    cin >> n;
    
    int dim[n];
    for(int i = 0; i <= n; i++){
        cin >> dim[i];
    }
    MatrixChainOrder(dim, n);
    cout << endl;
}



