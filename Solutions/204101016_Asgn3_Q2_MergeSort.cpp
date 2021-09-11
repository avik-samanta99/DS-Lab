/*
======================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. 3(b) : In-Place Merge Sort
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
======================================
*/

#include<bits/stdc++.h>
using namespace std;

/*
======================================================
Structure to represent one number in the array (list)
-> data : data / value in the node 
-> next : this points to the node just next to it
======================================================
*/
struct listNode{
	int data;
	listNode *next;
};

/*
============================================================
Function to create a node for a specific value / key / data
============================================================
*/
listNode *createNode(int value){
	listNode *curNode = new listNode();
	curNode -> data = value;
	curNode -> next = NULL;
	return curNode;
}

/*
=======================================================================================
Finding the middle of the linked list
-> We use two pointers, one slow, and another fast
-> slow pointer moves one step at a time
-> fast pointer moves two steps at a time
-> So, when the fast pointer reaches the end of the list, the slow reaches the middle
-> That's how we find the middle of a linked list [in O(n) time]
=======================================================================================
*/
void findMiddle(listNode **head, listNode **middle){
	if(!(*head) or !((*head) -> next)) *middle = *head;
	listNode *fast = (*head) -> next, *slow = *head;
	while(fast and fast -> next){
		slow = slow -> next;
		fast = fast -> next -> next;
	}
	*middle = slow;
}

/*
========================================================================================================================================
Merging two already sorted linked list
-> Here we pick one element each from both the lists, one after another
-> then we compare those two values from each list
-> if element from left list is smaller, then we will take that element, and move the pointer to the next element in the left list
-> or if element from right list is smaller, then we will take that element, and move the pointer to the next element in the right list
-> at the end we will end up with a whole sorted list, combining both the left and right list
-> here we are not using any extra memory / space, as we are just modifying the links of the elements / nodes, not storing it elsewhere
========================================================================================================================================
*/
void merge(listNode **head, listNode **leftHead, listNode **rightHead){
	listNode *itrLeft = *leftHead, *itrRight = *rightHead;
	listNode *itrHead;
	bool headFound = false;
	while(itrLeft and itrRight){
		if(itrLeft -> data <= itrRight -> data){
			if(!headFound){
			    *head = itrLeft;
			    itrHead = *head;
			    headFound = true;
			}
			else{
			    itrHead -> next = itrLeft;
			    itrHead = itrHead -> next;
			}
		    itrLeft = itrLeft -> next;
		}
		else{
			if(!headFound){
			    *head = itrRight;
			    itrHead = *head;
			    headFound = true;
			}
			else{
			    itrHead -> next = itrRight;
			    itrHead = itrHead -> next;
			}
		    itrRight = itrRight -> next;
		}
	}
	if(itrLeft) itrHead -> next = itrLeft;
	if(itrRight) itrHead -> next = itrRight;
}

/*
==============================================================================
Merge Sort of the linked list
-> Base Case : If the list is empty or has one element, return the list
-> Find the middle of the linked list [O(n) time]
-> Divide the list into two parts, using the middle element
-> Recusrsively solve for both the parts [T(n/2)]
-> Then merge the two solutions, to get the complete sorted list [O(n) time]
==============================================================================
*/
void mergeSort(listNode **head){
	if(!(*head) or !((*head) -> next)) return;
	listNode *leftHead = *head, *middle;
	findMiddle(head, &middle);
	listNode *rightHead = middle -> next;
	middle -> next = NULL;
	mergeSort(&leftHead);
	mergeSort(&rightHead);
	merge(head, &leftHead, &rightHead);
}

/*
===========================================================================
This is to give some basic information about the myself and the assignment
===========================================================================
*/
void info(){
	cout << "====================================================================\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 3rd Assignment : \"IN-PLACE MERGE SORT\" !!\n";
	cout << "====================================================================\n\n";
}

/*
====================================================================
This is to give some explaination of my approach towards the problem
====================================================================
*/
explainationOfApproach(){
	cout << "Let me explain my approach for the problem :-\n";
	cout << "-> First create a linked list using the elements,\n";
	cout << "-> Then we will use the method similar to normal merge sort, with just a little tweak,\n";
	cout << "-> Now we will find the middle of the linked list, using two pointers method,\n";
	cout << "-> Then we will divide the list into two parts, breaking the link using the middle element,\n";
	cout << "-> Now recursively solve for both the lists, which are created after dividing the list into two parts,\n";
	cout << "-> Then after recursively sorting both the sub lists, we have to merge those lists,\n";
	cout << "-> We will use the simple merge concept to merge those two lists,\n";
	cout << "-> Select one element from each list at a time, compare those two elements,\n";
	cout << "-> Smaller element gets selected, links are modified, and pointer moves to the next of the smaller element,\n";
	cout << "-> Repeat the process, until we explore all the elements from both the lists,\n";
	cout << "-> We don't have to use extra space, as we can just modify the links, to change the order.\n\n";
	cout << "Note : The code is implemented only for integer values ...\n\n";
	
}

int main(){
	/*
	=====================================
	Some preprocessing and documentation
	=====================================
	*/
	info();
	explainationOfApproach();
	
	/*
	========================================================
	-> Taking the imput array size (number of elements)
	-> Take the inputs (data) from the user (integer)
	-> Constructing a linked list with the elements entered
	========================================================
	*/
	int size, value;
	listNode *head, *itr;
	while(true){
		cout << "Enter the number of elements in the array : ";
		cin >> size;
	    if(size <= 0) cout << "Invalid input for size. Enter again.\n";
		else break;	
	}
	cout << "\nEnter the elements (integer) of the array to be sorted :-\n";
	for(int i = 0; i < size; i ++){
		cin >> value;
		listNode *curNode = createNode(value);
		if(i == 0) head = curNode;
		else itr -> next = curNode;
		itr = curNode;
	}
	
	/*
	====================================
	Applying merge sort on the elements
	====================================
	*/
	mergeSort(&head);
	
	/*
	=================================
	Output / Display the sorted list
	=================================
	*/
	cout << "\nThe list after sorting the elements :-\n";
	itr = head;
	while(itr){
	    cout << itr -> data << " ";
		itr = itr -> next;
	}
	cout << endl;
	
	return 0;
}
