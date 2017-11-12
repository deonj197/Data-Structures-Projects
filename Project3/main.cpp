//
// Created by deonj on 11/11/2017.
//

#include <vector>

using std::vector;

#include <iostream>

using std::cout; using std::cin; using std::endl;

#include <cmath>

#include <string>

using std::string;

struct Loon {
    int xCord;
    int yCord;
    bool visited;
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

    void printGraph();

    string determineIfAllCanBeReached();

};

Loon::Loon() {

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
    Loon *otherLoon1 = new Loon(100,100);
    Loon *otherLoon2 = new Loon(100,100);
    double minDistance = 100;
    double distToNextLoon;

    for (auto nextLoon : loons) {
        if (nextLoon->xCord != loon->xCord || nextLoon->yCord != loon->yCord) {
            distToNextLoon = sqrt(
                    pow((nextLoon->xCord - loon->xCord), 2) +
                    pow((nextLoon->yCord - loon->yCord), 2)
            );
            if (distToNextLoon < minDistance) {
                minDistance = distToNextLoon;
                otherLoon1 = nextLoon;
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
    minDistance = 100;
    for (auto nextLoon : loons) {
        if ((nextLoon->xCord != loon->xCord || nextLoon->yCord != loon->yCord) &&
                (nextLoon->xCord != otherLoon1->xCord || nextLoon->yCord != otherLoon1->yCord)) {
            distToNextLoon = sqrt(
                    pow((nextLoon->xCord - loon->xCord), 2) +
                    pow((nextLoon->yCord - loon->yCord), 2)
            );
            if (distToNextLoon < minDistance) {
                minDistance = distToNextLoon;
                otherLoon2 = nextLoon;
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
    if (!otherLoon1->visited) {
        otherLoon1->visited = true;
        visitClosestTwoStations(otherLoon1);
    }

    if (!otherLoon2->visited) {
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

void Graph::printGraph() {
    for (auto loon : loons) {
        cout << loon->visited << endl;
    }
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