/*
==============================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. 5(a) : K-closest elements
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
=============================================
*/

#include<bits/stdc++.h>
using namespace std;

/*
===========================================================================
This is to give some basic information about the myself and the assignment
===========================================================================
*/
void info(){
	cout << "=============================================================\n";
	cout << "Hii !! This is Avik Samanta ...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the problem : \"K-CLOSEST ELEMENT\" !!\n";
	cout << "=============================================================\n\n";
}

/*
===========================
Explaination of my approach
===========================
*/
void approach(){
	cout << "Let's explain my approach towards the problem : \"K-Closest Element\" :-\n";
	cout << "-> First take the array and the key element, for which we have to find the K-Closest,\n";
	cout << "-> Then apply the Partition algorithm, using the key as the pivot element,\n";
	cout << "-> Now elements smaller than the key are to the left of the key element, and\n";
	cout << "-> The elements larger than (or equal to) the key, are to the right of the key,\n";
	cout << "-> Take the left partition elements and Construct a max-Heap,\n";
    cout << "-> Take the right partition elements and construct a min-Heap,\n";
	cout << "-> Now take the value of k from user, and then find the k-closest elements,\n";
	cout << "-> Each time compare the maximum element from the max-Heap [having the values smaller than key],\n";
	cout << "-> And minimmum element from the min-Heap [having the values equal to or larger than the key],\n";
	cout << "-> Then take the one with lesser absolute distance from the key, and extract that from the respective Heap,\n";
	cout << "-> Repeat this process until we get required k elements (closest from the key).\n\n";	
}

/*
=======================================================
Function to verify an element belong to an array or not
=======================================================
*/
int validKey(int list[], int size, int key){
	int i;
	for(i = 0; i < size; i ++)
	    if(key == list[i])
	        break;
	if(i == size) return -1;
	else return i;
}
/*
====================================================================================================
Given an array and two indices, this function will swap the values of those two indices in the array
====================================================================================================
*/
void swap(int array[], int pos1, int pos2){
	array[pos1] = array[pos1] + array[pos2];
	array[pos2] = array[pos1] - array[pos2];
	array[pos1] = array[pos1] - array[pos2];
}

/*
============================================================================
Function to reflect the partition algorithm (of famous Quick Sort Algorithm)
============================================================================
*/
int partition(int array[], int size, int position){
	if(position != size - 1) swap(array, position, size-1);
	int pivot = array[size - 1];
    int j, i;
    for(i = 0, j = 0; i < size; i ++){
        if(array[i] < pivot){
        	if(i != j){
        		swap(array, i, j);
        	}
        	j ++;
        }
    }
	if(j != size - 1) swap(array, j, size - 1);
    return j;
}

/*
=====================================================================================
Function to get the position of the left child (if left child was there) in the heap
=====================================================================================
*/
int leftChild(int index){
	return (2 * index + 1);
}

/*
======================================================================================
Function to get the position of the right child (if right child was there) in the heap
======================================================================================
*/
int rightChild(int index){
	return (2 * index + 2);
}

/*
===================================================================
Function to check if the left child exists or not for a given node
===================================================================
*/
bool ifLeft(int index, int size){
	if(leftChild(index) < size) return true;
	else return false;
}

/*
===================================================================
Function to check if the right child exists or not for a given node
===================================================================
*/
bool ifRight(int index, int size){
	if(rightChild(index) < size) return true;
	else return false;
}

/*
=======================================================================================
Function to ensure / modify the current subtree to follow the min-Heap property
-> using the child subtree's which are already following the min-Heap properties
-> compare if the node, its left child and right child, and find the minimum among them
-> Then if its not the current node, swap the value with the current node
-> Then apply minHeapify recursively for the child with which we just swaped the values
=======================================================================================
*/
void minHeapify(int list[], int index, int size){
	int left = leftChild(index), right = rightChild(index);
	if(!ifLeft(index, size)) return;
	else if(!ifRight(index, size)){
		if(list[left] < list[index]){
			swap(list, index, left);
			minHeapify(list, left, size);
		}
	}
	else{
		if(list[left] < list[index] and list[left] <= list[right]){
			swap(list, left, index);
			minHeapify(list, left, size);
		}
		else if(list[right] < list[index] and list[right] < list[left]){
			swap(list, right, index);
			minHeapify(list, right, size);
		}
	}
}

/*
===========================================================
Function to convert an array of elements into a min-Heap
-> Apply minHeapify for each element from the last (bottom)
===========================================================
*/
void constructMinHeap(int list[], int size){
	for(int i = size - 1; i >= 0; i --){
		minHeapify(list, i, size);
	}
}

/*
=======================================================================================
Function to extract the minimum element from a max-Heap
-> This takes O(log N) time, where N = Number of elements
-> Swap the root element with the last element, and then apply minHeapify for the root
-> Then decrease the size of the heap by one (as if the element is removed / extracted)
=======================================================================================
*/
int extractMin(int list[], int &size){
	int min = list[0];
	swap(list, 0, size - 1);
	size --;
	minHeapify(list, 0, size);
	return min;
}

