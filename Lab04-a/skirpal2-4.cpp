#include <iostream>
using namespace std;

void MaxHeapify(int* arr, int size, int i){
	int largest;
	int l = (2*(i+1))-1;
	int r = ((2*(i+1))+1)-1;
	
	if(l < size && arr[l] > arr[i]){
	       largest = l;
	}
	else{
		largest = i;
	}

	if(r < size && arr[r] > arr[largest]){
		largest = r;
	}
	
	if(largest != i){
		int key = arr[i];
		arr[i] = arr[largest];
		arr[largest] = key;
		MaxHeapify(arr, size, largest);
	}
}

void BuildMaxHeap(int* arr, int size){
	for(int i = (size-1)/2; i >= 0; i--){
		MaxHeapify(arr, size, i);
	}
}

void HeapSort(int* arr, int size){
	BuildMaxHeap(arr, size);
	for(int i = size-1; i >= 1; i--){
		int key = arr[0];
		arr[0] = arr[i];
		arr[i] = key;
		size--;
		MaxHeapify(arr, size, 0);
	}
}
int main(int argc, char **argv){
	int n;
	cin >> n;
	int arr[n];

	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	
	HeapSort(arr, n);

	for(int i = 0; i < n; i++){
		cout << arr[i] << ";";
	}
}
