/**
 *  main.cpp
 *  CIS 350
 *  Created on 9/19/2017
 *  Assignment: Project 1
 *  Description: Input is received as a string separated into several lines.
 *      The first line is the number of graphs to be input. Graphs are the main
 *      data type used in the program.
 *      The next line is the number of rows (lines) N that make up the first graph.
 *      The next N lines are the rows of the first graph.
 *          Each row begins with a char representing a vertex, followed by an int
 *          representing the number of vertices that are adjacent to that vertex, followed by a list of
 *          those vertices. All items in the row are separated by one space.
 *      After this the following lines are a repeat of the structure for the first graph,
 *      and this is done for all graphs (The number of graphs specified in teh first line of input).
 *      For each graph the vertices at the start of the row are organized into a vector
 *      which signifies the initial ordering of the vertices. Then all permutations of this order
 *      are tested to see which one produces the lowest max distance between two vertices
 *      that were listed as being adjacent to each other in the original input.
 *      Finally the order that meets this spec is printed on one line along with the max distance between
 *      adjacent nodes (cover) for that particular order. Again there is one space separating each item on a line,
 *      and one line is output for the solution to each graph.
 *  @author: Deon Jackson
 */

#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <vector>
using std::vector;
#include <iterator>
using std::begin; using std::end; using std::distance;
#include <algorithm>
using std::find; using std::next_permutation; using std::sort;
#include <string>
using std::to_string;
#include <cmath>


// from Data Structures and Algorithm Analysis in C++ (Third Edition), by Mark Allen Weiss
template<class Object>
class Matrix {
public:
    Matrix(int rows = 0, int cols = 0) : array(rows) {
        for (int i = 0; i < rows; i++)
            array[i].resize(cols);
    }

    void resize(int rows, int cols) {
        array.resize(rows);
        for (int i = 0; i < rows; i++)
            array[i].resize(cols);
    }

    const vector<Object> &operator[](int row) const { return array[row]; }

    vector<Object> &operator[](int row) { return array[row]; }

    int numrows() const { return array.size(); }

    int numcols() const { return numrows() ? array[0].size() : 0; }

private:
    vector<vector<Object>> array;
};

class Graph {
public:
    explicit Graph(int size); // creates an empty graph with size vertices
    void fillGraph(); // fills in the graph from cin
    void printGraph(); // prints the graph (for debugging only)
    void minimizeMaxCover();
    int maxCover(vector<char> order); // returns the maxCover for the
    // ordering order
    int cover(char vertex, vector<char> order); // returns the cover size for vertex
private:
    Matrix<char> adj;
};

/**
 * @post: Constructor for Graph object.
 * @param: size The number of vertices on the graph.
 */
Graph::Graph(int size) {
    adj.resize(size,1);
}

/**
 * @pre: Assumes that there is ample input form cin to fill the graph with.
 * @post: Fills a Graph object.
 */
void Graph::fillGraph() {
    char newChar;
    int numAdjNodes;
    for (int i = 0; i < adj.numrows(); i++) {
        cin >> newChar;
        adj[i][0] = newChar;
        cin >> numAdjNodes;
        adj[i].push_back(*(to_string(numAdjNodes).c_str()));
        for (int j = 0; j < numAdjNodes; j++) {
            cin >> newChar;
            adj[i].push_back(newChar);
        }
    }
}

/**
 * @post: Displays a Graph object.
 */
void Graph::printGraph() {
    for (int i = 0; i < adj.numrows(); i++) {
        for (auto letter: adj[i]) {
            cout << letter << " ";
        }
        cout << endl;
    }
}

/**
 * @pre: Assumes the order is sorted lexicographically
 * @post: Finds the maximum cover of a Graph object for the given order.
 * @param: order
 * @return: max cover
 */
int Graph::maxCover(vector<char> order) {
    int maxCover = 0;
    int currentCover = 0;
    for (auto letter: order) {
        currentCover = cover(letter,order);
        maxCover = (currentCover > maxCover) ? currentCover : maxCover;
    }
    return maxCover;
}

/**
 * @pre: Assumes the order is sorted lexicographically
 * @post: Finds the cover size for a vertex of a Graph object with a given order.
 * @param: vertex
 * @param: order
 * @return: cover
 */
int Graph::cover(char vertex, vector<char> order) {
    int cover = 0;
    int diff = 0;
    for (int row = 0; row < adj.numrows(); row++) {
        if (adj[row][0] == vertex) {
            const vector<char> & vertexRow = adj[row];
            for (int col = 2; col < vertexRow.size(); col++) {
                diff = abs(distance(find(order.begin(), order.end(), vertex),
                                    find(order.begin(), order.end(), vertexRow[col])));
                cover = (diff > cover) ? diff : cover;
            }
            break;
        }
    }

    return cover;
}

/**
 * Assumes a permutable container such us a vector is available and filled.
 * @post: Determines the order that minimizes the maximum cover.
 * Prints out the winning order and its maximum cover.
 */
void Graph::minimizeMaxCover() {
    int min = 5000;
    vector<char> baseOrder;
    vector<char> winningOrder;
    for (int i = 0; i < adj.numrows(); i++) {
        baseOrder.push_back(adj[i][0]);
    }
    sort(baseOrder.begin(),baseOrder.end());
    do {
        int max = maxCover(baseOrder);
        if (max < min) {
            min = max;
            winningOrder = baseOrder;
        } else if (max == min) {
            winningOrder = (winningOrder < baseOrder) ? winningOrder : baseOrder;
        }
    } while (next_permutation(baseOrder.begin(), baseOrder.end()));
    for (auto letter: winningOrder) {
        cout << letter << " ";
    }
    cout << min;
}
/**
 * @post: Entry point and hub for execution of the program.
 */
int main() {
    int numGraphs;
    cin >> numGraphs;
    for (int i = 0; i < numGraphs; i++) {
        int size;
        cin >> size;
        Graph graph{size};
        graph.fillGraph();
        //graph.printGraph();
        graph.minimizeMaxCover();
        if (i < (numGraphs-1)) {
            cout << endl;
        }
    }
    return 0;
}