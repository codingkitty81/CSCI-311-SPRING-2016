

#include "graph.h"

void Graph::addVertex(string name) {
   Vertex* temp = new Vertex();
   vertices[name] = *temp;
}

void Graph::addEdge(string from, string to, int weight) {
   Neighbor* temp = new Neighbor();
   temp->name = to;
   temp->weight = weight;
   adjList[from].push_back(*temp);
}

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

void Graph::relax(string u, string v, int weight) {
   if(vertices[v].key > (vertices[u].key + weight)) {
      vertices[v].key = vertices[u].key + weight;
      vertices[v].pi = u;
      minQ.decreaseKey(v, vertices[v].key);
   }
}