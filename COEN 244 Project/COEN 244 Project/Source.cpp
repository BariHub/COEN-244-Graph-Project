#include <iostream>
#include <vector>
#include "Graph.h"
#include "uGraph.h"
#include "dGraph.h"
#include "Node.h"
#include "Edge.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// The graphs should be acyclic, the nodes and edges should not loop around, it was coded with that in mind
// nodes should not loop to itself, initially 10 nodes have been added, but you can still add or remove your own nodes. ALSO, the edges must be inputted manually.
// keep in mind...that I coded this thinking it was only one type of graph: Directed graph.
// However with that being said I did implement both types of graphs
int main() {
	Graph* grp = nullptr;
	int type;
	while (1) { // sets whether it is directed or undirected
		cout << "Choose graph type: Enter 0 for Undirected graph or 1 for Directed graph." << endl;
		cin >> type;
		if (type == 0) {
			grp = new uGraph();
			cout << "GRAPH SET TO UNDIRECTED." << endl;
			break;
		}
		else if (type == 1) {
			grp = new dGraph();
			cout << "GRAPH SET TO DIRECTED." << endl;
			break;
		}
		else {
			cout << "Did not input correct number try again..." << endl;
		}
	}

	// initializing all nodes from the file nodes.txt, starts off with 5 nodes
	cout << "Initializing all Nodes from a file. (Note: the edges must be inputted manually. Also, can add nodes or remove nodes afterwards.)" << endl;
	ifstream file;
	string first;
	string last;
	file.open("nodes.txt");
	if (!file) {
		cerr << "File could not be opened...";
		exit(1);
	}
	string line;
	int counter = 0;
	while (!file.eof()) {
		getline(file, line);
		istringstream str{ line };
		str >> first >> last;
		counter++;
	}
	Node* nd; // creates an array of nodes equal to the number of nodes in file
	nd = new Node[counter];
	Edge* ed[30];
	int i = 0;
	file.clear();
	file.seekg(0, ios::beg);
	while (!file.eof()) {
		getline(file, line);
		istringstream str{ line };
		str >> first >> last;
		nd[i] = Node(first, last);
		grp->addNode(nd[i]);
		i++;
	}

	int select;
	while (1) {
		cout << endl << "Below is a list of commands: " << endl; //
		cout << "Press 0 to exit the entire program." << endl; //
		cout << "Press 1 for adding node. (Can add an additional 15 nodes)" << endl; //
		cout << "Press 2 for removing node (based on its ID)." << endl; //
		cout << "Press 3 for adding edge." << endl; //
		cout << "Press 4 for removing edge." << endl; //
		cout << "Press 5 for search for a node.(Use function 6 or 7 to see which are available)" << endl; //
		cout << "Press 6 for print Nodes By ID." << endl; //
		cout << "Press 7 for print all information." << endl; //
		cout << "Press 8 for print all paths from one specific node." << endl; //
		cout << "Press 9 for print all path for every node." << endl; //
		cout << "Press 10 to obtain information of a certain node." << endl; //
		cout << "Press 11 to obtain information of a certain edge." << endl; //
		cout << "Press 12 for cleaning entire graph." << endl; //
		cout << "Press 13 to check if graph is empty." << endl << endl; //
		cin >> select;
		if (select > 13 || select < 0) {
			cout << "Out of bounds, select again." << endl;
		}

		string name;
		string surname;

		switch (select) {
		case 0:
			cout << "You chose to exit the program, closing..." << endl;
			return 0;
		case 1:
			cout << "You chose to add node, please input first name: ";
			cin >> name;
			cout << "You chose to add node, please input last name: ";
			cin >> surname;
			Node* example;
			example = new Node(name, surname);
			grp->addNode(*example);
			cout << "Node successfully added, use function 6 or 7 to check the list." << endl;
			break;
		case 2:
			int remove;
			cout << "Enter the ID of the node that you wish to remove: ";
			cin >> remove;
			if (grp->searchNode(remove)) {
				grp->removeNode(grp->getNode(remove));
				cout << "Remove successful." << endl;
			}
			else cout << "Did not remove, Node does not exist, try again." << endl;
			break;
		case 3:
			int s1;
			int s2;
			int y;
			cout << "Enter the ID of start node: ";
			cin >> s1;
			cout << "Enter the ID of end node: ";
			cin >> s2;
			cout << "How long has the two friends known each other for? (Enter number of years): ";
			cin >> y;
			cout << endl;

			if (!(grp->searchNode(s1)) || !(grp->searchNode(s2)) || (s1 == s2)) {
				cout << "One of the IDs inputted was invalid or the two inputs were identical, not allowed, try again..." << endl;
				break;
			}
			Edge* dummy;
			dummy = new Edge(grp->getNode(s1), grp->getNode(s2), y);
			if (grp->addEdge(*dummy)) {
				cout << "Edge (" << dummy->getstart()->getID() << ", " << dummy->getend()->getID() << ")" << " successfully added." << endl;
				break;
			}
			cout << "Could not add edge." << endl;
			break;
		case 4:
			int l1;
			int l2;
			cout << "Enter the ID of start node: ";
			cin >> l1;
			cout << "Enter the ID of end node: ";
			cin >> l2;
			cout << endl;

			if (!(grp->searchNode(l1)) || !(grp->searchNode(l2)) || (l1 == l2)) {
				cout << "One of the IDs inputted was invalid or the two inputs were identical, not allowed, try again..." << endl;
				break;
			}
			Edge* dummy1;
			dummy1 = new Edge(grp->getNode(l1), grp->getNode(l2), 10);
			if (grp->removeEdge(*dummy1)) {
				cout << "Removed the edge (" << dummy1->getstart()->getID() << ", " << dummy1->getend()->getID() << ")" << " successfully." << endl;
				break;
			}
			cout << "Edge doesnt exist." << endl;
			break;
		case 5:
			int search;
			cout << "Enter the ID of the node that you wish to search: ";
			cin >> search;
			if (grp->searchNode(search)) {
				cout << "Node exists." << endl;
				break;
			}
			else cout << "Node does not exist." << endl;
			break;
		case 6:
			grp->printNodesByID();
			break;
		case 7:
			grp->printAll();
			break;
		case 8:
			int idd;
			cout << "Input the ID of node you wish to find all paths for: ";
			cin >> idd;
			if (grp->searchNode(idd)) {
				grp->printPath(grp->getNode(idd));
				break;
			}
			cout << "Node with that ID does not exist." << endl;
			break;
		case 9:
			cout << "Printing all paths: " << endl;
			grp->printAllPath();
			break;
		case 10:
			int info;
			cout << "Input the ID of node you wish to know information of: ";
			cin >> info;
			if (grp->searchNode(info)) {
				grp->getNode(info).print();
				cout << endl;
				break;
			}
			break;
		case 11:
			int n1;
			int n2;
			cout << "Input the start ID of the edge: ";
			cin >> n1;
			cout << "Input the end ID of the edge: ";
			cin >> n2;
			if (grp->searchEdge(n1, n2)) {
				cout << "Edge exists, here are the pairs: ";
				grp->getEdge(grp->getNode(n1), grp->getNode(n2)).print();
				cout << endl;
				break;
			}
			break;
		case 12:
			if (grp->clean()) {
				cout << "graph is now clean." << endl;
			}
			else cout << "graph is not clean." << endl;
			break;
		case 13:
			if (grp->isEmpty()) {
				cout << "graph is empty." << endl;
			}
			else cout << "graph is not empty." << endl;
			break;
		}
	}

	file.close();
	return 0;
}