#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <string>

using namespace std;

class Graph
{ // see uGraph or dGraph for more comments on the implementation
public:
	Graph() = default;
	virtual ~Graph() {};

	virtual bool addNode(Node&) = 0; // adds only one node
	virtual bool removeNode(Node&) = 0; // removes only one node
	virtual bool addEdge(Edge&) = 0;
	virtual bool removeEdge(Edge&) = 0;
	virtual bool searchNode(int) = 0;
	virtual bool searchEdge(int, int) = 0;
	virtual Node& getNode(int) const = 0;
	virtual Edge& getEdge(Node&, Node&) const = 0;
	virtual int getnumNodes() const = 0;
	virtual int getnumEdges() const = 0;
	virtual bool isEmpty() const = 0;
	virtual void printNodesByID() const = 0;
	virtual void printAll() const = 0;
	virtual void printPath(Node&) const = 0;
	virtual void printAllPath() const = 0; 
	virtual bool clean() = 0;
};

#endif GRAPH_H