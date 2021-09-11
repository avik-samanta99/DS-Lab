/*
==============================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. 4(b) : PreOrder Threaded tree Traversal
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
=============================================
*/

#include<bits/stdc++.h>
using namespace std;
#define leftChild first // first element of the pair is the left child
#define rightChild second // second element of the pair is the right child

/*
====================================================
Structure for a node of the tree 
-> nodeID : unique node ID for each node
-> left / right : children nodes
-> thread : If there's a thread from the node or not
====================================================
*/
class treeNode{
	public:
	int nodeID;
	bool thread;
	treeNode *left, *right;
};

/*
===============================
Creating anode of type treeNode
===============================
*/
treeNode *createNode(int id){
	treeNode *temp = new treeNode();
	temp -> nodeID = id;
	temp -> left = NULL;
	temp -> right = NULL;
	temp -> thread = false;
}

/*
======================================================================
This function traverse the pre-order threaded binary tree in pre-order
======================================================================
*/
void preOrderThreadedTraversal(treeNode *root){
	treeNode *curNode = root;
	while(curNode){
		cout << curNode -> nodeID << " ";
		if(curNode -> left) curNode = curNode -> left;
		else curNode = curNode -> right;
	} cout << endl;
}

/*
===========================================================================
This is to give some basic information about the student and the assignment
===========================================================================
*/
void info(){
	cout << "========================================================================\n";
	cout << "Hii !! This is Avik Samanta...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the 4th Assignment : \"Threaded Binary Tree\" !!\n";
	cout << "========================================================================\n\n";
}

void instruction(){
	cout << "Here are explaination of the approach and instruction to follow :-\n\n";
	cout << "1. First we will construct our Binary Tree having the pre-order threads :-\n";
	cout << "-> We are using linked representation of Binary Tree,\n";
	cout << "-> Where, nodeID : each node has unique nodeID to identify them,\n";
	cout << "-> In our case please keep the nodeID as 1 to n (integers) [n : no of nodes],\n";
	cout << "-> left : link to the left child of the current node,\n";
	cout << "-> right : link to the right child of the current node,\n";
	cout << "-> thread : If the node has a pre-order thread or not,\n";
	cout << "-> User should give input in the following format :-\n";
	cout << "   -> Each input denotes one edge of the binary tree, with format like :-\n";
	cout << "   -> parent child link [parent nodeID | child nodeID | which link (L : left / R : right)],\n";
	cout << "   -> i.e. 1 2 L [this indicates, Node 2 is left child of Node 1 (edge from 1 to 2),\n";
	cout << "   -> In that case if a tree has n nodes, there is n-1 edges, so, n-1 such input needed.\n";
	cout << "-> Now based on that, we created vector of pairs, with index being the nodeID, and pair containing the left and right child info,\n";
	cout << "-> Then we will construct the binary tree level by level [using a queue, containg the node addresses of the tree],\n";
	cout << "-> Now there are three cases, while creating the threads [as we are creating preorder threaded binary tree],\n";
	cout << "-> case 1 : the current node have both the right and left child,\n";
	cout << "   -> Then the thread will be transfered to the right child [if there's a thread at the current node],\n";
	cout << "   -> And the thread will be removed from the node we are inspecting now [if there's a thread at the current node].\n";
	cout << "   -> And the left child will now have a thread to the right child,\n";
	cout << "-> case 2 : the current node only have the left child,\n";
	cout << "   -> Then the thread will be transfered to the left child [if there's a thread at the current node],\n";
	cout << "   -> And the thread will be removed from the current node [if there's a thread at the current node].\n";
	cout << "-> case 3 : the current node only have the right child,\n";
	cout << "   -> Then the thread will be transfered to the right child [if there's a thread at the current node],\n";
	cout << "   -> And the thread will be removed from the current node [if there's a thread at the current node].\n\n";
	cout << "2. Now traverse the tree in pre-order :-\n";
	cout << "-> We will display whichever node we are currently at,\n",
	cout << "-> If the node has a left child, then the current node is being updated to the left child,\n",
	cout << "-> Or if there's no left child, then the current node will be updated to the right child,\n",
	cout << "-> The right pointer either points to the right child (if there), else points to the pre-order successsor,\n";
	cout << "If there's no right child, not even preorder successor, then the right child is NULL, that means, that's the end of traversal.\n\n";
}

