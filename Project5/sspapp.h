/*
 * @file sspapp.h Processes input to build and query a graph to
 * find the shortest path
 *
 * @author Katherine Jouzapaitis
 * @date 05/08/2016
 */

#include <iostream>
#include <fstream>
#include "graph.h"

class SSPapp {
   public:
      void readGraph();
      void processQueries();
   private:
      Graph myGraph;
};