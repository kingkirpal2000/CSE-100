#include <iostream>
#include <stdlib.h>
using namespace std;

int Partition(int* arr,int p,int r){
	int x = arr[r];
	int i = p-1;
	for(int j = p; j <= r-1; j++){
		if(arr[j] <= x){
			i++;
			int key = arr[i];
			arr[i] = arr[j];
			arr[j] = key;
		}
	}
	int key = arr[i+1];
	arr[i+1] = arr[r];
	arr[r] = key;
	return i+1;
}

int RandomizedPartition(int* arr, int p, int r){
	int i = p + (rand()%(r-p+1));
	int key = arr[i];
	arr[i] = arr[r];
	arr[r] = key;
	return Partition(arr, p, r);
}

void RandomizedQuicksort(int* arr, int p, int r){
	if(p < r){
		int q = RandomizedPartition(arr, p, r);
		RandomizedQuicksort(arr, p, q-1);
		RandomizedQuicksort(arr, q+1, r);
	}
}

int main(int argc, char** argv){
	int n;
	cin >> n;
	
	int arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	RandomizedQuicksort(arr, 0, n-1);
	
	for(int i = 0; i < n; i++){
		cout << arr[i] << ";";
	}
}
