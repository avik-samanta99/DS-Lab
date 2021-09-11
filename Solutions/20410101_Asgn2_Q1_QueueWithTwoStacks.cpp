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
================================================================================
Class Stack : This implements the Stack Functionalities 
stackList : This is the pointer to the list where we will stack up the elements
stackTop : This denotes the Top of the stack, where we can Push and Pop
stackSize : This denotes the maximum number of elements our stack can hold
Stack() : Constructor intializing the data of our Stack class
setSize() : Setting the size of our stackList, provided by the user
isEmpty() : Method to tell us if our stack is empty or not
isFull() : Method to tell us if our stack is full or not
push() : This function implements the push functionality of our Stack
pop() : This function implements the pop functionality of our Stack
display() : This displays the stackList as LIFO / FILO
displayReverse() : This displays the stackList as FIFO / LILO
~Stack() : This is the destructor, which deletes the List pointer at the end
template<class T> : This is to implement the generic Datatypes concept
================================================================================
*/
template <class T>
class Stack{
	private:
		T *stackList;
		int stackTop;
		int stackSize;
		
	public:
		Stack (){
            stackList = NULL;
            stackTop = -1;
            stackSize = 0;
		}

		void setSize(int size){
			stackList = new T(size);
			stackTop = -1;
			stackSize = size;
		}

		bool isEmpty(){
			return (stackTop == -1);
		}

		bool isFull(){
			return (stackTop == stackSize - 1);
		}

		void push(T data){
			stackList[stackTop + 1] = data;
			stackTop ++;
		}

		T pop(){
			T elementPoped = stackList[stackTop];
			stackTop --;
			return elementPoped;
		}
		
		void display(){
			for(int i = stackTop; i >= 0; i --) 
			    cout << stackList[i] << " ";
		}
		
		void displayReverse(){
			for(int i = 0; i <= stackTop; i ++) 
			    cout << stackList[i] << " ";
		}
		
		~Stack(){
			delete (stackList);
		}
};


/*
================================================================================
Class Queue : This implements the Queue Functionalities 
stackInsert : This is a Stack type variable, to help in enQueue/insert operation
stackDelete : This is a Stack type variable, to help in deQueue/delete operation
Queue() : default Constructor
setSize() : Setting the size of both the stackInsert and stackDelete
isEmpty() : Method to tell us if our Queue is empty or not
isFull() : Method to tell us if our Queue is full or not
enQueue() : This function implements the Insert functionality of our Queue
deQueue() : This function implements the Delete functionality of our Queue
display() : This displays the current situation of our Queue
displayNext() : This displays the next element in our Queue
template<class T> : This is to implement the generic Datatypes concept
================================================================================
*/
template <class T>
class Queue{
	private:
		Stack<T> stackInsert, stackDelete;
		
	public:
		Queue(){}
        
        /*
        ==============================================================================
        setSize() : This is to set the size of both the stacks, as per the user wants
		==============================================================================
        */
		void setSize(int size){
			stackInsert.setSize(size);
			stackDelete.setSize(size);
		}

        /*
        ================================================================================================================
        isFull() : This is the function to check if the Queue is full or not (If we can insert anymore elements or not)
		-> if the stackInsert is full and stackDelete is not empty, then the Queue is full 
		-> Else if stackInsert is not full or stackInsert is full but stackDelete is empty, then our Queue is not full
		================================================================================================================
        */
		bool isFull(){
            return (stackInsert.isFull() and !stackDelete.isEmpty());
		}

        /*
        ==================================================================================================================================================
        isEmpty() : This is the function to check if the Queue is empty or not
		-> if both the stackInsert and stackDelete are empty, then the Queue is empty; else Queue is not empty if either of them has at least one element
		==================================================================================================================================================
        */
		bool isEmpty(){
			return (stackInsert.isEmpty() and stackDelete.isEmpty());
		}

