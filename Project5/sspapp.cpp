/*
 * @file sspapp.cpp Processes input to build and query a graph to
 * find the shortest path
 *
 * @author Katherine Jouzapaitis
 * @date 05/08/2016
 */

#include "sspapp.h"

/*
 * @brief Processes input to build the lists of vertices and
 * weighted edges
 *
 * @return nothing
 *
 * Uses std cin to get input. First input the number of vertices,
 * next a string with all the vertex names, next the number of
 * weighted edges, then looped through to get the edges.
 */
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

/*
 * @brief Processes the queries to calculate the shortest
 * path between two given vertices.
 * 
 * @return nothing
 *
 * Using std cin for input. The line gets separated into
 * two different strings to call getShortestPath.
 */
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