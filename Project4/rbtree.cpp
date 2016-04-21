
// rbtree.cpp 
// 20.04.2016

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;
using std::string;

RBTree::RBTree() {
   nil = new Node();
   nil->color = 'B';
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = new Node();
   root = nil;
}

RBTree::~RBTree() {
   while(root->right != nil || root->left != nil) {
      if(root->right != nil) {
         rbDelete(root->right);
      }
      if(root->left != nil) {
         rbDelete(root->left);
      }
   }
   delete root;
   delete nil;
}

void RBTree::rbInsert(const string& key, const string& value) {
   Node* z = new Node(key, value, nil);
   rbInsert(z);
}

void RBTree::rbDelete(const string& key, const string& value) {
   vector<Node*> dupKeyList;
    Node *listStart = rbTreeSearch(root, key);
    if(listStart != nil)
    {
        Node *node = listStart;
        while((node != nil) && (*node->key == key))
        {
            dupKeyList.push_back(node);
            node = rbTreeSuccessor(node);
        }
        node = rbTreePredecessor(listStart);
        while((node != nil) && (*node->key == key))
        {
            dupKeyList.push_back(node);
            node = rbTreePredecessor(node);
        }
    }
    for(vector<Node*>::iterator it = dupKeyList.begin();
        it != dupKeyList.end(); ++it)
    {
        if(*((*it)->value) == value)
        {
            rbDelete(*it);
        }
    }
}

vector<const string*> RBTree::rbFind(const string& key) {
   vector<const string*> nodeList;
   Node* listStart = rbTreeSearch(root, key);
   if(listStart != nil) {
      Node* node = listStart;
      while(node != nil && *(node->key) == key) {
         nodeList.push_back(node->key);
         nodeList.push_back(node->value);
         node = rbTreeSuccessor(node);
      }
      node = rbTreePredecessor(listStart);
      while(node != nil && *(node->key) == key) {
         nodeList.push_back(node->key);
         nodeList.push_back(node->value);
         node = rbTreePredecessor(node);
      }
   }
   return nodeList;
}

void RBTree::rbPrintTree() {
   reverseInOrderPrint(root, 0);
}

RBTree::Node::Node() {
   key = nullptr;
   value = nullptr;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = 'R';
}

RBTree::Node::Node(const string& key, const string& value, Node* s) {
   string* tempKey = new string(key);
   string* tempValue = new string(value);
   this->key = tempKey;
   this->value = tempValue;
   this->parent = s;
   this->right = s;
   this->left = s;
   this->color = 'R';
}

RBTree::Node::~Node() {
   parent = right = left = nullptr;
   delete key;
   delete value;
}

RBTree::Node* RBTree::rbTreeMinimum(Node* x) {
   while(x->left != nil) {
      x = x->left;
   }
   return x;
}

RBTree::Node* RBTree::rbTreeMaximum(Node* x) {
   while(x->right != nil) {
      x = x->right;
   }
   return x;
}

RBTree::Node* RBTree::rbTreeSuccessor(Node* x) {
   if(rbTreeSearch(root, *x->key) == nil) {
      return x;
   }
   if(x->right != nil) {
      return rbTreeMinimum(x->right);
   }
   Node* temp = x->parent;
   while(temp != nil && x == temp->right) {
      x = temp;
      temp = temp->parent;
   }
   return temp;
}

RBTree::Node* RBTree::rbTreePredecessor(Node* x) {
   if(rbTreeSearch(root, *x->key) == nil) {
      return x;
   }
   if(x->left != nil) {
      return rbTreeMaximum(x->left);
   }
   Node* temp = x->parent;
   while(temp != nil && x == temp->left) {
      x = temp;
      temp = temp->parent;
   }
   return temp;
}

RBTree::Node* RBTree::rbTreeSearch(Node* root, const string& key) {
   if(root == nil || *(root->key) == key) {
      return root;
   }
   if(key < *(root->key)) {
      return rbTreeSearch(root->left, key);
   } else {
      return rbTreeSearch(root->right, key);
   }
}

void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

void RBTree::leftRotate(Node* x) {
   Node* y = x->right;
   x->right = y->left;
   if(y->left != nil) {
      y->left->parent = x;
   }
   y->parent = x->parent;
   if(x->parent == nil) {
      root = y;
   } else if(x == x->parent->left) {
      x->parent->left = y;
   } else {
      x->parent->right = y;
   }
   y->left = x;
   x->parent = y;
}