        /*
        ==================================================================================================================================================
        enQueue() : This is the function for Insertion, implemented by pushing the value in the stackInsert (or Stack-1)
		-> We will push the element into stackInsert if there is a space for the element (stackInsert is not full)
		-> Or if stackInsert is full and stackDelete is empty, we transfer all the elements from stackInsert to stackDelete, then push it into stackInsert
		-> But if stackInsert is full and there are some elements in  stackDelete, we will block the Insertion
		==================================================================================================================================================
        */
		void enQueue(T data){
			if(isFull()){
				cout << "We are out of space in the stack-1 (stack for insertion).\n";
				cout << "And the stack-2 (stack for Deletion) is not empty to transfer all the elements.\n";
				cout << "Delete some elements first to insert again.\n\n";
			}
			else if(stackInsert.isFull()){
				while(!stackInsert.isEmpty()){
            		T popedElement = stackInsert.pop();
            		stackDelete.push(popedElement);
            	}
            	stackInsert.push(data);
            	cout << "Data has been inserted to our Queue.\n\n";
            }
            else{
            	stackInsert.push(data);
            	cout << "Data has been inserted to our Queue.\n\n";
            }
		}

        /*
        ===================================================================================================================================================
        deQueue() : This is the function for Deletion, implemented by popping a value out from the stackDelete (or Stack-2)
		-> We will pop one element out from stackDelete if there are one or more elements in stackDelete (stackDelete is not empty)
		-> Or if stackDelete is empty and stackInsert is not empty, we transfer all the elements from stackInsert to stackDelete, then pop from stackDelete
		-> But if stackDelete is empty and there are no elements in stackInsert, we will give a message that there are no elements in the Queue
		===================================================================================================================================================
        */
        void deQueue(){
            if(isEmpty()){
            	cout << "There is nothing to delete, as the queue is already empty.\n";
            	cout << "Please insert some elements to delete again.\n\n";
            }
            else if(stackDelete.isEmpty()){
            	while(!stackInsert.isEmpty()){
            		T popedElement = stackInsert.pop();
            		stackDelete.push(popedElement);
            	}
            	T deleted = stackDelete.pop();
            	cout << "The deleted element is : " << deleted << ".\n\n";
            }
            else{
            	T deleted = stackDelete.pop();
            	cout << "The deleted element is : " << deleted << ".\n\n";
			}
        }

        /*
        ===================================================================================================================================================
        displayNext() : This is the function for displaying the next element in the Queue
        -> Implementation is same as delete or deQueue, but at the end we will push the poped element back after displaying 
		-> We will pop one element out from stackDelete if there are one or more elements in stackDelete (stackDelete is not empty)
		-> Or if stackDelete is empty and stackInsert is not empty, we transfer all the elements from stackInsert to stackDelete, then pop from stackDelete
		-> But if stackDelete is empty and there are no elements in stackInsert, we will give a message that there are no elements in the Queue
		-> If deleted then we will push the element back into the stackDelete, to keep our Queue content unchanged
		===================================================================================================================================================
        */
        void displayNext(){
            if(isEmpty()){
        		cout << "There is nothing to show. The Queue is empty.\n\n";
        	}
        	else if(stackDelete.isEmpty()){
            	while(!stackInsert.isEmpty()){
            		T popedElement = stackInsert.pop();
            		stackDelete.push(popedElement);
            	}
            	T deleted = stackDelete.pop();
            	cout << "The next element in the Queue : " << deleted << ".\n\n";
            	stackDelete.push(deleted);
            }
            else{
            	T deleted = stackDelete.pop();
            	cout << "The next element in the Queue : " << deleted << ".\n\n";
            	stackDelete.push(deleted);
			}
        }

        /*
        ==============================================================================================
        display() : This is the function for displaying the Queue (the current situation of the Queue)
        -> We will print the stackDelete in FILO / LIFO manner and stackInsert as FIFO / LILO manner 
		==============================================================================================
        */
        void display(){
        	if(isEmpty()){
        		cout << "There is nothing to show. The Queue is empty.\n\n";
        	}
        	else{
        		cout << "This is our Queue : ";
        		stackDelete.display();
        		stackInsert.displayReverse();
        		cout << "\n\n";
        	}
        }
        
