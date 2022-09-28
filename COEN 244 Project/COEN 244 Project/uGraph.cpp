#include "uGraph.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <vector>
#include <stack>

uGraph::uGraph() : numNodes(0), numEdges(0)
{
	Nodes = new Node[limit];
	Edges = new Edge[3 * limit];
}

uGraph::~uGraph()
{
	delete[] Nodes;
	delete[] Edges;
}
// adds node, checks if it reached limit, checks if there is an identical node (based on ID) - DONE
bool uGraph::addNode(Node& n)
{
	if (numNodes < limit) { // if the number of nodes exceeds certain limit, it fails to add
		for (int i = 0; i < numNodes; i++) { // check to see if there is an identical node within the array
			if (n.getID() == Nodes[i].getID()) {
				cout << "Identical node exists, did not add." << endl;
				return false;
			}
		}
		for (int i = 0; i < numNodes; i++) { // adds node into the array in order (based on ID)
			if (n.getID() < Nodes[i].getID()) {
				for (int j = numNodes; j > i; j--) {
					Nodes[j] = Nodes[j - 1];
				}
				Nodes[i] = n;
				numNodes++;
				return true;
			}
		}
		Nodes[numNodes] = n;
		numNodes++;
		return true;
	}
	cout << "Could not add Node. Reached limit to how many nodes can be added. Check the limit member variable for max size." << endl;
	return false;
}
// removes node, checks to see if it exists first, removes any edges that is related to that node - DONE
bool uGraph::removeNode(Node& n)
{
	for (int i = 0; i < numNodes; i++) {
		if (n.getID() == Nodes[i].getID()) {
			for (int j = 0; j < numEdges; j++) {
				if ((n.getID() == Edges[j].getstart()->getID()) || (n.getID() == Edges[j].getend()->getID())) {
					removeEdge(Edges[j]);
					j--;
				}
			}
			for (int j = i; j < numNodes - 1; j++) {
				Nodes[j] = Nodes[j + 1];
			}
			numNodes--;
			return true;
		}
	}
	cout << "Could not remove node. It does not exist." << endl;
	return false;
}
// adds edge, checks to see if it hasnt reached limit, checks to see if there isnt any duplicate edges, doesn't self loop - DONE
bool uGraph::addEdge(Edge& e)
{
	if (numEdges < 3 * limit) { // the number of edges is limited to the size of nodes times 3
		for (int i = 0; i < numEdges; i++) { // checks to see if there isnt any duplicates
			if ((e.getstart()->getID() == Edges[i].getstart()->getID()) && (e.getend()->getID() == Edges[i].getend()->getID())) {
				cout << "Edge already exists. Did not add." << endl;
				return false;
			}
		}
		if (e.getstart()->getID() == e.getend()->getID()) { // checks to see if it loops to itself
			cout << "Edge loops to itself, not allowed, did not add." << endl;
			return false;
		}
		for (int i = 0; i < numEdges; i++) { // adds the edge in after all checks
			if (e.getstart()->getID() <= Edges[i].getstart()->getID()) { // adds edges into the array semi-orderly

				for (int j = numEdges; j > i; j--) {
					Edges[j] = Edges[j - 1];
				}
				Edges[i] = e;
				numEdges++;
				sortEdges(); // fully sorts and orders edges by ID
				return true;
			}
		}
		Edges[numEdges] = e;
		numEdges++;
		return true;
	}
	cout << "Could not add Edge. Reached limit to how many edges can be added. Check the limit member variable for max size." << endl;
	return false;
}
// removes edge
bool uGraph::removeEdge(Edge& e)
{
	for (int i = 0; i < numEdges; i++) {
		if ((e.getstart()->getID() == Edges[i].getstart()->getID()) && (e.getend()->getID() == Edges[i].getend()->getID())) {
			for (int j = i; j < numEdges - 1; j++) {
				Edges[j] = Edges[j + 1];
			}
			numEdges--;
			return true;
		}
	}
	cout << "Could not remove Edge." << endl;
	return false;
}
// searches for node based on ID
bool uGraph::searchNode(int ID)
{
	for (int i = 0; i < numNodes; i++) {
		if (ID == Nodes[i].getID()) {
			return true;
		}
	}
	cout << "Could not find specified node." << endl;
	return false;
}
// searches for edge based on start and end ID
bool uGraph::searchEdge(int a, int b)
{
	for (int i = 0; i < numEdges; i++) {
		if ((a == Edges[i].getstart()->getID()) && (b == Edges[i].getend()->getID())) {
			return true;
		}
	}
	cout << "Could not find specified edge." << endl;
	return false;
}
// returns node if given an ID, it if exists
Node& uGraph::getNode(int ID) const
{
	for (int i = 0; i < numNodes; i++) {
		if (Nodes[i].getID() == ID) {
			return Nodes[i];
		}
	}
	cout << "Does not exist..." << endl;
	exit(0);
}
// redo, return based on nodes.......
Edge& uGraph::getEdge(Node& first, Node& last) const
{
	for (int i = 0; i < numEdges; i++) {
		if ((first.getID() == Edges[i].getstart()->getID()) && (last.getID() == Edges[i].getend()->getID())) {
			return Edges[i];
		}
	}
	cout << "Could not get edge, it does not exist..." << endl;
	exit(0);
}
// gets number of nodes
int uGraph::getnumNodes() const
{
	return numNodes;
}
// gets number of edges
int uGraph::getnumEdges() const
{
	return numEdges;
}
// checks if it is empty - DONE
bool uGraph::isEmpty() const
{
	if (getnumNodes() == 0 && getnumEdges() == 0)
		return true;
	else return false;
}

