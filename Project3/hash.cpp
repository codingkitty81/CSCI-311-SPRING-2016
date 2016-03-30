/*
 * @file hash.cpp Builds and manipulates a Hash Table.
 *
 * @author Katherine Jouzapaitis
 * @date 3/30/2016
 *
 * Resources:
 * http://pumpkinprogrammer.com/2014/06/21/c-tutorial-intro-to-hash-tables/
 */

#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

/*
 * @brief Default constructor.
 * 
 * Sets collisions, longestList, and runningAvgListLength to 0.
 */
Hash::Hash() {
   collisions = 0;
   longestList = 0;
   runningAvgListLength = 0;
}

/*
 * @brief Removes a specific string from the hash table.
 * @param word, a string specified to be removed from the hash table.
 *
 * Uses the hash function to determine the index of the container
 * to search the list at that array for the given string. Upon
 * successful removal the runningAvgListLength will be recalculated.
 */
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

/*
 * @brief Prints the entire contents of the hash table.
 * 
 * Iterates through the containers, and then iterates through
 * each list printing each string of the list followed by a comma
 * and a space.
 */
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

/*
 * @brief Processes the input file to build a hash table.
 * @param fileName, a string containing the name of the file to be
 *          processed.
 *
 * Opens the given file name and while there is input being read will
 * call a hash function to get an index value to determine which container
 * the string should be added to by using push_back and will check for
 * collisions before each insert. After each insert averageItOut is
 * called to get the runningAvgListLength updated.
 */
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

/*
 * @brief Searches the hash table for a given string.
 * @param word, a string specified to be searched for.
 * @return if string is found return true, otherwise return false.
 * 
 * Uses the hash function on the given string to determine
 * the index of the container the string would be in.
 */
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

/*
 * @brief Prints the entire hash table to a file.
 * @param fileName, a string specifying the name of the file 
 * to be written to.
 *
 * Outputs the contents of the hash table by iterating through
 * the containers and then the list in each container.
 */
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

/*
 * @brief Prints the Total Collisions, Longest List Ever, Average List 
 *          Length Over Time, and the Load Factor of the hash table.
 *
 * Prints the collisions, longestList, runningAvgListLength, kept track
 * of throughout the program. Calculates and prints the load factor
 * for the final table.
 */
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

/*
 * @brief Averages out the length of the lists in the table
 *          and updates the runningAvgListLength.
 *
 * Computes the current list length by dividing the number of items
 * in the lists, by the number of nonempty lists, then updates the
 * running average by adding the running average to the current
 * average and dividing by two.
 */
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