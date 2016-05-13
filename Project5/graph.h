/*
 * @file graph.h Constructs a graph with vertices and weighted
 * edges, and findest the shortest path utilizing a min priority
 * queue.
 *
 * @author Katherine Jouzapaitis
 * @date 05/08/2016
 *
 * Resources:
 * https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 */

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include "minpriority.h"

using std::string;
using std::map;
using std::vector;

class Graph {
   public:
      void addVertex(string name);
      void addEdge(string from, string to, int weight);
      string getShortestPath(string from, string to);

   private:
      class Vertex {
         public:
            string pi;
            int key;
      };
      
      class Neighbor {
         public:
            string name;
            int weight;
      };

      void buildSSPTree(string source);
      void relax(string u, string v, int weight);
      string currentSource;
      map<string, Vertex> vertices;
      map<string, vector<Neighbor> > adjList;
      MinPriorityQ minQ;

      
};