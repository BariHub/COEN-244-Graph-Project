#ifndef EDGE_H
#define EDGE_H
#include "Node.h"

class Edge
{
public:
	Edge();
	Edge(Node&, Node&, int);
	Edge(const Edge&);
	~Edge();

	Node* getstart() const;
	Node* getend() const;
	int getyears() const;
	void setstart(Node*);
	void setend(Node*);
	void setyears(int);

	void print() const;

	const Edge& operator=(const Edge&);
	const bool operator==(const Edge&) const;
	const bool operator!=(const Edge&) const;

private:
	int years;
	Node* start;
	Node* end;
};

#endif EDGE_H