#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct neighborNode
{
string neighborName;
neighborNode * next;

neighborNode::neighborNode(string n, neighborNode * p) : neighborName(n),next(p)
{};

};


struct houseNode
{
string houseName;
neighborNode * neighborListHead;
houseNode * next;

houseNode::houseNode(string n, neighborNode * p, houseNode * t) : houseName(n),neighborListHead(p),next(t)
{};

};


class linkedlist
{
public:
linkedlist();
void addHouseNode(string hname);
void addNeighborNode (string hname, string nname);
void printAll();
bool hnExists(string hname);
bool nnExists(string hname, string nname);
void deleteAll(); //to deallocate all dynamic data
void conquer(string hname, string h2name);
void replacethename(string hname, string h2name);
bool controlpath();
private:
houseNode * head;
// any helper functions you see necessary
// ...
};