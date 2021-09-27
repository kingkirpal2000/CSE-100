#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

int hashFunction(int k, int m){
    return (k % m);
}

void outputHashTable(list<int>* T, int m){
    for(int i = 0; i < m; i++){
        cout << i << ":";
        list<int>::iterator it;
        for(it = T[i].begin(); it != T[i].end(); ++it){
            cout << *it << "->";
        }
        cout << ";" << endl;
    }
}


void searchHashTable(list<int>* T, int m, int k){
    list<int>::iterator it;
    int searchM = hashFunction(k, m);
    int i = 0;
    for(it = T[searchM].begin(); it != T[searchM].end(); ++it){
        if(*it == k){
            cout << k << ":FOUND_AT" << searchM << "," << i << ";" << endl;
            return;
        }
        i++;
    }
    cout << k << ":NOT_FOUND;" << endl;
}

void deleteHashTable(list<int>* T, int m, int x){
    list<int>::iterator it;
    int searchM = hashFunction(x, m);
    int i = 0;
    for(it = T[searchM].begin(); it != T[searchM].end(); ++it){
        if(*it == x){
            T[searchM].erase(it);
            cout << x << ":DELETED;" << endl;
            return;
        }
        i++;
    }
    cout << x << ":DELETE_FAILED;" << endl;
}

void insertHashTable(list<int>* T, int m, int x){
    T[hashFunction(x, m)].push_front(x);
}

int main(int argc, char** argv){
	int m;
	cin >> m;

	list<int> T[m];
	
    char command;
   
    
    while(true){
        cin >> command;
        if (command == 'i'){
            int key;
            cin >> key;
            insertHashTable(T, m, key);
        } else if (command == 's'){
            int key;
            cin >> key;
            searchHashTable(T, m, key);
        } else if (command == 'd'){
            int key;
            cin >> key;
            deleteHashTable(T, m, key);
        } else if (command == 'o'){
            outputHashTable(T, m);
        } else if (command == 'e'){
            return 0;
        } else {
            cout << "Input invalid" << endl;
        }
    }
}