/*
===============
Driver fucntion
===============
*/
int main(){
	/*
	==========================================================================
	Some pre-processing, giving instructions and explaination of the approach
	==========================================================================
	*/
	info();
	instruction();
	
	/*
	==================================================
	Constructing the binary tree with preorder threads 
	==================================================
	*/
	int n, parent, child, rootNode;
	char link;
	// input for the umber of nodes
	while(true){
		cout  << "Enter the number of nodes : ";
		cin >> n;
		if(n <= 0) cout << "Invalid entry! Try again...\n";
		else break;
	}
	// List to keep track of the nodes and their children
	vector<pair<int, int>> ourBinaryTree(1000, make_pair(-1, -1));
	// list to keep track of the address of the nodes in the tree
    treeNode *nodeAddress[1000];
    for(int i = 0; i <= n; i ++) nodeAddress[i] = NULL;
    // input for the edges in the tree
	cout << "So enter the edges\' information (parent-child-link) :-\n";
	for(int i = 1; i < n; i ++){
		cin >> parent >> child >> link;
		if(link == 'l' or link == 'L'){
			ourBinaryTree[parent].leftChild = child;
		}
		else{
			ourBinaryTree[parent].rightChild = child;
		}
	}
	
	// Creating the preorder threaded tree
	cout << "Enter the root Node : ";
	cin >> rootNode;
	treeNode *root = createNode(rootNode);
	// Queue to maintain the level by level construction
	vector<treeNode *> queue;
	queue.push_back(root);
	// Iterate until we are done
	while(!queue.empty()){
		treeNode *curNode = queue[0];
		queue.erase(queue.begin());
		// case 1 : when our node has both the children (left and right)
		if(ourBinaryTree[curNode -> nodeID].leftChild != -1 and ourBinaryTree[curNode -> nodeID].rightChild != -1){
			treeNode *threadNode = curNode -> right;
			curNode -> left = createNode(ourBinaryTree[curNode -> nodeID].leftChild);
			curNode -> right = createNode(ourBinaryTree[curNode -> nodeID].rightChild);
			if(curNode -> thread){
				curNode -> right -> right = threadNode;
				curNode -> right -> thread = true;
				curNode -> thread = false;
			}
			curNode -> left -> right = curNode -> right;
			curNode -> left -> thread = true;
			queue.push_back(curNode -> left);
			queue.push_back(curNode -> right);
		}
		// case 2 : when our node has only the left child
		else if(ourBinaryTree[curNode -> nodeID].leftChild != -1){
			curNode -> left = createNode(ourBinaryTree[curNode -> nodeID].leftChild);
			if(curNode -> thread){
				curNode -> left -> right = curNode -> right;
				curNode -> left -> thread = true;
				curNode -> right = NULL;
				curNode -> thread = false;
			}
			queue.push_back(curNode -> left);
		}
		// case 3 : when our node has only the right child
		else if(ourBinaryTree[curNode -> nodeID].rightChild != -1){
			treeNode *threadNode = curNode -> right;
			curNode -> right = createNode(ourBinaryTree[curNode -> nodeID].rightChild);
			if(curNode -> thread){
				curNode -> right -> right = threadNode;
				curNode -> right -> thread = true;
				curNode -> thread = false;
			}
			queue.push_back(curNode -> right);
		}
	}
	
	// traverse the tree in pre-order[using the pre-order threads
	cout << "\nThe pre-order traversal [using the threads] :-\n";
	preOrderThreadedTraversal(root);
	
	return 0;
}
