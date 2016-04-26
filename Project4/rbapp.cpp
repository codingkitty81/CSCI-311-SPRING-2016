/*
 * @file rbapp.cpp An application to process commands either
 * by command line or from file using stdin.
 *
 * @brief Processes commands using stdin. Commands can be entered
 * either manually or from a file, and will stop processing
 * either at the quit command or when the file has reached its end.
 *
 * @author Katherine Jouzapaitis
 * @date 04/20/2016
 */
 
#include "rbapp.h"
#include <sstream>
#include <iostream>

/*
 * @brief Default constructor
 *
 * Constructs a RBapp to process commands for a red-black tree
 * with done set to false as default.
 */
RBapp::RBapp() : done(false) {}

/*
 * @brief Calls processCommand while done is false.
 *
 * @return nothing
 */
void RBapp::mainLoop() {
   while(done == false) {
      processCommand();
   }
}

/*
 * @brief Routes commands to the proper processing functions
 *
 * @return nothing
 *
 * Takes commands either through command line or from file and
 * routes those commands to the proper process function. If read
 * from a file if the end is reached done will be set to true.
 */
void RBapp::processCommand() {
   std::string line;
   getline(std::cin, line);
   std::istringstream input(line);
   std::string command;
   input >> command;
   line = line.substr(line.find_first_of(" \t")+1);
   if(command == "insert") {
      processInsert(line);
   } else if(command == "print") {
      processPrint();
   } else if(command == "find") {
      processFind(line);
   } else if(command == "delete") {
      processDelete(line);
   } else if(command == "quit") {
      processQuit();
   } else {
      done = true;
   }
}

/*
 * @brief Processes the info passed in to properly call rbInsert
 *
 * @param line a reference to a string of information to be used
 * for a call to rbInsert
 *
 * @return nothing
 *
 * Divides line into key and value parts for the rbInsert function
 * call.
 */
void RBapp::processInsert(string& line) {
   int pos = line.find(' ');
   string key = line.substr(0, pos);
   line = line.substr(line.find_first_of(" \t")+1);
   myRBT.rbInsert(key, line);
}

/*
 * @brief Calls the print function on the red-black tree
 *
 * @return nothing
 */
void RBapp::processPrint() {
   myRBT.rbPrintTree();
}

/*
 * @brief Processes the info passed in to properly call rbFind
 *
 * @param key a reference to a string of the key to be searched for
 *
 * @return nothing
 *
 * Calls rbFind on a given key and makes a list of all of the 
 * instances of that key found in the tree. Once the list is made,
 * it is iterated through and using std::cout the key and value
 * of every instance found is printed.
 */
void RBapp::processFind(string& key) {
   vector<const string*> foundList = myRBT.rbFind(key);
   for(vector<const string*>::iterator it = foundList.begin();
         it != foundList.end(); it++) {
            std::cout << *(*it) << " ";
            it++;
            std::cout << *(*it) << std::endl;
         }
}

/*
 * @brief Processes the info passed in to properly call rbDelete
 *
 * @param line a reference to a string containing the key and
 * value of a node to be deleted from the tree
 *
 * @return nothing
 *
 * Line is taken apart to get the kay and value needed to properly
 * call the rbDelete function.
 */
void RBapp::processDelete(string& line) {
   int pos = line.find(' ');
   string key = line.substr(0, pos);
   line = line.substr(line.find_first_of(" \t")+1);
   myRBT.rbDelete(key, line);
}

/*
 * @brief Sets done to true to terminate RBapp processing
 *
 * @return nothing
 */
void RBapp::processQuit() {
   done = true;
}

/*
 * @brief Main function of rbapp.cpp
 *
 * Creates a new RBapp, starts the mainLoop to process commands,
 * then deletes the RBapp to free up any memory used.
 */
int main() {
   RBapp* myRBapp = new RBapp();
   myRBapp->mainLoop();
   delete myRBapp;
   return 0;
}