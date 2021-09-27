#include <iostream>
#include <tuple>
#include <climits>
using namespace std;

tuple<int, int, int>findMaxCross(int *A, int low, int mid, int high){
	int maxLeft, maxRight;
	int leftSum = INT_MIN;
	int sum = 0; 

	for(int i = mid; i >= low; i--){
		sum += *(A+i);
		if(sum > leftSum){
			leftSum = sum;
			maxLeft = i;
		}
	}
	int rightSum = INT_MIN;
	sum = 0; 
	for(int j = mid+1; j <= high; j++){
		sum += *(A+j);
		if(sum > rightSum){
			rightSum = sum;
			maxRight = j;
		}
	}
	return tuple<int, int, int>{maxLeft, maxRight, (leftSum+rightSum)};	

}

tuple<int, int, int>findMaxSub(int *A,int low, int high){
	int mid;
	if(high == low) return {low, high, *(A+low)};
	else mid = (low+high)/2;
	int leftLow, leftHigh, leftSum;
	int rightLow, rightHigh, rightSum;
	int crossLow, crossHigh, crossSum;

	tie(leftLow, leftHigh, leftSum) = findMaxSub(A, low, mid);
	tie(rightLow, rightHigh, rightSum) = findMaxSub(A, mid+1, high);
	tie(crossLow, crossHigh, crossSum) = findMaxCross(A, low, mid, high);

	if(leftSum >= rightSum && leftSum >= crossSum) return tuple<int, int, int>{leftLow, leftHigh, leftSum};
	else if (rightSum >= leftSum && rightSum >= crossSum) return tuple<int, int, int>{rightLow, rightHigh, rightSum};
	else return tuple<int, int, int>{crossLow, crossHigh, crossSum};

}	

int main(int argc, char **argv){
	int size;
	cin >> size;

	int *arr;
	arr = (int*) malloc(size*sizeof(int));

	for(int i = 0; i < size; i++){
		cin >> *(arr+i);
	}
	int low, high, sum;	
	tie(low, high, sum) = findMaxSub(arr, 0, size-1);
	cout << sum;
}