void RBTree::rightRotate(Node* x) {
   Node* y = x->left;
   x->left = y->right;
   if(y->right != nil) {
      y->right->parent = x;
   }
   y->parent = x->parent;
   if(x->parent == nil) {
      root = y;
   } else if(x == x->parent->right) {
      x->parent->right = y;
   } else {
      x->parent->left = y;
   }
   y->right = x;
   x->parent = y;
}

void RBTree::rbInsertFixup(Node* z) {
   Node* y;
   while(z->parent->color == 'R') {
      if(z->parent == z->parent->parent->left) {
         y = z->parent->parent->right;
         if(y->color == 'R') {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         } else {
            if(z == z->parent->right) {
               z = z->parent;
               leftRotate(z);
            }
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            rightRotate(z->parent->parent);
         }
      } else {
         y = z->parent->parent->left;
         if(y->color == 'R') {
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
         } else {
            if(z == z->parent->left) {
               z = z->parent;
               rightRotate(z);
            }
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            leftRotate(z->parent->parent);
         }
      }
   }
   root->color = 'B';
}

void RBTree::rbDeleteFixup(Node* x) {
   while(x != root && x->color == 'B') {
      Node* w;
      if(x == x->parent->left) {
         w = x->parent->right;
         if(w->color == 'R') {
            w->color = 'B';
            x->parent->color = 'R';
            leftRotate(x->parent);
            w = x->parent->right;
         }
         if(w->left->color == 'B' && w->right->color == 'B') {
            w->color = 'R';
            x = x->parent;
         } else {
            if(w->right->color == 'B') {
               w->left->color = 'B';
               w->color = 'R';
               rightRotate(w);
               w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->right->color = 'B';
            leftRotate(x->parent);
            x = root;
         }
      } else {
        w = x->parent->left;
        if(w->color == 'R') {
           w->color = 'B';
           x->parent->color = 'R';
           rightRotate(x->parent);
           w = x->parent->left;
        }
        if(w->right->color == 'B' && w->left->color == 'B') {
           w->color = 'R';
           x = x->parent;
        } else {
           if(w->left->color == 'B') {
              w->right->color = 'B';
              w->color = 'R';
              leftRotate(w);
              w = x->parent->left;
           }
           w->color = x->parent->color;
           x->parent->color = 'B';
           w->left->color = 'B';
           rightRotate(x->parent);
           x = root;
         }
      }
   }
   x->color = 'B';
}

void RBTree::rbTransplant(Node* u, Node* v) {
   if(u->parent == nil) {
      root = v;
   } else if(u == u->parent->left) {
      u->parent->left = v;
   } else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

void RBTree::rbInsert(Node* z) {
   if(root == nullptr) {
      root = z;
      root->left = nil;
      root->right = nil;
      root->parent = nil;
      root->color = 'B';
   } else {
      Node* y = nil;
      Node* x = root;
      while(x != nil) {
         y = x;
         if(*(z->key) < *(x->key)) {
            x = x->left;
         } else {
            x = x->right;
         }
      }
      z->parent = y;
      if(y == nil) {
         root = z;
      } else if(*(z->key) < *(y->key)) {
         y->left = z;
      } else {
         y->right = z;
      }
      z->left = nil;
      z->right = nil;
      z->color = 'R';
      rbInsertFixup(z);
   }
}

void RBTree::rbDelete(Node* z) {
   if(root == nullptr) {
      //do nothing
      return;
   }
   
   if(rbTreeSearch(root, *z->key) == nil) {
      return;
   }
   
   Node* x;
   Node* y = z;
   char yColor = y->color;
   if(z->left == nil) {
      x = z->right;
      rbTransplant(z, x);
   } else if(z->right == nil) {
      x = z->left;
      rbTransplant(z, x);
   } else {
      //Uses successor
      /*
      y = rbTreeMinimum(z->right);
      yColor = y->color;
      x = y->right;
      if(y->parent == z) {
         x->parent = y;
      } else {
         rbTransplant(y, x);
         y->right = z->right;
         y->right->parent = y;
      }
      rbTransplant(z,y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
      */
      //Uses predecessor
      y = rbTreeMaximum(z->left);
      yColor = y->color;
      x = y->left;
      if(y->parent == z) {
         x->parent = y;
      } else {
         rbTransplant(y, x);
         y->left = z->left;
         y->left->parent = y;
      }
      rbTransplant(z,y);
      y->right = z->right;
      y->right->parent = y;
      y->color = z->color;
   }
   if(yColor == 'B') {
      rbDeleteFixup(x);
   }
}