        ~Queue() {}
};

/*
============================================================================================================
This is the driver function for all the Queue operations; I tried to make it as interractive as possible
Also made it a generic function, so that we can use the datatype as the user wants, type is not pre-defined
============================================================================================================
*/
template<class T>
void QueueOperationDriverFunction(){
	Queue<T> myQueue;
	int size, choice;
	while(true){
		cout << "\nEnter the size of the Stacks to be used : ";
		cin >> size;
		if(size > 0) break;
		else cout << "What! Do you want elements in your queue or not? Please try again..\n";
	}
	myQueue.setSize(size);
	/*cout << "-> So, as per your chosen size of stack, our Queue can hold at max (" << 2 * size << ") elements at once.\n";
	cout << "-> But at worst case, it may block insertions even if there are only (" << size + 1 << ") elements.\n";
	cout << "-> It may happen if the Stack-2 has one element only, and Stack-1 is full (has " << size << " elements).\n";
	cout << "-> Now if you try to insert any element, as Stack-1 is full and we can't transfer them into Stack-2, the insertion will be blocked.\n";
	cout << "-> So, the maximum capacity of our Queue may vary from (" << size + 1 << ") to (" << 2 * size << ").\n";
	cout << "-> This completely depends on the order of execution of operations (Insert and Delete).\n\n";*/
    cout << "\nNow choose from following options what you want to do :-\n";
    cout << "1. Insert an elemetnt (enQueue),\n";
    cout << "2. Delete an element (deQueue),\n";
    cout << "3. Display the next element in the Queue,\n";
    cout << "4. Display the current Queue,\n";
    cout << "5. Terminate the program.\n\n";
    while(true){
    	cout << "Enter your choice : ";
    	cin >> choice;
    	switch(choice){
    		case 1:{
    			T data;
                cout << "Enter the element you want to insert : ";
                cin >> data;
                myQueue.enQueue(data);
                break;
    		}
    		case 2:{
                myQueue.deQueue();
                break;
    		}
    		case 3:{
    			myQueue.displayNext();
    			break;
    		}
    		case 4:{
                myQueue.display();
                break;
    		}
    		case 5:{
    			cout << "Ohh! You choose to exit...\n";
    			cout << "Thanks!! That was a lot of fun.\n";
                exit(0);
    		}
    		default:
    		    cout << "Invalid entry. Enter again...\n\n";
    	}
    }
}

/*
===========================================================================
This is to give some basic information about the myself and the assignment
===========================================================================
*/
void info(){
	cout << "----------------------------------------------------------------------------\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 2nd Assignment : \"QUEUE USING TWO STACKS\" !!\n";
	cout << "----------------------------------------------------------------------------\n\n";
}

/*
=================================================================================
This is a helper function to make the user select a datatypeof his/her preference
=================================================================================
*/
int selectType(){
	int choice;
    cout << "What type of data are you going to store in the queue?\n";
	cout << "Choose one of the following :-\n";
	cout << "1. Enter 1 for integer.\n";
	cout << "2. Enter 2 for character.\n";
	cout << "3. Enter 3 for float.\n";
	cout << "4. Enter 4 for double.\n";
	while(true){
		cout << "Enter your choice for preferred datatype : ";
		cin >> choice;
        if(choice <= 4 and choice >= 1) break;
        else cout << "Invalid Entry. Try again.\n"; 
	}
	return choice;
}

/*
===========================
Main or the Driver function
===========================
*/
int main(){
	info();
	int type = selectType();
	switch(type){
		case 1:
            QueueOperationDriverFunction <int> ();
            break;
		case 2:
            QueueOperationDriverFunction <char> ();
            break;
		case 3:
            QueueOperationDriverFunction <float> ();
            break;
		case 4:
            QueueOperationDriverFunction <double> ();
            break;
		default :
		    cout << "Invalid Entry. We need to exit.\n";
		    exit(0);
	}
	return 0; 
}
