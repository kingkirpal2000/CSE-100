#include <iostream>
using namespace std;

int main(int argc, char **argv){
	int AL; //Array length variable
	cin >> AL;

	int* arr;	
	arr = new int[AL];
	for(int i = 0; i < AL; i++){
		cin >> arr[i];
	}

	for(int i = 1; i < AL; i++){
		int key = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > key){
		        arr[j+1] = arr[j];
			arr[j] = key;
			j--;
		}
		for (int k = 0; k <= i; k++){
			cout << arr[k] << ";";
		}
		cout << endl;
	}
}

// { 3, 4, 5, 1, 2 }
//   j     i
