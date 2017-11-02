/**
 * @author Deon Jackson
 * Course: CIS 350
 * Assignment: Project 2
 * Description: The program accepts as input, a sequence of two line cases,
 * where the first line has two numbers. The first number represents a number
 * of employees (N), and the second number represents the percentage of employees reporting to
 * any given supervisor that must request a raise, in order for the supervisor to
 * submit a raise request to their own supervisor. On the second line of each case, there are N
 * numbers, each of which represents the boss of an employee. For example, if the third number is a five,
 * then the boss of employee number three is employee number five.
 * The program reads in cases until the first line reads 0 0, and prints out a organizational chart for each case.
 */

#include <vector>

using std::vector;

#include <iostream>

using std::cout; using std::cin; using std::endl;

#include <cmath>

using std::ceil;

#include <algorithm>

using std::find; using std::sort; using std::begin; using std::end;

struct Node {
    int id;
    int minRequests4Raise;
    vector<Node *> underlings;
    explicit Node(int n = 0); // constructor
};

class Tree {
private:
    Node *root;
    void print(Node *ptr, int level); // private version of print.
    Node *find(Node *root, int target); // private version of find.
    Node *recursiveFind(Node *root, int target);

public:
    explicit Tree(Node *rt = nullptr);
    explicit Tree(int id);
    Node *getRoot();
    void printTree(); // public print
    Node *find(int target); // public find
};

class Forest {
private:
    vector<Tree> trees;
public:
    void print();
    Node *find(int target);
    void insert(int boss, int underling);
    explicit Forest();
    void clear();
    Node *recursiveFind(Node *root, int target);
    int calculateVotesNeeded(Node *root);
    int calculateDepth(Node *root);
    void sortForest(Node *root);
};

/**
 * Purpose: Initialize a Node object.
 * Pre: n >= 0.
 * Post: A node has been created with id = n.
 * @param n a positive integer.
 */
Node::Node(int n) {
    id = n;
}

/**
 * Purpose: Initialize a Tree object.
 * Pre: rt != nullptr and points to the address of a node with
 * a set id, and potentially children as well.
 * Post: A Tree has been created with rt as its root.
 * @param rt pointer to a Node.
 */
Tree::Tree(Node *rt) {
    root = rt;
}

/**
 * Purpose: Initialize a Tree object.
 * Pre: id >= 0.
 * Post: A Tree has been created with a node having a value of id
 * as its root.
 * @param id a positive integer.
 */
Tree::Tree(int id) {
    Node node{id};
    root = &node;
}

/**
 * Purpose: Retrieve the root of a Tree.
 * Pre: The Tree has been initialized.
 * Post: The tree is not altered, and its root is returned.
 * @return a Node * representing a root.
 */
Node *Tree::getRoot() {
    return root;
}

/**
 * Purpose: Prints a tree.
 * Pre: ptr != nullptr. level >= 0.
 * Post: An organizational representation of the tree is printed, with
 * all children in numerical order.
 * @param ptr a root of a Tree.
 * @param level, the current depth of the tree.
 */
void Tree::print(Node *ptr, int level) {
    for (int i = 0; i < level; ++i) {
        cout << "    ";
    }
    cout << ptr->id << endl;
    if (!ptr->underlings.empty()) {
        sort(ptr->underlings.begin(), ptr->underlings.end(), [](Node *a, Node *b) {
            return a->id < b->id;
        });
        for (auto child: ptr->underlings) {
            print(child, level + 1);
        }
    }
}

/**
 * Purpose: Public gateway to the master print function.
 * Pre: The tree being printed has been initialized.
 * Post: The private print function is called.
 */
void Tree::printTree() {
    print(root, 0);
}

/**
 * Purpose: Search a Tree's full structure for a given Node.
 * Pre: root != nullptr. level >= 0.
 * Post: A Node * if returned if the target id was found. Otherwise nullptr.
 * @param root
 * @param target
 * @return Node *
 */
Node *Tree::recursiveFind(Node *root, int target) {
    if (!root->underlings.empty()) {
        for (auto child: root->underlings) {
            if (child->id == target) {
                return child;
            } else {
                Node *node = recursiveFind(child, target);
                if (node != nullptr) {
                    return node;
                }
            }
        }
    }
    return nullptr;
}

/**
 * Purpose: Search for and retrieve a Node.
 * Pre: root != nullptr, target >= 0.
 * Post: A Node * if returned if the target id was found. Otherwise nullptr.
 * @param root
 * @param target
 * @return Node *
 */
Node *Tree::find(Node *root, int target) {
    if (root->id == target) {
        return getRoot();
    } else {
        Node *node = recursiveFind(root, target);
        return node;
    }
}

/**
 * Purpose: Public gateway to the private find function.
 * Pre: target >= 0.
 * Post: private find function is called.
 * @param target
 * @return Node *
 */
Node *Tree::find(int target) {
    return find(getRoot(), target);
}

/**
 * Purpose: Initialize a Forest object.
 * Post: A Forest is created.
 */
Forest::Forest() {
    trees.push_back(Tree(0));
}

