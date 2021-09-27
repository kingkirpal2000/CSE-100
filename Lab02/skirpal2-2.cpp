#include <iostream>
using namespace std;

void Merge(int arr[], int l, int m, int r){
	int sizeLeft, sizeRight;  // Because we need to keep track of the left and right array independently 
							  // while moving elements around in arr, it is best to copy L and R to seperate arr
	sizeLeft = m-l+1; 
	sizeRight = r-m;

	int L[sizeLeft], R[sizeRight];
	int Lstart = l;
	int Rstart = m+1;
	for(int i = 0; i < sizeLeft; i++){  // copied appropriate elements to their respective arrays
		L[i] = arr[i + Lstart];
	}
	for(int i = 0; i < sizeRight; i++){
		R[i] = arr[i + Rstart];
	}

	int LPointer = 0; // This will keep track of elements in right pointer and left pointer respectively 
	int RPointer = 0;
	int i = l;
		
	for(;i <= (r+1); i++){ // this loop will exit upon reaching the length of either L or R
		if(LPointer < sizeLeft && RPointer < sizeRight){
			if(L[LPointer] <= R[RPointer]){
				arr[i] = L[LPointer++];
			} else {
				arr[i] = R[RPointer++];
			}
		} else {
			break;
		}
	}

	while(LPointer < sizeLeft){  // created two while loops to finish copying the elements that broke from the array before finishing
		arr[i] = L[LPointer];
		LPointer++;
		i++;
	}

	while(RPointer < sizeRight){
		arr[i] = R[RPointer];
		RPointer++;
		i++;

	}
	
	// when we reach this Merge function with L and R of size one it will start working its way 
	// back upwards of the recursive tree
	// as it goes up the tree, it will be sorted and merged at each level that is why we can copy the left over
	// elements of L and R without worrying about them being sorted or not
	// in other words they would already be sorted
}

void MergeSort(int A[], int firstIndex, int lastIndex){
	if(firstIndex >= lastIndex){ //this would mean there is one or less elements left
		return;
	}
	int m = firstIndex + (lastIndex - firstIndex) / 2; // middle of the array is starting point and the distance between the ending point from the start point divided by 2
    MergeSort(A, firstIndex, m); // Recursive call for left side of the array
	MergeSort(A, m+1, lastIndex); // Recursive call to the right side of the array 
	Merge(A, firstIndex, m, lastIndex); // Merge back to one array at ever level of recursion tree	
}

int main(int argc, char **argv){
	int n;
	cin >> n;

	int arr[n];

	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	MergeSort(arr, 0, n-1); //initial call to mergesort

	for(int i = 0; i < n; i++){
		cout << arr[i] << ";";
	}
	
}


/*
 * Merge(L, R)
 * 	m <- length(L) + length(R)
 * 	s <- int array of size m
 * 	i <- 1, j <- 1;
 * 	for k = 1 -> m do:
 * 		if L(i) < R(i) then 
 * 			s(k) <- L(i)
 * 			i = i + 1
 * 		else 
 * 			s(k) <- R(i)
 * 			j = j + 1
 * 	return s
 */

/*
 * MergeSort(A[])
 * 	n <- length(A)
 * 	if n <= 1 then 
 * 		return A
 * 	L <- MergeSort(A[1:n/2])
 * 	R <- MergeSort(A[n+1:n])
 * 	return Merge(L,R)
 */


