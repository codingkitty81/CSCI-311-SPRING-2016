

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