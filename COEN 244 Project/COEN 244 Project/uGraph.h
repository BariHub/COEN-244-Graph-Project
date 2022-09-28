#ifndef UGRAPH_H
#define UGRAPH_H

#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;

//template <int limit>
class uGraph :public Graph
{
public:
	uGraph();
	~uGraph();

	virtual bool addNode(Node&);
	virtual bool removeNode(Node&);
	virtual bool addEdge(Edge&);
	virtual bool removeEdge(Edge&);
	virtual bool searchNode(int); // searches for node if it exists
	virtual bool searchEdge(int, int); // searches for edge if it exists
	virtual Node& getNode(int) const; // gets node, if given an ID
	virtual Edge& getEdge(Node&, Node&) const; // gets node if given 2 nodes, start and end
	virtual int getnumNodes() const;
	virtual int getnumEdges() const;
	virtual bool isEmpty() const; // checks if graph is empty
	virtual void printNodesByID() const; // prints the nodes by ID and full name
	virtual void printAll() const; // prints all nodes with ID and full name alongside with its adjacent connections
	virtual void printPath(Node&) const; // print path for one specific node
	virtual void printAllPath() const; // print path for all nodes/ loops through
	virtual void sortEdges(); // sorts the edges in smallest to largest
	virtual bool clean(); // cleans the graph from all nodes and edges

private:
	int numNodes; // number of nodes
	int numEdges; // number of edges
	int limit = 20; // the maximum amount of allowable nodes, for edges, it is 3 times this amount.
	Node* Nodes;
	Edge* Edges;
};

#endif UGRAPH_H