/**
 * Purpose: Print a Forest.
 * Post: Each tree is the Forest is printed in organizational order.
 */
void Forest::print() {
    for (auto tree: trees) {
        if (tree.getRoot()->id == 0) {
            tree.printTree();
        }
    }
}

/**
 * Purpose: Insert a Node into the Forest, based on id.
 * Pre: boss >= 0. underling >= 0.
 * Post: The boss and underling are both inserted if they
 * were not already in the Forest.
 * @param boss
 * @param underling
 */
void Forest::insert(int boss, int underling) {
    Node *workerPointer = find(underling);
    Node *bossPointer = find(boss);
    bossPointer->underlings.push_back(workerPointer);
}

/**
 * Purpose: Search dull Forest structure for a given id.
 * Pre: root != nullptr. target >= 0.
 * Post: Either a Node * or nullptr is returned depending on whether or
 * not the id was found.
 * @param root
 * @param target
 * @return
 */
Node *Forest::recursiveFind(Node *root, int target) {
    if (!root->underlings.empty()) {
        for (auto child: root->underlings) {
            if (child->id == target) {
                return child;
            } else {
                Node *node = recursiveFind(child, target);
                if (node != nullptr) {
                    return node;
                }
            }
        }
    }
    return nullptr;
}

/**
 * Purpose: Determine how deep the root tree of the Forest is.
 * Pre: root != nullptr.
 * Post: The depth of the Forest ( >= 1 ) is found.
 * @param root
 * @return depth
 */
int Forest::calculateDepth(Node *root) {
    int depth = 1;
    int tempDepth = 0;
    int childDepth = 0;

    if (!root->underlings.empty()) {
        for (auto child: root->underlings) {
            tempDepth += calculateDepth(child);
            childDepth = (tempDepth > childDepth) ? tempDepth : childDepth;
            tempDepth = 0;
        }
    }

    return depth + childDepth;
}

/**
 * Purpose: Sort the trees based on size or depth, to ensure we are only counting the
 * minimum number of workers needed to submit requests.
 * Pre: root != nullptr
 * Post: All trees ahave been sorted.
 * @param root
 */
void Forest::sortForest(Node *root) {
    if (!root->underlings.empty()) {
        sort(root->underlings.begin(), root->underlings.end(), [this](Node *a, Node *b) {
            if (a->underlings.size() == b->underlings.size()) {
                return calculateDepth(a) < calculateDepth(b);
            }
            return a->underlings.size() < b->underlings.size();
        });
    }
    for (auto child: root->underlings) {
        sortForest(child);
    }
}

/**
 * Purpose: Calculate the minimum number of workers in the forest who must
 * request a raise in order for everyone to receive a raise.
 * Pre: root != nullptr.
 * Post: The minimum number of workers to submit requests is known.
 * @param root
 * @param threshold
 * @return min num of workers who must ask for a raise
 */
int Forest::calculateVotesNeeded(Node *root) {
    int retVal = 0;
    double decVal;
    int cielVal;
    int threshold = root->minRequests4Raise;

    if (!root->underlings.empty()) {
        if (threshold == 100) {
            cielVal = root->underlings.size();
        } else {
            decVal = ((double) threshold / 100.0) * root->underlings.size();
            cielVal = (int) ceil(decVal);

        }
        for (int i = 0; i < cielVal; i++) {
            retVal += calculateVotesNeeded(root->underlings[i]);
        }
    } else {
        retVal = 1;
    }

    return retVal;
}

/**
 * Search for a given id in the Forest.
 * Pre: target >= 0.
 * Post: A full recursive search of the Forest is executed
 * and either a Node * or nullptr is returned.
 * @param target
 * @return Node * if the id is found, or nullptr otherwise.
 */
Node *Forest::find(int target) {
    for (auto tree: trees) {
        if (tree.getRoot()->id == target) {
            return tree.getRoot();
        } else {
            Node *node = recursiveFind(tree.getRoot(), target);
            if (node != nullptr) {
                return node;
            }
        }
    }

    Node *n1 = new Node{target};
    Tree tree{n1};
    trees.push_back(tree);

    return tree.getRoot();
}

/**
 * Purpose: Clear the trees vector.
 * Post: All trees are vacated form the trees vector.
 */
void Forest::clear() {
    trees.clear();
}

int main() {
    int numEmployees;
    int requestThreshold;
    int boss;
    int underling;
    Forest forest{};
    Node *bossPointer;

    cin >> numEmployees >> requestThreshold;
    while (!(numEmployees == 0 && requestThreshold == 0)) {
        forest.clear();
        for (int i = 0; i < numEmployees; i++) {
            cin >> boss;
            bossPointer = forest.find(boss);
            bossPointer->minRequests4Raise = requestThreshold;
            underling = i + 1;
            forest.insert(boss, underling);
        }
        forest.sortForest(forest.find(0));
        cout << forest.calculateVotesNeeded(forest.find(0)) << endl;

        cin >> numEmployees >> requestThreshold;
    }
    return 0;
}

