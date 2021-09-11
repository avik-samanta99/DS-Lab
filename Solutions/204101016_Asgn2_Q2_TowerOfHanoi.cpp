/*
======================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. : Polynomial Class
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
======================================
*/

#include<bits/stdc++.h>
using namespace std;

/*
==============================================================
This is the stucture for each stack entry. This contains :-
-> Disks : representing the current no of disks to be moved
-> Source : representing the current source tower
-> Destination : representing the current destination tower
-> Intermediate : representing the current Intermediate tower
==============================================================
*/
struct stackEntry{
	int Disks;
	char Source, Destination, Intermediate;
};

/*
========================================================================================================
Stack : we are constructing the user defined stack, so that we can use that in our program
stackList : this is the list keeping trak of stack entries (entries are of user defined stackEntry type)
stackTop : defines the top of the stack (if no elements, stackTop = -1)
stackSize : represents the size of the stack (capacity of the stack)
Stack() : constructor, initializing the variables of the Stack class
isEmpty() : Checks if the Stack is empty or not
isFull() : checks if the Stack is full or not
push() : pushes the information (of type stackEntry) is there is space in the Stack
pop() : Pop the top element (last inserted) from the Stack, if there is any
~Stack() : Destructor, deleting the stackList pointer after the execution of our program
========================================================================================================
*/
class Stack{
	private:
		stackEntry *stackList;
		int stackTop;
		int stackSize;
		
	public:
		Stack(int size){
			stackList = (stackEntry *)malloc(sizeof(stackEntry) * size);
			stackTop = -1;
			stackSize = size;
		}
		
		bool isEmpty(){
			return (stackTop == -1);
		}
		
		bool isFull(){
			return (stackTop == stackSize - 1);
		}
		
		void push(stackEntry newEntry){
			if(isFull()){
				cout << "Stack Overflow. Program crashed. Exiting.\n";
				exit(0);
			}
			else{
				stackList[stackTop + 1] = newEntry;
				stackTop ++;
			}
		}
		
		stackEntry pop(){
			stackEntry poped;
			if(isEmpty()){
				poped.Disks = 0;
				poped.Source = poped.Destination = poped.Intermediate = ' ';
				return poped;
			}
			else{
				poped = stackList[stackTop];
				stackTop --;
				return poped;
			}
		}
		
		~Stack(){
			delete stackList;
		}
};

/*
===========================================================================
This is to give some basic information about the myself and the assignment
===========================================================================
*/
void info(){
	cout << "========================================================================================\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 2nd Assignment (Part 2) : \"TOWER OF HANOI (Iterative)\" !!\n";
	cout << "========================================================================================\n\n";
}

int main(){
	info();
	/*
	===========================================================================================
	Lets take three variables denoting the Towers (Source, Destination and Intermediate Towers)
	===========================================================================================
	*/
	char source, destination, intermediate;
	cout << "There are three sticks/rods : A , B and C...\n\n";
	
	/*
	=============================
	Let's choose the Source Tower
	=============================
	*/
	cout << "Which stick/rod do you want as your Source?\n";
	while(true){
	    cout << "Enter your choice (A , B or C) : ";
	    cin >> source;
	    if(source == 'A' or source == 'B' or source == 'C') break;
	    else cout << "Invalid Entry! Choose from given options...\n";
	}
	
	/*
	==================================
	Let's choose the Destination Tower
	==================================
	*/
	cout << "\nWhich stick/rod do you want as your Destination?\n";
	while(true){
		cout << "Enter your choice (A , B or C) : ";
	    cin >> destination;
	    if((destination == 'A' or destination == 'B' or destination == 'C') and (destination != source)) break;
	    else cout << "Invalid Entry! Choose the right option...\n";
	}
	
	/*
	================================================
	So make sure which one is the Intermediate Tower
	================================================
	*/
	if(source != 'A' and destination != 'A') intermediate = 'A';
	else if(source != 'B' and destination != 'B') intermediate = 'B';
	else if(source != 'C' and destination != 'C') intermediate = 'C';
	
	/*
	================================
	Let's decide the number of Disks
	================================
	*/
	int n;
	while(true){
	    cout << "\nEnter the number of disks : ";
		cin >> n;
		if(n > 0) break;
		else cout << "Invalid entry! Try again..\n";
	}
	
    /*
    ======================================================================================================
    Approach :-
    -> The concept for solving this problem is transfer n-1 disks to the Intermediate Tower (from Source)
	-> Then move the last disk to the Destination Tower (from Source Tower)
	-> Now tranefer those n-1 disks back to the Destination Tower (from Intermediate) 
	-> This is the recursive approach, though the same can be implemented iteratively using a Stack
	-> The main difference is that :- 
	-> The condition we call earlier in recursion, will be pushed into the stack later
	-> The condition we call later in recursion, will be pushed into the stack earlier
	-> So that the condition pushed later is executed earlier, due to LIFO characteristics of stack
	-> for (disks : n, source : A, destination : B, intermediate : C) the stacks entry would be >>
	-> a)  (disks : n-1, source : C, destination : B, intermediate : A)
	-> b)  (disks : 1, source : A, destination : B, intermediate : C)
	-> c)  (disks : n-1, source : A, destination : C, intermediate : B)
	-> And the execution of them is reverse of their entry in the stack
	-> And we will make a move only when, for current condition, the no. of disks = 1.
	======================================================================================================
    */
	Stack ourStack(3 * n);
	stackEntry newEntry;
	newEntry.Disks = n;
	newEntry.Source = source;
	newEntry.Destination = destination;
	newEntry.Intermediate = intermediate;
	ourStack.push(newEntry);

	cout << "\nSo the sequence of movement of disks is as follows :-\n";
	while(!ourStack.isEmpty()){
        stackEntry poped = ourStack.pop();
        if(poped.Disks == 1) 
        	cout << "Move the top disk from " << poped.Source << " -> " << poped.Destination << " .\n";
        else{
        	newEntry.Disks = poped.Disks - 1;
        	newEntry.Source = poped.Intermediate;
        	newEntry.Destination = poped.Destination;
        	newEntry.Intermediate = poped.Source;
        	ourStack.push(newEntry);
        	
        	newEntry.Disks = 1;
        	newEntry.Source = poped.Source;
        	newEntry.Destination = poped.Destination;
        	newEntry.Intermediate = poped.Intermediate;
        	ourStack.push(newEntry);
        	
        	newEntry.Disks = poped.Disks - 1;
        	newEntry.Source = poped.Source;
        	newEntry.Destination = poped.Intermediate;
        	newEntry.Intermediate = poped.Destination;
        	ourStack.push(newEntry);
        }
	}
	cout << "Total number of moves taken : " << pow(2, n) - 1 << " ...\n";
    
    cout << "\nThanks !! that was fun, right ...\n";
    
	return 0;
}
