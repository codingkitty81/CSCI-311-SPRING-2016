/*
 *
 *
 * Resources:
 * http://pumpkinprogrammer.com/2014/06/21/c-tutorial-intro-to-hash-tables/
 */

#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

Hash::Hash() {
   collisions = 0;
   longestList = 0;
   runningAvgListLength = 0;
}

void Hash::remove(string word) {
   int index = hf(word);
   for(list<string>::iterator it = hashTable[index].begin();
         it != hashTable[index].end(); it++) {
      if(*it == word) {
         hashTable[index].remove(word);
         averageItOut();
         break;
      }
   }
}

void Hash::print() {
   for(int i = 0; i < HASH_TABLE_SIZE; i++) {
      std::cout << i << ":\t";
      for(list<string>::iterator it = hashTable[i].begin();
            it != hashTable[i].end(); it++) {
              std::cout << *it << ", ";
            }
      std::cout << "\n";
   }
}

void Hash::processFile(string fileName) {
   string line;
   std::ifstream newFile;
   newFile.open(fileName);
   if(newFile.is_open()) {
      while(getline(newFile, line)) {
         int index = hf(line);
         if(!hashTable[index].empty()) {
            collisions++;
         }
         hashTable[index].push_back(line);
         averageItOut();
         for(int i = 0; i < HASH_TABLE_SIZE; i++) {
            if(hashTable[i].size() > longestList) {
               longestList = hashTable[i].size();
            }
         }
      }
   }
   newFile.close();
}

bool Hash::search(string word) {
   int index = hf(word);
   for(list<string>::iterator it = hashTable[index].begin();
         it != hashTable[index].end(); it++) {
      if(*it == word) {
         return true;
      }
   }
   return false;
}

void Hash::output(string fileName) {
   std::ofstream newFile;
   newFile.open(fileName);
   for(int i = 0; i < HASH_TABLE_SIZE; i++) {
      newFile << i << ":\t";
      for(list<string>::iterator it = hashTable[i].begin();
            it != hashTable[i].end(); it++) {
               newFile << *it << ", ";
            }
      newFile << std::endl;  
   }
   newFile.close();
}

void Hash::printStats() {
   std::cout << "Total Collisions = " << collisions << "\n";
   std::cout << "Longest List Ever = " << longestList << "\n";
   std::cout << "Average List Length Over Time = " 
                  << runningAvgListLength << "\n";
   double load = 0;
   int itemsInLists = 0;
      for(int i = 0; i < HASH_TABLE_SIZE; i++) {
         if(hashTable[i].size() > 0) {
            itemsInLists = itemsInLists + hashTable[i].size();
         }
      }
   load = ((double)itemsInLists) / ((double)HASH_TABLE_SIZE);
   std::cout << "Load Factor = " << load << "\n";
}

void Hash::averageItOut() {
   int nonEmptyLists = 0;
   int itemsInLists = 0;
   for(int i = 0; i < HASH_TABLE_SIZE; i++) {
      if(hashTable[i].size() > 0) {
         nonEmptyLists++;
         itemsInLists = itemsInLists + hashTable[i].size();
      }
   }
   double currentListAvg = ((double)itemsInLists) / ((double)nonEmptyLists);
   runningAvgListLength = (runningAvgListLength + currentListAvg)/2;
}