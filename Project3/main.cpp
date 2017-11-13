//
// Created by deonj on 11/11/2017.
//

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

Loon::Loon() {
    // Initialize to the upper bounds of x and y.
    this->xCord = INFINITY;
    this->yCord = 20.0;
}

Loon::Loon(int xCord, int yCord) {
    this->xCord = xCord;
    this->yCord = yCord;
}

Graph::Graph(int numPairs) {
    this->numPairs = numPairs;
}

void Graph::addLoon(Loon *loon) {
    loons.push_back(loon);
}

void Graph::visitClosestTwoStations(Loon *loon) {
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

string Graph::determineIfAllCanBeReached() {
    for (auto loon : loons) {
        if (loon->startingPos) {
            visitClosestTwoStations(loon);
            break;
        }

    }
    for (auto loon : loons) {
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

    while (numOfPairs) {
        graph = Graph{numOfPairs};
        for (int i = 0; i < numOfPairs; i++) {
            cin >> xVal >> yVal;
            loon = new Loon(xVal, yVal);
            loon->startingPos = (i == 0);
            loon->visited = (i == 0);
            graph.addLoon(loon);
        }
        cout << graph.determineIfAllCanBeReached() << endl;
        cin >> numOfPairs;
    }

}