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
#include "CensusData.h"

// formal parameter name commented out to avoid unused variable warning
void CensusData::insertionSort(int type) {
   int vecSize = this->data.size();
   
   if(type == 0) {
      for(int j = 1; j < vecSize; j++) {
         Record* key = this->data[j];
         int i = j-1;
            while(i > -1 && this->data[i]->population > key->population) {
               data[i+1] = data[i];
               i = i-1;
            }
         data[i+1] = key;
      }
   } else {
      for(int j = 1; j < vecSize; j++) {
         Record* key = this->data[j];
         int i = j-1;
            while(i > -1 && *(this->data[i]->city) > *(key->city)) {
               data[i+1] = data[i];
               i = i-1;
            }
         data[i+1] = key;
      }
   }
   
}

// formal parameter name commented out to avoid unused variable warning
void CensusData::mergeSort(int type) {
   if(type == 0) {
      
   }
}

// formal parameter name commented out to avoid unused variable warning
void CensusData::quickSort(int /*type*/) {
}
