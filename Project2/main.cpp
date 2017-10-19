/**
 * @author Deon Jackson
 * Course: CIS 350
 * Assignment: Project 2
 * Description: ...
 */

#include <vector>
using std::vector;

struct Node
{
    int id;
    int minRequests4Raise;
    vector< Node *> underlings;
    Node(int n = 0); // constructor
};

class Tree
{
private:
    Node * root;
    void print(Node * ptr, int level); // private version of print.
    Node * find(Node * root, int target); // private version of find.

public:
    Tree(Node * rt = nullptr);
    Tree(int id);
    Node * getRoot();
    void printTree(); // public print
    Node * find(int target); // public find
};

class Forest
{
private:
    vector< Tree > trees;
public:
    void print();
    Node * find(int target);
    void insert(int boss, int underling);
    Forest();
    void clear();
};