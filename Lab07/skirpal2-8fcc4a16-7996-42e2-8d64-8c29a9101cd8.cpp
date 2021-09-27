//
//  skirpal2.cpp
//  
//
//  Created by Sabir Kirpal on 3/11/21.
//

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

vector< vector<int> > EBUCR(int *p, int n){
    vector < vector<int> > answer;
    vector<int> r(n+1, 0);
    vector<int> s(n+1, 0);
    r[0] = 0;
    int q;
    for(int j = 1; j <= n; j++){
        q = INT_MIN;
        for(int i = 0; i < j; i++){
            if( q < (p[i] + r[j-i-1])){
                q = p[i] + r[j-i-1];
                s[j] = i+1;
            }
        }
        r[j] = q;
    }
    cout << q << endl;
    answer.push_back(r);
    answer.push_back(s);
    
    return answer;
}

void PCRS(int *p, int n){
    vector< vector<int> > answer = EBUCR(p, n);
    
    while (n > 0){
        cout << answer[1][n] << " ";
        n = n - answer[1][n];
    }
    cout << "-1" << endl;
}

int main(int argc, char** argv){
    int n;
    cin >> n;

    int p[n];
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }
    PCRS(p, n);

}
