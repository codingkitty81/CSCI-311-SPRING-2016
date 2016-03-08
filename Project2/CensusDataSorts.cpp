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
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include "CensusData.h"

// formal parameter name commented out to avoid unused variable warning
void CensusData::insertionSort(int type) {
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

// formal parameter name commented out to avoid unused variable warning
void CensusData::mergeSort(int type) {
   int begin = 0;
   int end = this->getSize() - 1;
   merge_sort(type, begin, end);
}

void CensusData::merge_sort(int type, int begin, int end) {
   if(begin < end) {
      int midPoint = floor((begin + end)/2);
      merge_sort(type, begin, midPoint);
      merge_sort(type, midPoint + 1, end);
      merge(type, begin, midPoint, end);
   }
}

void CensusData::merge(int type, int begin, int midPoint, int end) {
   int point1 = midPoint - begin + 1;
   int point2 = end - midPoint;
   
   //Create temp vectors for left and right of midpoint
   vector<Record*> leftSide;
   vector<Record*> rightSide;
      
   //Populate the temp vectors
   for(int i = 0; i < point1; i++) {
      leftSide.push_back(this->data[begin + i]);
   }
      
   for(int j = 0; j < point2; j++) {
      rightSide.push_back(this->data[midPoint + j + 1]);
   }
   
   //Establish index counters for different vectors
   int i = 0;
   int j = 0;
   int k = begin;
   
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

// formal parameter name commented out to avoid unused variable warning
void CensusData::quickSort(int type) {
   int p = 0;
   int r = this->getSize() - 1;
   
   randomized_quickSort(type, p, r);
}

void CensusData::randomized_quickSort(int type, int p, int r) {
   if(p < r) {
      int q = randomized_partition(type, p, r);
      randomized_quickSort(type, p, q - 1);
      randomized_quickSort(type, q + 1, r);
   }
}

int CensusData::randomized_partition(int type, int p, int r) {
   std::default_random_engine parValue(time(0));
   std::uniform_int_distribution<int> dist(p, r);
   
   int i = dist(parValue);
   Record* temp = this->data[r];
   data[r] = data[i];
   data[i] = temp;
   return partition(type, p, r);
}

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

bool CensusData::isSmaller(int type, Record* left, Record* right) {
   if(type == 0) {
      return (left->population <= right->population);
   } else {
      return (*(left->city) <= *(right->city));
   }
}