/*
 * @file minpriority.cpp Empliments and manipulates a min priority queue
 *
 * @author Katherine Jouzapaitis
 * @date 05/04/2016
 *
 * Resources:
 * http://tjeyamy.blogspot.com/2013/01/minimum-priority-queue-implemented.html
 */
#include "minpriority.h"

/*
 * @brief Default constructor
 */
MinPriorityQ::MinPriorityQ(/*int size*/) {}

/*
 * @brief Destructor
 *
 * Clears minHeap for memory reasons.
 */
MinPriorityQ::~MinPriorityQ() {
   minHeap.clear();
}

/*
 * @brief Inserts a new Element to minHeap
 *
 * @param id a string containing data to be associated with a key
 * @param key an integer associated with a particular string id
 *
 * @return nothing
 *
 * Creates a new Element with the given id and INT_MAX for the key,
 * pushes the Element onto the end of minHeap, then calls decreaseKey
 * with the given key to adjust the key correctly and get the Element
 * into the right place within the minHeap.
 */
void MinPriorityQ::insert(string id, int key) {
   Element* temp = new Element();
   temp->id = id;
   temp->key = INT_MAX;
   minHeap.push_back(temp);
   decreaseKey(id, key);
}

/*
 * @brief Searches the minHeap for a given string and decreases the key
 * to a new given value, then adjusts Element's placement in the heap
 *
 * @param id a string the heap is searched through for
 * @param newKey an integer of the new value of the key that goes with
 * the given id
 *
 * @return nothing
 *
 * Iterates through the minHeap searching for the given id, changes the
 * corrisponding key to a smaller value, then adjusts the heap to be in
 * the correct order.
 */
void MinPriorityQ::decreaseKey(string id, int newKey) {
   int index = 0;
   for(std::vector<Element*>::iterator it = minHeap.begin();
         it != minHeap.end(); it++) {
      if((*it)->id == id) {
         (*it)->key = newKey;
         break;
      }
      index++;
   }
   while(index > 0 && minHeap[parent(index)]->key > minHeap[index]->key) {
      Element* temp = minHeap[index];
      minHeap[index] = minHeap[parent(index)];
      minHeap[parent(index)] = temp;
      index = parent(index);
   }
}

/*
 * @brief Extracts the element with the smallest key
 *
 * @return the string id of the Element with the smallest key
 *
 * Takes the first Element, swaps it with the last Element, then pops
 * the last Element off to reduce the list size. Then calls minHeapify
 * to reorder the remaining Elements.
 */
string MinPriorityQ::extractMin() {
   if(minHeap.size() == 0) {
      return "empty";
   }
   string min = minHeap[0]->id;
   minHeap[0] = minHeap[minHeap.size() - 1];
   minHeap.pop_back();
   minHeapify(0);
   return min;
}

/*
 * @brief Searches the tree to see if a specific id is there
 *
 * @param id a string containing the desired data to be searched for
 *
 * @return if id is found return true, otherwise return false
 *
 * Iterates through the vector minHeap, comparing each id to the given id.
 * If the end of the vector is reached without finding the given id, false
 * is returned.
 */
bool MinPriorityQ::isMember(string id) {
   for(std::vector<Element*>::iterator it = minHeap.begin();
         it != minHeap.end(); it++) {
      if((*it)->id == id) {
         return true;
      }
   }
   return false;
}

/*
 * @brief Builds the heap with the smallest Element key as the root
 *
 * @return nothing
 *
 * Swaps the first Element with an Element in the middle and calls
 * minHeapify to keep the heap in proper order.
 */
void MinPriorityQ::buildMinHeap() {
   for(int i = minHeap.size()/2; i >= 1; i--) {
      Element* temp = minHeap[0];
      minHeap[0] = minHeap[i];
      minHeap[i] = temp;
      minHeapify(0);
   }
}

/*
 * @brief Through key comparisons reorders the heap to keep the
 * Elements in proper order
 *
 * @param i an interger containing the starting point of the
 * comparisons
 *
 * @return nothing
 *
 * Swaps Elements as needed to have the smallest key at the root,
 * and then key values ascending from there.
 */
void MinPriorityQ::minHeapify(int i) {
   unsigned int l = left(i);
   unsigned int r = right(i);
   int smallest;
   if(l < minHeap.size() && minHeap[l]->key < minHeap[i]->key) {
      smallest = l;
   } else {
      smallest = i;
   }
   if(r < minHeap.size() && minHeap[r]->key < minHeap[smallest]->key) {
      smallest = r;
   }
   if(smallest != i) {
      Element* temp = minHeap[i];
      minHeap[i] = minHeap[smallest];
      minHeap[smallest] = temp;
      minHeapify(smallest);
   }
}

/*
 * @brief Gets the index of the parent of a given index
 *
 * @param i an integer containing the index of the Element
 * to find the parent of
 *
 * @return the index of the parent of the index given
 */
int MinPriorityQ::parent(int i) {
   int parent = floor(i/2);
   return parent;
}

/*
 * @brief Gets the index of the left Element of a given index
 *
 * @param i an integer containing the index of the Element
 * to find the left Element of
 *
 * @return the index of the left Element of the index given
 */
int MinPriorityQ::left(int i) {
   int left = 2 * i + 1;
   return left;
}

/*
 * @brief Gets the index of the right Element of a given index
 *
 * @param i an integer containing the index of the Element
 * to find the right Element of
 *
 * @return the index of the right Element of the index given
 */
int MinPriorityQ::right(int i) {
   int right = 2 * i + 2;
   return right;
}