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
#define maxStackSize 100

/*
========================================
Structure for a node of the tree 
-> nodeID : unique node ID for each node
-> left / right : children nodes
========================================
*/
struct treeNode{
	int nodeID;
	treeNode *left, *right;
};

/*
==============================================================
Function to create a treeNode, with given ID and default links
==============================================================
*/
treeNode *createNode(int id){
	treeNode *newNode = new treeNode();
	newNode -> nodeID = id;
	newNode -> left = NULL;
	newNode -> right = NULL;
	return newNode;
}

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
~Stack() : This is the destructor, which deletes the List pointer at the end
================================================================================
*/
class Stack{
	private:
		treeNode **stackList;
		int stackTop;
		int stackSize;
		
	public:
		Stack(){
            stackList = NULL;
            stackTop = -1;
            stackSize = 0;
		}

		void setSize(int size){
			stackList = new treeNode *[size]();
			stackTop = -1;
			stackSize = size;
		}

		bool isEmpty(){
			return (stackTop == -1);
		}

		bool isFull(){
			return (stackTop == stackSize - 1);
		}

		void push(treeNode *data){
			stackList[stackTop + 1] = data;
			stackTop ++;
		}

		treeNode *pop(){
			treeNode *elementPoped = stackList[stackTop];
			stackTop --;
			return elementPoped;
		}
		
		void display(){
			for(int i = stackTop; i >= 0; i --) 
			    cout << stackList[i] -> nodeID << " ";
		}
		
		~Stack(){
			delete (stackList);
		}
};

/*
===========================================
iterative algorithm for Pre-Order Traversal 
===========================================
*/
void preOrderIterative(treeNode *root){
	// defining our own stack
	Stack myStack;
	// setting the maximum size of the stack
    myStack.setSize(maxStackSize);
    // first push the root into the stack
    myStack.push(root);
    // we will iterate until the stack is empty
    while(!myStack.isEmpty()){
    	// pop the top element from the stack
    	treeNode *temp = myStack.pop();
    	// display the current element
    	cout << temp -> nodeID << " ";
    	// first push the right child into the stack
    	if(temp -> right) myStack.push(temp -> right);
    	// then push the left child into the stack
    	if(temp -> left) myStack.push(temp -> left);
	} cout << endl;
}

/*
============================================
iterative algorithm for Post-Order Traversal 
============================================
*/
void postOrderIterative(treeNode *root){
	// create two stacks
	Stack FirstStack, SecondStack;
	// set the maximum size of the stacks
    FirstStack.setSize(maxStackSize);
    SecondStack.setSize(maxStackSize);
    // first stack initially should contain the root, and the second stack should be empty
    FirstStack.push(root);
    // iterate until the first stack is empty
    while(!FirstStack.isEmpty()){
    	// pop the top element from the stack
    	treeNode *temp = FirstStack.pop();
    	// push that element into the second stack
    	SecondStack.push(temp);
    	// push the left child first into the first stack
    	if(temp -> left) FirstStack.push(temp -> left);
    	// then push the right child into the first stack
    	if(temp -> right) FirstStack.push(temp -> right);
	}
	// display the contents in the second stack [that is the post-order traversal]
	while(!SecondStack.isEmpty()){
		treeNode *temp = SecondStack.pop();
		cout << temp -> nodeID << " ";
	} cout << endl;
}

/*
===========================================================================
This is to give some basic information about the student and the assignment
===========================================================================
*/
void info(){
	cout << "===================================================================================\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 4th Assignment : \"Pre-Order & Post-Order Traversal\" !!\n";
	cout << "===================================================================================\n\n";
}

