/**
 * @file rbapp.h An application that stores information in a red-black tree.
 *
 * Note: put main() in rbapp.cpp - it should
 *                               - instantiate an RBapp
 *                               - call mainLoop()
 * @author Judy Challinger
 * @date 10/23/14
 **/

#ifndef CSCI_311_RBAPP_H
#define CSCI_311_RBAPP_H

#include <string>
#include "rbtree.h"

using std::string;

class RBapp {
    public:
        RBapp();                       // constructor
        void mainLoop();               // process commands until done
    private:
        RBTree myRBT;                  // the red black tree
        bool done;                     // flag for quit
        void processCommand();         // read and process one command
        void processInsert(string&);   // insert into red-black tree
        void processPrint();           // print tree
        void processFind(string&);     // find & print all occurances of a key
        void processDelete(string&);   // delete from the red-black tree
        void processQuit();
};

#endif // CSCI_311_RBAPP_H
