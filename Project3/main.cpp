/**
 * Created by Deon Jackson on 11/11/2017.
 * Course: CIS 350 F17
 * Assignment: Program 3
 * Description: This program is intended to decide whether or not all points on a
 * two dimensional plane can be reached, given the assumptions that, there is a single
 * starting point and you may only advance to the two closest points away from any given
 * point on the graph. The first line of input specifies the number of points on the graph.
 * The following line of input is a list of the coordinates for each point. This pattern repeats
 * and input terminates when a value of 0 is fed in for the number of points.
 * As output, the program returns yes or no, for each graph that was fed in, depending onj whether on not all points
 * could be reached.
 */

#include <vector>

using std::vector;

#include <iostream>

using std::cout; using std::cin; using std::endl;

#include <cmath>

#include <limits.h>

#include <string>

using std::string;

struct Loon {
    double xCord;
    double yCord;
    bool visited = false;
    bool startingPos = false;
    Loon();
    Loon(int xCord, int yCord);
};

class Graph {
private:
    int numPairs;
    vector<Loon *> loons;
public:
    explicit Graph(int numPairs);
    void visitClosestTwoStations(Loon* loon);
    void addLoon(Loon *loon);
    string determineIfAllCanBeReached();
};

/**
 * Zero parameter constructor for Loon.
 * post: New loon is created with its coordinates at the max bounds of the graph.
 */
Loon::Loon() {
    // Initialize to the upper bounds of x and y.
    this->xCord = INFINITY;
    this->yCord = 20.0;
}

/**
 * Two parameter constructor for Loon.
 * pre: xCord >= -20. yCord <= 20.
 * post: New Loon is created with the given coordinates.
 * @param xCord
 * @param yCord
 */
Loon::Loon(int xCord, int yCord) {
    this->xCord = xCord;
    this->yCord = yCord;
}

/**
 * Single parameter constructor for Graph.
 * pre: 1 <= numPairs <= 1000.
 * post: New Graph is created with its numPairs field set the given value.
 * @param numPairs
 */
Graph::Graph(int numPairs) {
    this->numPairs = numPairs;
}

/**
 * Adds the supplied Loon to the graph.
 * pre: loon != nullptr.
 * post: the Loon is added to the graph.
 * @param loon
 */
void Graph::addLoon(Loon *loon) {
    loons.push_back(loon);
}

/**
 * Flag the closest two Loons to any given Loon as visited.
 * pre: loon != nullptr.
 * post: The closets two Loons have their visited flags set to true.
 * @param loon
 */
void Graph::visitClosestTwoStations(Loon *loon) {
    // Our two watch pointers for the closets two balloons.
    auto *otherLoon1 = new Loon;
    auto *otherLoon2 = new Loon;
    double minDistance = INFINITY;
    double distToNextLoon;

    for (auto nextLoon : loons) {
        // Make sure the next balloon in the graph is not the one we are finding the closest two for.
        if (nextLoon->xCord != loon->xCord || nextLoon->yCord != loon->yCord) {
            // Apply the linear distance formula to find distance between balloons.
            distToNextLoon = sqrt(
                    pow((nextLoon->xCord - loon->xCord), 2) +
                    pow((nextLoon->yCord - loon->yCord), 2)
            );
            // Reassign min if appropriate.
            if (distToNextLoon < minDistance) {
                minDistance = distToNextLoon;
                otherLoon1 = nextLoon;
            // Handle the ties.
            } else if (distToNextLoon == minDistance) {
                if (nextLoon->xCord < otherLoon1->xCord) {
                    otherLoon1 = nextLoon;
                } else if (nextLoon->xCord == otherLoon1->xCord) {
                    if (nextLoon->yCord < otherLoon1->yCord) {
                        otherLoon1 = nextLoon;
                    }
                }
            }
        }
    }

    // Find the second place winner (Second closest balloon)
    minDistance = INFINITY;
    for (auto nextLoon : loons) {
        // Make sure the next balloon in the graph is not the one we are finding the closest two for.
        if ((nextLoon->xCord != loon->xCord || nextLoon->yCord != loon->yCord) &&
                // Exclude the balloon that one first place already.
                (nextLoon->xCord != otherLoon1->xCord || nextLoon->yCord != otherLoon1->yCord)) {
            // Apply the linear distance formula to find distance between balloons.
            distToNextLoon = sqrt(
                    pow((nextLoon->xCord - loon->xCord), 2) +
                    pow((nextLoon->yCord - loon->yCord), 2)
            );
            // Reassign min if appropriate.
            if (distToNextLoon < minDistance) {
                minDistance = distToNextLoon;
                otherLoon2 = nextLoon;
            // Handle the ties.
            } else if (distToNextLoon == minDistance) {
                if (nextLoon->xCord < otherLoon2->xCord) {
                    otherLoon2 = nextLoon;
                } else if (nextLoon->xCord == otherLoon2->xCord) {
                    if (nextLoon->yCord < otherLoon2->yCord) {
                        otherLoon2 = nextLoon;
                    }
                }
            }
        }
    }
    // Check base case which is both the closest two have already been visited.
    // Call this method recursively on the two closest balloons until base case is met.
    if (!otherLoon1->visited) {
        // Flag the first place winner as visited.
        otherLoon1->visited = true;
        visitClosestTwoStations(otherLoon1);
    }

    if (!otherLoon2->visited) {
        // Flag the second place winner as visited.
        otherLoon2->visited = true;
        visitClosestTwoStations(otherLoon2);
    }
}

/**
 * Return the result of whether or not all loons ina  graph can be reached.
 * post: All reachable Loons have been visited and flagged.
 * @return
 */
string Graph::determineIfAllCanBeReached() {
    for (auto loon : loons) {
        // Find the starting balloon and proceed.
        if (loon->startingPos) {
            visitClosestTwoStations(loon);
            break;
        }
    }
    for (auto loon : loons) {
        // If one wasn't visited, we have our answer.
        if (!loon->visited) {
            return "no";
        }
    }

    return "yes";
}

int main() {
    int numOfPairs;
    int xVal;
    int yVal;
    Loon *loon;
    cin >> numOfPairs;
    Graph graph{numOfPairs};

    // Terminates on numOfPairs == 0.
    while (numOfPairs) {
        graph = Graph{numOfPairs};
        for (int i = 0; i < numOfPairs; i++) {
            // Grab your pair and make a Loon.
            cin >> xVal >> yVal;
            loon = new Loon(xVal, yVal);
            // Flag the starting balloon (start and visited).
            loon->startingPos = (i == 0);
            loon->visited = (i == 0);
            // Throw the Loon onto the graph.
            graph.addLoon(loon);
        }
        cout << graph.determineIfAllCanBeReached() << endl;
        cin >> numOfPairs;
    }

}