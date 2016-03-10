/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger
 * @date 2/22/13
 * 
 * @author Katherine Jouzapaitis
 * @date 3/10/2016
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include "CensusData.h"

/*
 * @brief
 *    Insertion Sort of vector generated from input file.
 * @param   type An integer identifying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @return Nothing.
 *
 * Sorts vector by storing the current Record and comparing it to other records
 * and then inserting that record in front of the first Record it finds which
 * is larger than itself.
 */
void CensusData::insertionSort(int type) {
   //Establish end point for iteration.
   int vecSize = this->getSize();
   
   for(int j = 1; j < vecSize; j++) {
      Record* key = this->data[j];
      int i = j-1;
         while(i > -1 && !isSmaller(type, data[i], key)) {
            data[i+1] = data[i];
            i = i-1;
         }
      data[i+1] = key;
   }
}
/*
 * @brief
 *    Merge Sort of vector generated from file by calling helper function.
 * @param   type An integer identifying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @return Nothing.
 *
 * Calls helper function merge_sort after establishing begin (p) and end (r)
 * points for the sort to utilize.
 */
void CensusData::mergeSort(int type) {
   int p = 0;
   int r = this->getSize() - 1;
   merge_sort(type, p, r);
}

/*
 * @brief
 *    Helper function for mergeSort.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   p An integer defining the beginning of the vector being sorted.
 * @param   r An integer defining the end of the vector being sorted.
 * @return  Nothing.
 *
 * Handles the dividing portion of the divide and conquer style of how
 * Merge Sort operates. Recursively calls merge_sort until base cases are
 * established, then calls merge.
 */
void CensusData::merge_sort(int type, int p, int r) {
   if(p < r) {
      int q = floor((p + r)/2);
      merge_sort(type, p, q);
      merge_sort(type, q + 1, r);
      merge(type, p, q, r);
   }
}

/*
 * @brief
 *    Merges divided up vectors back together in ascending order.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   p An integer defining the beginning of the vector being sorted.
 * @param   q An integer defining the mid point of the vector being sorted.
 * @param   r An integer defining the end of the vector being sorted.
 * @return  Nothing.
 *
 * Creates vectors to handle data on the left and right sides of the mid
 * point, then does comparisons of Records before repopulating the original
 * vector with Records in ascending order.
 */
void CensusData::merge(int type, int p, int q, int r) {
   int point1 = q - p + 1;
   int point2 = r - q;
   
   //Create temp vectors for left and right of q
   vector<Record*> leftSide;
   vector<Record*> rightSide;
      
   //Populate the temp vectors
   for(int i = 0; i < point1; i++) {
      leftSide.push_back(this->data[p + i]);
   }
      
   for(int j = 0; j < point2; j++) {
      rightSide.push_back(this->data[q + j + 1]);
   }
   
   //Establish index counters for different vectors
   int i = 0;
   int j = 0;
   int k = p;
   
   while(i < point1 && j < point2) {
      if(isSmaller(type, leftSide[i], rightSide[j])) {
         data[k] = leftSide[i];
         i++;
      } else {
         data[k] = rightSide[j];
         j++;
      }
      k++;
   }
   
   //Populate any remaining from leftSide
   while(i < point1) {
      data[k] = leftSide[i];
      i++;
      k++;
   }
   
   //Populate any remaining from rightSide
   while(j < point2) {
      data[k] = rightSide[j];
      j++;
      k++;
   }
}

/*
 * @brief
 *    Quick Sort of vector generated from file by calling helper function.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @return Nothing.
 *
 * Calls helper function randomized_quickSort after establishing begin (p)
 * and end (r) points for the sort to utilize.
 */
void CensusData::quickSort(int type) {
   int p = 0;
   int r = this->getSize() - 1;
   
   randomized_quickSort(type, p, r);
}

/*
 * @brief
 *    Helper function for quickSort.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   p An integer defining the beginning of the vector being sorted.
 * @param   r An integer defining the end of the vector being sorted.
 * @return  Nothing.
 *
 * Handles the division of the orginal vector utilizing randomized
 * partitions to establish mid point (pivot) for the recursive calls
 * to randomized_quickSort.
 */
void CensusData::randomized_quickSort(int type, int p, int r) {
   if(p < r) {
      int q = randomized_partition(type, p, r);
      randomized_quickSort(type, p, q - 1);
      randomized_quickSort(type, q + 1, r);
   }
}

/*
 * @brief
 *    Establishes the pivot point of the vector randomly.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   p An integer defining the beginning of the vector being sorted.
 * @param   r An integer defining the end of the vector being sorted.
 * @return  the results of call to partition.
 *
 * Randomly chooses an index from the available Records, swaps the
 * selected record with the end Record (r), then calls partition with
 * the new end Record.
 */
int CensusData::randomized_partition(int type, int p, int r) {
   //Seed the random engine.
   std::default_random_engine parValue(time(0));
   //Sets limits to the random engine so nothing out of scope can be
   //chosen.
   std::uniform_int_distribution<int> dist(p, r);
   
   int i = dist(parValue);
   Record* temp = data[r];
   data[r] = data[i];
   data[i] = temp;
   return partition(type, p, r);
}
/*
 * @brief
 *    Sorts the vector into two partitions. One partition of Records lesser
 *    than the end Record, and one of Records greater than.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   p An integer defining the beginning of the vector being sorted.
 * @param   r An integer defining the end of the vector being sorted.
 * @return  the index position of the pivot.
 *
 * Through comparision to the end Record, i moves along the vector with
 * Records lesser than the end Record to the left of position i and Records
 * greater than at the right of position i. The end Record then gets moved
 * to position i + 1, as it is the pivot point of the vector.
 */
int CensusData::partition(int type, int p, int r) {
   Record* x = data[r];
   int i = p - 1;
   for(int j = p; j < r; j++) {
      if(isSmaller(type, data[j], x)) {
         i++;
         Record* temp = data[i];
         data[i] = data[j];
         data[j] = temp;
      }
   }
   Record* temp2 = data[i + 1];
   data[i + 1] = data[r];
   data[r] = temp2;
   return (i + 1);
}

/*
 * @brief
 *    Compares two Records.
 * @param   type An integer identitying the desired sort to be by Population
 *          (0) or by City Name (1).
 * @param   left A pointer to the Record to the left of the comparison.
 * @param   right A pointer to the Record to the right of the comparison.
 * @return  true if the left Record is lesser than or equal to the right
 *          Record, otherwise return false.
 *
 * Compares two Records, either by Population or City Name as specified by
 * by the type passed in, then returns true or false.
 */
bool CensusData::isSmaller(int type, Record* left, Record* right) {
   if(type == 0) {
      return (left->population <= right->population);
   } else {
      return (*(left->city) <= *(right->city));
   }
}