/*
=====================================
Name : AVIK SAMANTA
Roll no. : 204101016 
Asgn. 5(b) : Topological Sort
Environment :-
IDE : Dev C++
Compiler : TDM-GCC 4.9.2 (64 Bits)
Language standard : GNU C++ 11
=====================================
*/

#include<bits/stdc++.h>
using namespace std;

/*
===========================================================================
This is to give some basic information about the myself and the assignment
===========================================================================
*/
void info(){
	cout << "================================================================\n";
	cout << "Hii !! This is Avik Samanta ...\n";
	cout << "M.Tech.(1st Year) : 204101016\n";
	cout << "This is the solution for the problem : \"TOPOLOGICAL ORDERING\" !!\n";
	cout << "================================================================\n\n";
}

/*
===========================
Explaination of my approach
===========================
*/
void approach(){
	cout << "Here is the explaination of the approach :-\n";
	cout << "-> First from the given input we are constructing the Adjacency List,\n";
	cout << "-> Then we are checking if the graph has a cycle or not (in the formal way),\n";
	cout << "-> Now we have successfully verified that the graph is a DAG,\n";
	cout << "-> Now we will use the Topological Sort concept to verify if the given ordering is right or not,\n";
	cout << "-> We will have a set of currently independent nodes, for which either parents are processed, or don't have one,\n";
	cout << "-> So the node we are currently inspecting has to be from that independent set,\n";
	cout << "-> Because all other nodes are dependent on at least one node from the set,\n";
	cout << "-> So at any iteration if the current node doesn't belong to the current independent set, the ordering is wrong,\n";
	cout << "-> If all the nodes pass the test, then yes! the ordering is a valid topological ordering.\n\n";
}

/*
=====================================================================================================
This function detects if there's any cycle in the graph or not
-> This is to check if the given graph is at all DAG or not
-> First create boolean lists isVisited[] and inRecStack[]
-> isVisited[v] : tells if v is already visited or not (initialized with false)
-> inRecStack[v] : if v is in the current recursion stack or not (initialized false)
-> For all the vertices do the following :-
   1. if the vertex is not visited, make both isVisited and inRecStack true
   2. Then for all the adjacent vertices of the vertex do the following :-
    a) if not visited, the recursively check if there's a cycle from the node 
    b) if yes, then return true (means we have a cycle), if no, then return false
    c) there will be a cycle iff the node we are considering, is already there in the recursionStack
   3. if none of the nodes unable to find any cycle, return false
=====================================================================================================
*/
bool ifCycle(int curNode, vector<vector<int>> &adjList, vector<bool> &isVisited, vector<bool> &inRecStack){
	if(!isVisited[curNode]){
		isVisited[curNode] = true;
		inRecStack[curNode] = true;
		for(int i = 0; i < adjList[curNode].size(); i ++){
			if(!isVisited[adjList[curNode][i]] and ifCycle(adjList[curNode][i], adjList, isVisited, inRecStack)) 
                return true; 
            else if(inRecStack[adjList[curNode][i]]) 
                return true; 
		}
	}
	inRecStack[curNode] = false;
    return false;
}

/*
===============================
Driver function : main function
===============================
*/
int main(){
	
	/*
	=================================================================
    Some preprocessing : giving some info and explaining the approach	
	=================================================================
	*/
	info();
	approach();
	
	int n, m, u, v, i, j;
	/*
	==========================================
	Taking the graph information from the user
	-> # vertices, # edges, edge details
	==========================================
	*/
	vector<vector<int>> adjList; // Adjacency list respect to the graph
	vector<int> inDegree; // In degree for each of the nodes
	while(true){
		cout << "Enter the number of nodes : ";
		cin >> n;
		for(int i = 0; i <= n; i ++){
			adjList.push_back({});
			inDegree.push_back(0);
		}
		cout << "Enter the number of edges : ";
		cin >> m;
		cout << "Enter the edge information of the graph :-\n";
		for(i = 0; i < m; i ++){
			cin >> u >> v;
			adjList[u].push_back(v);
			inDegree[v] ++;
		}
		
		/*
		============================================================================
		isVisited : boolean list to check which node is visited, which is not
		inRecStack : boolean list to check if the node is in recursion stack or not
		============================================================================
		*/
		vector<bool> isVisited(n + 1, false), inRecStack(n + 1, false);
		
		/*
		==========================================================================
		Code to verify the graph has a cycle or not, if it has then its not a DAG
		==========================================================================
		*/
		for(i = 1; i <= n; i ++){
		    if(ifCycle(i, adjList, isVisited, inRecStack)){
		    	cout << "There is a cycle in the graph. This is not a DAG. Please enter valid information.\n\n";
		    	adjList.clear();
		    	isVisited.clear();
		    	inRecStack.clear();
		    	inDegree.clear();
		    	break;
			}
		}
		if(i > n) break;
	}
	
	/*
	============================================================================
	Input for ordering from user and verifying if the ordering is right or wrong
	============================================================================
	*/
	cout << "Enter the ordering (of size " << n << ") you want to verify :-\n";
	int ordering[n];
	int flag = 1;
	for(int i = 0; i < n; i ++){
	    cin >> ordering[i];
	    /*
	    ========================================================================================
	    This is to verify every node belongs to our graph, if not then already invalid ordering
	    ========================================================================================
	    */
	    if(ordering[i] <= 0 or ordering[i] > n) flag = 0;
	}
	if(!flag) cout << "FALSE! This is not a valid Topological Ordering ...\n\n";
	else{
		/*
		======================================================================================================
		independent : this set keeps all those vertices, which are currently independent
		means their parents (node from which it has edges) has already processed, or they don't have a parent
		any element in the independent set is ready to put into the topological ordering
		======================================================================================================
		*/
		set<int> independent;
		/*
		=====================================================================================================================
		initially some nodes will have no parents, they are already independent, and the ordering must start with any of them
		=====================================================================================================================
		*/
	    for(i = 1; i <= n; i ++) 
		    if(inDegree[i] == 0) 
			    independent.insert(i);
		 
		for(i = 0; i < n; i ++){
			/*
			================================================================================================================
			if any node from the ordering we are currently inspecting is not from the independent set, the ordering is wrong
			================================================================================================================
			*/
			if(independent.find(ordering[i]) == independent.end()){
				cout << "FALSE! This is not a valid Topological Ordering ...\n\n";
				break;
			}
			/*
			===================================================================
			if that belongs to the independent set, then we can proceed further
			===================================================================
			*/
			else{
				/*
				=================================================================================================================================
				first we will remove all the dependencies from that node, means we will decrease the in-degree of all adjacent nodes of this node
				=================================================================================================================================
				*/
				for(j = 0; j < adjList[ordering[i]].size(); j ++){
					inDegree[adjList[ordering[i]][j]] --;
					/*
					==============================================================================================================================
					if during decreasing the in-degree, some node has zero in-degree, that means its independent now, we can put that into the set
					==============================================================================================================================
					*/
					if(!inDegree[adjList[ordering[i]][j]])
						independent.insert(adjList[ordering[i]][j]);
				}
				/*
				=========================================================================================================
				then finally we processed the node, we don't need this further, release the node from the independent set
				=========================================================================================================
				*/
				independent.erase(ordering[i]);
			}
		}
		/*
		===============================================================================================================
		If all the vertices pass the valid ordering test, that means the ordering given is a valid topological ordering
		===============================================================================================================
		*/
		if(i == n) cout << "TRUE! This is a valid Topological Ordering  ...\n\n";
	    independent.clear();
	}
	
	return 0;
}
