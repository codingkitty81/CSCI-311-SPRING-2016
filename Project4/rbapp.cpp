/**
 * 
 */
 
#include "rbapp.h"
#include <sstream>
#include <iostream>

RBapp::RBapp() : done(false) {}

void RBapp::mainLoop() {
   while(done == false) {
      processCommand();
   }
}

void RBapp::processCommand() {
   //std::cout << "Enter a command: ";
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

void RBapp::processInsert(string& line) {
   int pos = line.find(' ');
   string key = line.substr(0, pos);
   line = line.substr(line.find_first_of(" \t")+1);
   myRBT.rbInsert(key, line);
}

void RBapp::processPrint() {
   myRBT.rbPrintTree();
}

void RBapp::processFind(string& key) {
   vector<const string*> foundList = myRBT.rbFind(key);
   for(vector<const string*>::iterator it = foundList.begin();
         it != foundList.end(); it += 2) {
            std::cout << *(*it) << " " << *(*it) << std::endl;
         }
}

void RBapp::processDelete(string& line) {
   int pos = line.find(' ');
   string key = line.substr(0, pos);
   line = line.substr(line.find_first_of(" \t")+1);
   myRBT.rbDelete(key, line);
}

void RBapp::processQuit() {
   done = true;
}

int main() {
   RBapp* myRBapp = new RBapp();
   myRBapp->mainLoop();
   return 0;
}