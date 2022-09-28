#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node
{
public:
	Node();
	Node(const char*, const char*);
	Node(string, string);
	Node(const Node&);
	~Node();

	char* getfirst() const;
	char* getlast() const;
	int getID() const;

	void setfirst(const char*);
	void setlast(const char*);

	void print() const;

	const Node& operator=(const Node&);
	const bool operator==(const Node&) const;
	const bool operator!=(const Node&) const;
private:
	char* firstname;
	char* lastname;
	static int nNodes;
	int ID;
};

#endif NODE_H