/*
 * @file graph.cpp Constructs a graph with vertices and weighted
 * edges, and findest the shortest path utilizing a min priority
 * queue.
 *
 * @author Katherine Jouzapaitis
 * @date 05/08/2016
 */

#include "graph.h"

/*
 * @brief Creates a new Vertex and adds it to the vertices map
 *
 * @param name a string containing the name of the vertex
 *
 * @return nothing
 *
 * Creates a new Vertex for the vertices map. The name will
 * be passed in via parameter the temp Vertex has no initial
 * value and will be assigned later.
 */
void Graph::addVertex(string name) {
   Vertex* temp = new Vertex();
   vertices[name] = *temp;
}

/*
 * @brief Creates a new weighted edge and adds it to the adjList map
 *
 * @param from a string containing the name of the vertex the edge
 * will start at
 * @param to a string containing the name of the vertex the edge will
 * end at
 * @param weight an integer containing the cost of following that edge
 *
 * @return nothing
 *
 * Creates a new Neighbor with the name from the to parameter and weight
 * from the weight parameter. Adds the Neighbor to the adjList indexed
 * by the from parameter.
 */
void Graph::addEdge(string from, string to, int weight) {
   Neighbor* temp = new Neighbor();
   temp->name = to;
   temp->weight = weight;
   adjList[from].push_back(*temp);
   std::sort(adjList[from].begin(), adjList[from].end(), [ ](const Neighbor& lhs, const Neighbor& rhs) {return (lhs.name < rhs.name);});
}

/*
 * @brief Calls buildSSPTree to get the shortest path and puts
 * together the vertex infomation for output using std out
 *
 * @param from a string containing the name of the starting Vertex
 * in the path
 * @param to a string containing the name of the ending Vertex
 * in the path
 *
 * @return a string listing the Vertices in the path separated by
 * "->", then followed by " with length " and the cost of the entire
 * path.
 */
string Graph::getShortestPath(string from, string to) {
   if(currentSource != from) {
      buildSSPTree(from);
   }
   
   std::list <string> pathList;
   pathList.push_front(to);
   string temp = vertices[to].pi;
   while(temp != from) {
      pathList.push_front(temp);
      temp = vertices[temp].pi;
   }
   pathList.push_front(from);
   
   std::stringstream shortPath;
   for(std::list <string>::iterator it = pathList.begin(); it != pathList.end(); it++) {
      shortPath << *it;
      if(*it != to) {
         shortPath << "->";
      }
   }
   
   shortPath << " with length " << vertices[to].key;
   
   return shortPath.str();
}

/*
 * @brief Using Dijkstra's algorithm and min priority queue to
 * calculate the shortest path from a given source
 *
 * @param source a string containing the name of the Vertex that
 * is the starting point of the shortest path
 *
 * @return nothing
 *
 * Iterates through the map of vertices giving the source a weight
 * of 0 and every other vertice a weight of INT_MAX. Puts the
 * vertices in the min priority queue, then extracts from the
 * min priority queue to start relaxing the edges to get the
 * appropriate weights assigned as the path is calculated.
 */
void Graph::buildSSPTree(string source) { //Dijkstra
   currentSource = source;
   for(map<string, Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
      if(it->first != source) {
         it->second.key = INT_MAX;
         it->second.pi = "NIL";
      } else {
         it->second.key = 0;
      }
      minQ.insert(it->first, it->second.key);
   }
   while(1) {
      std::string u = minQ.extractMin();
      if(u == "empty") {
         break;
      }
      for(vector<Neighbor>::iterator it = adjList[u].begin(); it != adjList[u].end(); it++) {
         relax(u, it->name, it->weight);
      }
   }
}

/*
 * @brief Calculates the weight of the edge as the path
 * from a source lengthens
 *
 * @param u a string containing the name of the vertex that is
 * the starting point of the particular edge being looked at
 * @param v a string containing the name of the vertex that is
 * the ending point of the particular edge being looked at
 * @param weight an integer containing the weight from vertex
 * u to v
 *
 * @return nothing
 *
 * Checks to see is the current key of v is greater than the
 * key of u and the weight to get from u to v combined. If it
 * is the key of v is changed to the sum of the weight and key
 * of u to get an accurate cost to v from the source of the
 * SSPTree. Finally decreases the key of vertex v so it ends
 * up in the right place in the min priority queue.
 */
void Graph::relax(string u, string v, int weight) {
   if(vertices[v].key > (vertices[u].key + weight)) {
      vertices[v].key = vertices[u].key + weight;
      vertices[v].pi = u;
      minQ.decreaseKey(v, vertices[v].key);
   }
}