void uGraph::printNodesByID() const
{
	for (int i = 0; i < numNodes; i++) {
		Nodes[i].print();
		cout << endl;
	}
}
// prints all nodes with their respective adjacent edges
void uGraph::printAll() const
{
	cout << "Total number of Nodes: " << getnumNodes() << ", total number of Edges: " << getnumEdges() << endl;
	for (int i = 0; i < numNodes; i++) {
		Nodes[i].print();
		cout << ": ";
		for (int j = 0; j < numEdges; j++) {
			if (Edges[j].getstart()->getID() == Nodes[i].getID()) {
				Edges[j].print();
				cout << ", ";
			}
		}
		cout << endl;
	}
}
// prints path for node n
void uGraph::printPath(Node& n) const
{
	vector<bool> Ed(numEdges, true);
	vector<vector<Node>> paths; // all current paths that are done.
	vector<Node> dfs;
	bool itExists = false;

	for (int i = 0; i < numNodes; i++) { // checks if node exists in nodes[i] array
		if (Nodes[i].getID() == n.getID()) {
			itExists = true;
		}
	}
	if (!itExists) {
		cout << "Node does not exist, therefore cannot print path. Exiting..." << endl;
		return;
	}

	int counter = 0; // for undirected graph, will loop through all edges as if there is only one direction, then we will do it again in the reverse direction to find all paths
	dfs.push_back(n); // pushes initial starting node into the array
	do {
		for (int i = 0 + counter; i < Ed.size(); i++) { // the first node that is found to be adjacent to the node on top of the dfs stack
			if ((dfs.back().getID() == Edges[i].getstart()->getID()) && (Ed[i] == true)) { // if the node at the end of stack
				if (dfs.back().getID() == n.getID()) { // if the last node
					counter++;
					Ed.clear();
					Ed.resize(numEdges);
					for (int l = 0; l < Ed.size(); l++) { // reinitialize everything to true after it finds n.getID() everytime to properly loop through all nodes
						Ed[l] = true;
					}
				}
				dfs.push_back(*Edges[i].getend()); // pushes the node that the edge is ending on
				Ed[i] = false; // it has seen the edge
				i = counter - 1; // starts from the approapriate 
				paths.push_back(vector<Node>()); // create a new path
				for (int k = 0; k < dfs.size(); k++) {
					paths[paths.size() - 1].push_back(dfs[k]);
				}
			}
		}
		dfs.pop_back();
	} while (!dfs.empty());

	counter = 0; // for undirected graph, will loop through all edges as if there is only one direction, then we will do it again in the reverse direction to find all paths
	dfs.push_back(n); // pushes initial starting node into the array
	do {
		for (int i = 0 + counter; i < Ed.size(); i++) { // the first node that is found to be adjacent to the node on top of the dfs stack
			if ((dfs.back().getID() == Edges[i].getend()->getID()) && (Ed[i] == true)) { // if the node at the end of stack
				if (dfs.back().getID() == n.getID()) { // if the last node
					counter++;
					Ed.clear();
					Ed.resize(numEdges);
					for (int l = 0; l < Ed.size(); l++) { // reinitialize everything to true after it finds n.getID() everytime to properly loop through all nodes
						Ed[l] = true;
					}
				}
				dfs.push_back(*Edges[i].getstart()); // pushes the node that the edge is ending on
				Ed[i] = false; // it has seen the edge
				i = counter - 1; // starts from the approapriate 
				paths.push_back(vector<Node>()); // create a new path
				for (int k = 0; k < dfs.size(); k++) {
					paths[paths.size() - 1].push_back(dfs[k]);
				}
			}
		}
		dfs.pop_back();
	} while (!dfs.empty());

	for (int i = 0; i < paths.size(); i++) {
		for (int j = 0; j < paths[i].size(); j++) {
			cout << paths[i][j].getID() << "<->";
		}
		cout << endl;
	}
}
// loops through printPath()
void uGraph::printAllPath() const
{
	for (int i = 0; i < numNodes; i++) {
		cout << "Paths for " << Nodes[i].getID() << ": " << endl;
		printPath(Nodes[i]);
		cout << endl;
	}
}
// sorts edges from least to greatest by IDs
void uGraph::sortEdges()
{
	Edge* temp;
	temp = new Edge();
	int i = 0;
	int j = 0;
	for (i = 0; i < numEdges; i++) {
		for (j = i; j < numEdges; j++) {
			if (Edges[i].getstart()->getID() == Edges[j].getstart()->getID()) {
				if (Edges[i].getend()->getID() >= Edges[j].getend()->getID()) {
					*temp = Edges[j];
					Edges[j] = Edges[i];
					Edges[i] = *temp;
					continue;
				}
			}
			break;
		}
	}
}
// wipes everything clean
bool uGraph::clean()
{
	numNodes = 0;
	numEdges = 0;
	delete[] Nodes;
	delete[] Edges;
	Nodes = new Node[limit];
	Edges = new Edge[3 * limit];
	if (numNodes == 0 && numEdges == 0) {
		return true;
	}
	else return false;
}
