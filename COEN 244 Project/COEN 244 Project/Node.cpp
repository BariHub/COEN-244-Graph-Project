#include "Node.h"
#include <iostream>
using namespace std;

int Node::nNodes = 0;

Node::Node()
{
	firstname = nullptr;
	lastname = nullptr;
	ID = nNodes;
	nNodes++;
}

Node::Node(const char* fname, const char* lname)
{
	firstname = new char[strlen(fname) + 1];
	strcpy(firstname, fname);
	lastname = new char[strlen(lname) + 1];
	strcpy(lastname, lname);
	ID = nNodes;
	nNodes++;
}

Node::Node(string first, string last)
{
	firstname = new char[first.length() + 1];
	strcpy(firstname, first.c_str());
	lastname = new char[last.length() + 1];
	strcpy(lastname, last.c_str());
	ID = nNodes;
	nNodes++;
}

Node::Node(const Node& rhs)
{
	firstname = new char[strlen(rhs.firstname) + 1];
	strcpy(firstname, rhs.firstname);
	lastname = new char[strlen(rhs.lastname) + 1];
	strcpy(lastname, rhs.lastname);
	ID = rhs.ID;
}

Node::~Node()
{
	/*delete[] firstname;
	delete[] lastname;*/
}

char* Node::getfirst() const
{
	return firstname;
}

char* Node::getlast() const
{
	return lastname;
}

int Node::getID() const
{
	return ID;
}

void Node::setfirst(const char* first)
{
	firstname = NULL;
	firstname = new char[strlen(first) + 1];
	strcpy(firstname, first);
}

void Node::setlast(const char* last)
{
	lastname = NULL;
	lastname = new char[strlen(last) + 1];
	strcpy(lastname, last);
}

void Node::print() const
{
	cout << "ID: " << getID() << " Full name: " << getfirst() << " " << getlast();
}

const Node& Node::operator=(const Node& rhs)
{
	if (&rhs != this) {
		delete[] firstname;
		delete[] lastname;
		firstname = new char[strlen(rhs.firstname) + 1];
		strcpy(firstname, rhs.firstname);
		lastname = new char[strlen(rhs.lastname) + 1];
		strcpy(lastname, rhs.lastname);
		ID = rhs.ID;
	}
	return *this;
}

const bool Node::operator==(const Node& rhs) const
{
	if ((ID == rhs.ID)) return true;
	return false;
}

const bool Node::operator!=(const Node& rhs) const
{
	if (ID != rhs.ID) {
		return true;
	}
	return false;
}
