#include "Edge.h"
#include "Node.h"
#include <iostream>
using namespace std;


Edge::Edge() : years(0)
{
	start = new Node();
	end = new Node();
}

Edge::Edge(Node& s, Node& e, int years) : years(years)
{
	start = new Node(s);
	end = new Node(e);
}

Edge::Edge(const Edge& rhs) : years(rhs.years)
{
	start = new Node(*rhs.start);
	end = new Node(*rhs.end);
}

Edge::~Edge()
{
	delete start;
	delete end;
}

Node* Edge::getstart() const
{
	return start;
}

Node* Edge::getend() const
{
	return end;
}

int Edge::getyears() const
{
	return years;
}

void Edge::setstart(Node* s)
{
	start = s;
}

void Edge::setend(Node* e)
{
	end = e;
}

void Edge::setyears(int y)
{
	years = y;
}

void Edge::print() const
{
	cout << "(" << start->getID() << ", " << end->getID() << ")"; // "years: " << getyears() << endl;
}

const Edge& Edge::operator=(const Edge& rhs)
{
	if (&rhs != this) {
		years = rhs.years;
		start = rhs.start;
		end = rhs.end;
	}
	return *this;
}

const bool Edge::operator==(const Edge& rhs) const
{
	if ((start == rhs.start) && (end == rhs.end)) { // need to check && (years == rhs.years)
		return true;
	}
	return false;
}

const bool Edge::operator!=(const Edge& rhs) const
{
	if ((start != rhs.start) || (end != rhs.end)) { // need to check || (years != rhs.years)
		return true;
	}
	return false;
}
