

#include "sspapp.h"

void SSPapp::readGraph() {
    int vertNum;
    std::cin >> vertNum;
    string line;
    for(int i = 0; i < vertNum; i++) {
        std::cin >> line;
        myGraph.addVertex(line);
    }
    int edgeNum;
    std::cin >> edgeNum;
    string to;
    string from;
    int dist;
    std::getline(std::cin, line);
    for(int i = 0; i < edgeNum; i++) {
        std::getline(std::cin, line);
        std::istringstream input(line);
        input >> from >> to >> dist;
        myGraph.addEdge(from, to, dist);
    }
}

void SSPapp::processQueries() {
    string line;
    string from;
    string to;
    while(std::getline(std::cin, line)) {
        std::istringstream input(line);
        input >> from >> to;
        std::cout << myGraph.getShortestPath(from, to) << std::endl;
    }
}

int main() {
    SSPapp app;
    app.readGraph();
    app.processQueries();
    
    return 0;
}