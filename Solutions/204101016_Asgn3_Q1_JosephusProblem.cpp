/*
======================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. 3(a) : Josephus Problem
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
Structure to represent one person
-> personID : gives us the a ID to identify a person
-> next : this points to the person left to him
-> prev : this points to the person right to him
======================================================
*/
struct listNode{
	int personID;
	listNode *next, *prev;
};

/*
==============================================================================================
Function to create a node for a specific person
-> person ID passed as argument to assign a ID to a person
-> pointer to the left person and as well as right person (if known) is also sent as argument
==============================================================================================
*/
listNode *createNode(int id, listNode *nextPerson, listNode *prevPerson){
	listNode *curPerson = new listNode();
	curPerson -> personID = id;
	curPerson -> next = nextPerson;
	curPerson -> prev = prevPerson;
	return curPerson;
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
	cout << "This is the solution for the 3rd Assignment : \"JOSEPHUS PROBLEM\" !!\n";
	cout << "====================================================================\n\n";
}

/*
====================================================================
This is to give some explaination of my approach towards the problem
====================================================================
*/
explainationOfApproach(){
	cout << "Overview of Josephus Problem :-\n\n";
	cout << "-> People are standing in a circle waiting to be executed.\n";
	cout << "-> Counting begins at a specified point in the circle and proceeds around the circle in the left direction.\n";
	cout << "-> After a specified number of people are skipped, the next person is executed.\n";
	cout << "-> The procedure is repeated with the remaining people, starting with the next person on the left.\n";
	cout << "-> We skip the same number of people, until only one person remains, and is freed.\n\n";
	cout << "Approach I have taken to solve the problem :-\n\n";
	cout << "1. A circular linked list to represent the circle of people, each node denoting a person.\n";
	cout << "2. Approach : The specified skip count = k, no of people = n :-\n";
	cout << "   -> We have to traverse k links to find the target person to be executed,\n";
	cout << "   -> Then after execution, we have to traverse another link to reset the start point,\n";
	cout << "   -> So for \"n (no of persons left) > k (no of skips)\", for each execution we need to traverse \"(k + 1)\" links,\n";
	cout << "   -> Now for \"n (no of persons left) <= k (no of skips)\", we actually don't have to traverse all \"(k + 1)\" links,\n";
	cout << "   -> We will be executing x'th person on the left of the current person, where x = (k % n),\n";
	cout << "   -> So for \"n <= k\", we have to traverse \"(k % n)\" links to execute one person and 1 to reset the start pointer, so (k % n) + 1 in total.\n\n";
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
	======================================================================================
	Getting the value of N (no of persons) and value of k (number of skips) from the user
	======================================================================================
	*/
	int n, k;
	while(true){
		cout << "Enter the number of persons : ";
		cin >> n;
		if(n <= 0) cout << "You have entered something invalid! Try again...\n";
		else break;
	}
	while(true){
		cout << "Enter the value of \"skip count\" : ";
		cin >> k;
		if(n < 0) cout << "You have entered something invalid! Try again...\n";
		else break;
	}
	
	/*
	============================================================
	Create the circular linked list with each persons as a node
	============================================================
	*/
	listNode *head = NULL, *prevPerson = NULL;
	for(int i = 1; i <= n; i ++){
		listNode *curPerson = createNode(i, head, prevPerson);
		if(i == 1){
		    head = curPerson;
		    head -> next = curPerson;
			head -> prev = curPerson;  
		}
		else{
		    prevPerson -> next = curPerson;
		    head -> prev = curPerson;   
		}
		prevPerson = curPerson;
	} cout << endl;
	
	/*
	========================================================================================================================================
	The specified skip count = k, no of people = n :-
	-> We have to traverse k links to find the target person to be executed,
	-> Then after execution, we have to traverse another link to reset the start point,
	-> So for "n (no of persons left) > k (no of skips)", for each execution we need to traverse "(k + 1)" links,
	-> Now for "n (no of persons left) <= k (no of skips)", we actually don't have to traverse all "(k + 1)" links,
	-> We will be executing x'th person on the left of the current person, where x = (k % n),
	-> So for "n <= k", we have to traverse "(k % n)" links to execute one person and 1 to reset the start pointer, so (k % n) + 1 in total.
	========================================================================================================================================
	*/
	int totCount = 0, curCount;
	while(n > 1){
		// Current state of the problem
		cout << "Person still alive : " << n << ", Skip count value : " << k << endl;
		
		// No of links to advance to find the target node
		curCount = (k % n);
		cout << "No of links traversed to find the target person : " << curCount << ".\n";
		
		// Advance with the links to Find the target person
		listNode *target = head;
		for(int i = 1; i <= curCount; i ++) 
		    target = target -> next;
		cout << "================= P" << head -> personID << " killed P" << target -> personID << " =================\n";
		
		// Modify links
		target -> prev -> next = target -> next;
		target -> next -> prev = target -> prev;
		
		// advance another link to reset the start point
		head = target -> next;
	    cout << "No. of links advanced to reset the start point : 1.\n\n";
	    curCount ++;
		
		// kill the target (delete node)
		free(target);
		n --;
		
		// update total links advanced count
		totCount += curCount;
	}
	cout << "Now we are left with only one person (P" << head -> personID << "). The process must halt here.\n\n";
    cout << "Total no of links traversed for the whole process : " << totCount << ".\n";
	
	return 0;
}