/*
=======================================================================================
Function to ensure / modify the current subtree to follow the max-Heap property
-> using the child subtree's which are already following the max-Heap properties
-> compare if the node, its left child and right child, and find the maximum among them
-> Then if its not the current node, swap the value with the current node
-> Then apply maxHeapify recursively for the child with which we just swaped the values
=======================================================================================
*/
void maxHeapify(int list[], int index, int size){
	int left = leftChild(index), right = rightChild(index);
	if(!ifLeft(index, size)) return;
	else if(!ifRight(index, size)){
		if(list[left] > list[index]){
			swap(list, index, left);
			maxHeapify(list, left, size);
		}
	}
	else{
		if(list[left] > list[index] and list[left] >= list[right]){
			swap(list, left, index);
			maxHeapify(list, left, size);
		}
		else if(list[right] > list[index] and list[right] > list[left]){
			swap(list, right, index);
			maxHeapify(list, right, size);
		}
	}
}

/*
===========================================================
Function to convert an array of elements into a max-Heap
-> Apply maxHeapify for each element from the last (bottom)
===========================================================
*/
void constructMaxHeap(int list[], int size){
	for(int i = size - 1; i >= 0; i --){
		maxHeapify(list, i, size);
	}
}

/*
=======================================================================================
Function to extract the maximum element from a max-Heap
-> This takes O(log N) time, where N = Number of elements
-> Swap the root element with the last element, and then apply maxHeapify for the root
-> Then decrease the size of the heap by one (as if the element is removed / extracted)
=======================================================================================
*/
int extractMax(int list[], int &size){
	int max = list[0];
	swap(list, 0, size - 1);
	size --;
	maxHeapify(list, 0, size);
	return max;
}

/*
===============
driver function
===============
*/
int main(){
    
    /*
    =============================================================================
    This is the some pre-processing. Giving some info and explaining the approach
    ============================================================================= 
    */
    info();
    approach();
    
    /*
    =========================================================================================
    This section is for the user input for information of the array we are going to work with 
    =========================================================================================
    */
	int n;
	while(true){
		cout << "Enter the size of the array : ";
		cin >> n;
		if(n <= 0) cout << "Invalid entry! Try again ...\n";
		else break;
	}
	int array[n];
	cout << "Enter the elements of the array :-\n";
	for(int i = 0; i < n; i ++) cin >> array[i];
    
    /*
    =========================
    Input for our key element
    =========================
    */
    int key, position;
    while(true){
	    cout << "\nEnter the key element, x = ";
	    cin >> key;
	    if((position = validKey(array, n, key)) == -1) 
		    cout << "Key is not present in the list! Enter again ...\n"; 
		else break;  
	}
    
    /*
    ========================================================================================
    Applying the partition algorithm, to seperate the values larger and smaller than the key
    ========================================================================================
    */
    cout << "\nthe current position of the key in the array : " << position << endl;
	position = partition(array, n, position);
	cout << "The array after applying Partition Algoritm :-\n";
	for(int i = 0; i < n; i ++) cout << array[i] << " "; cout << endl;
	cout << "The new position of the key in the array : " << position << endl << endl;
    
    /*
    ==========================================================
    Now using the smaller values than the key, make a Max-Heap
    and using the larger values than the key, make a Max-Heap
    ==========================================================
    */
    int maxHeapSize = position, minHeapSize = n - position - 1;
	int maxHeap[maxHeapSize], minHeap[minHeapSize];
    for(int i = 0; i < maxHeapSize; i ++) 
    	maxHeap[i] = array[i];
    for(int i = 0; i < minHeapSize; i ++)
    	minHeap[i] = array[position + i + 1];
    cout << "The Max-Heap constructed using the left partition :-\n";
    constructMaxHeap(maxHeap, maxHeapSize);
    for(int i = 0; i < maxHeapSize; i ++) cout << maxHeap[i] << " "; cout << endl << endl;
    
    cout << "The Min-Heap constructed using the right partition :-\n";
    constructMinHeap(minHeap, minHeapSize);
    for(int i = 0; i < minHeapSize; i ++) cout << minHeap[i] << " "; cout << endl << endl;

    /*
    =================================================================================================
    User input for the value of k (in K-Closest element), and verifying is value of k is valid or not
    =================================================================================================
    */
    int k;
    while(true){
	    cout << "Enter the value of k (for K-closest) : ";
	    cin >> k;
	    if(k >= n or k <= 0) cout << "Invalid entry. Try again ...\n";
	    else break;
	}

    /*
    =============================================
    Finding the K-Closest element using the heaps
    =============================================
    */
    int KClosest[k];
    int count;
	for(count = 0; count < k and maxHeapSize and minHeapSize; count ++){
        if(abs(maxHeap[0] - key) < abs(minHeap[0] - key)){
            KClosest[count] = extractMax(maxHeap, maxHeapSize);
        }
        else if(abs(maxHeap[0] - key) >= abs(minHeap[0] - key)){
            KClosest[count] = extractMin(minHeap, minHeapSize);
        }
	}
	if(count != k){
        while(maxHeapSize and count != k){
        	KClosest[count] = extractMax(maxHeap, maxHeapSize);
        	count ++;
        }
        while(minHeapSize and count != k){
        	KClosest[count] = extractMin(minHeap, minHeapSize);
        	count ++;
        }
	}
    
    cout << "The k-closest elements from the key are :-\n";
	for(int i = 0; i < k; i ++) cout << KClosest[i] << " "; cout << endl;

	return 0;
}
