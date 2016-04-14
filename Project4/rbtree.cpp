// rbtree.cpp 

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

RBTree::RBTree() {}

RBTree::~RBTree() {}

void RBTree::rbInsert(const string& key, const string& value) {}

void RBTree:: rbDelete(const string& key, const string& value) {}

vector<const string*> RBTree::rbFind(const string& key) {}

RBTree::Node::Node() {}

RBTree::Node::Node(const string& key, const string& value, Node* nilPt) {}

RBTree::Node::~Node() {}

Node* RBTree::rbTreeMinimum(Node* ) {}

Node* RBTree::rbTreeMaximum(Node* ) {}

Node* RBTree::rbTreeSuccessor(Node* ) {}

Node* RBTree::rbTreePredecessor(Node* ) {}

Node* RBTree::rbTreeSearch(Node* , const string& key) {}

void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

void RBTree::leftRotate(Node* ) {}

void RBTree::rightRotate(Node* ) {}

void RBTree::rbInsertFixup(Node* ) {}

void RBTree::rbDeleteFixup(Node* ) {}

void RBTree::rbTransplant(Node* , Node* ) {}

void RBTree::rbInsert(Node* ) {}

void RBTree::rbDelete(Node* ) {}