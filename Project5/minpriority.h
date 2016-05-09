/*
 * @file minpriority.h Empliments and manipulates a min priority queue
 *
 * @author Katherine Jouzapaitis
 * @date 05/04/2016
 */
#include <cmath>
#include <vector>
#include <string>
#include <climits>

using std::string;

class MinPriorityQ {
public:
   MinPriorityQ(/*int size*/);
   ~MinPriorityQ();
   void insert(string id, int key);
   void decreaseKey(string id, int newKey);
   string extractMin();
   bool isMember(string id);
private:
   class Element {
   public:
      string id;
      int key;
   };
   
   //Element[] minHeap;
   std::vector<Element*> minHeap;
   
   void buildMinHeap();
   void minHeapify(int i);
   int parent(int i);
   int left(int i);
   int right(int i);
};