void instruction(){
	cout << "Here are explaination of the approach and instruction to follow :-\n\n";
	cout << "1. First we will construct our Binary Tree :-\n";
	cout << "-> We are using linked representation of Binary Tree,\n";
	cout << "-> Where, nodeID : each node has unique nodeID to identify them,\n";
	cout << "-> In our case try to keep the nodeID as 1 to n [n : no of nodes],\n";
	cout << "-> left : link to the left child of the current node,\n";
	cout << "-> right : link to the right child of the current node,\n";
	cout << "-> User should give input in the following format :-\n";
	cout << "   -> Each node denotes one edge of the binary tree, with format like :-\n";
	cout << "   -> parent child link [parent nodeID | child nodeID | which link (L : left / R : right)],\n";
	cout << "   -> i.e. 1 2 L [this indicates, Node 2 is left child of Node 1 (edge from 1 to 2),\n";
	cout << "   -> In that case if a tree has n nodes, there is n-1 edges, so, n-1 such input needed.\n";
	cout << "-> Then we will link the nodes edge by edge, to construct the binary tree.\n";
	cout <<"\n2. Now the approach for Iterative Pre-Order traversal :-\n";
	cout << "-> Pre-Order Traversal : [root -> left subtree (recursive) -> right subtree (recursive)],\n";
	cout << "-> We will try to replicate the recursive approach in our iterative approach,\n";
	cout << "-> We will make our own stack, initially will have only the root,\n";
	cout << "-> And in eah step, pop the top node, display the current node data,\n";
	cout << "-> Then we will push the right child first, then the left child,\n";
	cout << "-> So that LIFO property makes sure that left child is executed first, then the right child.\n";
	cout <<"\n3. Now the approach for Iterative Post-Order traversal :-\n";
	cout << "-> Post-Order Traversal : [left subtree (recursive) -> right subtree (recursive) -> root],\n";
	cout << "-> As the root is processed after the children, we have to keep the root stored anywhere else for later,\n";
	cout << "-> That's why we will use 2 stacks to implement the post-order traversal,\n";
	cout << "-> In First stack, we initially will have root, and second stack is initially empty,\n";
	cout << "-> In the first stack we pop out the top node each time, push it into the second stack,\n";
    cout << "-> Then push its children the first stack, [first left child, then right child],\n";
    cout << "-> So that left is poped from the 1st stack, and pushed into 2nd stack after right child,\n";
    cout << "-> Now if you see in the 2nd stack, the order is now, left child at top, then right child, and root at bottom.\n";
    cout << "-> Now if we display the 2nd stack, that is actually our post-order traversal.\n\n";
}

int main(){
	/*
	==========================================================================
	Some pre-processing, giving instructions and explaination of the approach
	==========================================================================
	*/
	info();
	instruction();
	
	/*
	============================
	Constructing the binary tree
	============================
	*/
	int n, parent, child, rootNode;
	char link;
	// input for the number of nodes (n)
	cout  << "Enter the number of nodes : ";
	cin >> n;
	// this stores the Address for each of the nodes
    treeNode *nodeAddress[1000];
    for(int i = 0; i <= n; i ++) nodeAddress[i] = NULL;
    // input for the edges (n-1) and construction of the tree
	cout << "So enter the edges\' information (parent-child-link) :-\n";
	for(int i = 1; i < n; i ++){
		cin >> parent >> child >> link;
		treeNode *newParent, *newChild;
		if(nodeAddress[parent] == NULL){
			newParent = createNode(parent);
			nodeAddress[parent] = newParent;
		}
        else newParent = nodeAddress[parent];
        if(nodeAddress[child] == NULL){
			newChild = createNode(child);
			nodeAddress[child] = newChild;
		}
        else newChild = nodeAddress[child];
        if(link == 'L' or link == 'l') newParent -> left = newChild;
        else if(link == 'R' or link == 'r') newParent -> right = newChild;
	}
	
	// selection of the root node
	cout << "Enter the root node : ";
	cin >> rootNode;
	treeNode *root = nodeAddress[rootNode];

    // function calls for the preorder and postorder traversal
    cout << "\nThe pre-order traversal of the tree is :-\n";
    preOrderIterative(root);
    cout << "\nThe post-order traversal of the tree is :-\n";
    postOrderIterative(root);
    
	return 0;
}
