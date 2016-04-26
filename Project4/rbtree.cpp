/**
 * @file rbtree.cpp An application that stores information in a red-black tree.
 * 
 * @brief Creates a red-black tree with nodes containing a color, a string key,
 * and a string value. The tree can contain duplicates. When delete is called
 * all instances will be searched for and deleted. Keys can be searched for
 * and printed out.
 * 
 * @author Judy Challinger
 * @author Katherine Jouzapaitis
 * @date 04/20/2016
 * 
 * Resources: http://ideone.com/mr7juv
 */

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;
using std::string;

/*
 * @brief Default constructor
 *
 * Creates new instances of nil and root. Sets the color of nil
 * and assigns the pointers to nil.
 */
RBTree::RBTree() {
   nil = new Node();
   nil->color = 'B';
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = new Node();
   root = nil;
}

/*
 * @brief Destructor
 *
 * Goes through the tree and deletes the nodes, once all the nodes
 * have been deleted nodes root and nil get deleted as well.
 */
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

/*
 * @brief Public function to access the private rbInsert function
 *
 * @param key a reference to a string containing information which
 * is used to determine where in the tree it should go
 * @param value a reference to a string containing information which
 * is associated with the key
 *
 * @return Nothing
 *
 * Creates a new node using the key and value parameters passed in,
 * then calls the private rbInsert function passing the node along.
 */
void RBTree::rbInsert(const string& key, const string& value) {
   Node* z = new Node(key, value, nil);
   rbInsert(z);
}

/*
 * @brief Public function to access the private rbDelete function
 *
 * @param key a reference to a string containing information which
 * is used to determine where in the tree it might be
 * @param value a reference to a string containing information which
 * is associated with the key
 *
 * @return Nothing
 *
 * Searches the tree for nodes with matching key and value, and
 * creates a list of all instances of matching nodes. The list is
 * then used to call the private rbDelete function with the node
 * passed along.
 */
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

/*
 * @brief Finds nodes that contain a specified key amd then makes
 * a list of all the nodes matching that key
 *
 * @param key a reference to a string specifying what key to be
 * searched for in the tree
 *
 * @return a vector list of keys and values matching the specified
 * key that was searched for
 *
 * Searches the tree for all nodes with the matching key and then
 * puts the found node's key and value into a vector. Each one found
 * gets added to the end of the list.
 */
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

/*
 * @brief Calls the private function for printing out the nodes
 * of the red-black tree
 * 
 * @return Nothing
 *
 * Calls the private function for printing out the nodes of the
 * red-black tree in reverse order, passing in the root node of the
 * tree and the starting depth of 0 to grab the entire tree.
 */
void RBTree::rbPrintTree() {
   reverseInOrderPrint(root, 0);
}

/*
 * @brief Default node constructor
 *
 * Creates a new node with all attributes set to nullptr and color
 * set to red.
 */
RBTree::Node::Node() {
   key = nullptr;
   value = nullptr;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
   color = 'R';
}

/*
 * @brief Overloaded node constructor
 *
 * @param key a reference to a string containing the key which
 * helps determine where in the tree the node will be placed
 * @param value a reference to a string containing the value to
 * associated with the particular key
 * @param s a pointer to nil
 *
 * Creates a new node with attributes dictated by the parameters
 * passed in and the color set to red.
 */
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

/*
 * @brief Destructor
 *
 * Sets parent, right, and left to nullptr, then deletes key and
 * value to free up memory.
 */
RBTree::Node::~Node() {
   parent = right = left = nullptr;
   delete key;
   delete value;
}

/*
 * @brief Finds the node with smallest key amongst the children
 * of the node provided
 *
 * @param x a pointer to the node whose children will be searched
 * to find the smallest key
 *
 * @return a pointer to the node with the smallest key of the
 * children examined
 *
 * Goes down the tree of left children from the node given to find
 * the smallest key.
 */
RBTree::Node* RBTree::rbTreeMinimum(Node* x) {
   while(x->left != nil) {
      x = x->left;
   }
   return x;
}

/*
 * @brief Finds the node with the largest key amongst the children
 * of the node provided
 *
 * @param x a pointer to the node whose children will be searched
 * to find the largest key
 *
 * @return a pointer to the node with the largest key of the
 * children examined
 *
 * Goes down the tree of the right children from the node given to
 * find the largest key.
 */
RBTree::Node* RBTree::rbTreeMaximum(Node* x) {
   while(x->right != nil) {
      x = x->right;
   }
   return x;
}

/*
 * @brief Finds the successor to a given node
 *
 * @param x a pointer to the node whose children will be searched
 * to find the successor (smallest key of the right child)
 *
 * @return a pointer to the node that is the successor
 *
 * Goes down the given nodes' branch of right children to find the
 * smallest key to use as the successor to the given node.
 */
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

/*
 * @brief Finds the predecessor to a given node
 *
 * @param x a pointer to the node whose children will be searched
 * to find the predecessor (largest key of the left child)
 *
 * @return a pointer to the node that is the predecessor
 *
 * Goes down the given nodes' branch of left children to find the
 * largest key to use as the predecessor to the given node.
 */
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

/*
 * @brief Searches the tree for an instance of a given key
 *
 * @param root a pointer to the root of the tree to make sure the
 * entire tree gets searched.
 * @param key a reference to a string that will be used for
 * comparison purposes
 *
 * @return a pointer to a node with a matching key
 *
 * Searches through the tree comparing the given key to the key of
 * each node until a match is found. If no match is found does nothing.
 */
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

/*
 * @brief Prints the tree in reverse order
 *
 * @param x a pointer to node where the printing of the tree is 
 * designed to start
 * @param depth an integer dictating at what level of the tree the
 * printing is to start
 *
 * @return nothing
 *
 * Goes through the tree starting a given node and depth and prints it
 * in reverse order, making the tree appear to be sideways.
 */
void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/*
 * @brief Performs a left rotation on the subtree of a given node
 *
 * @param x a pointer to a node for where a rotation will occur
 *
 * @return nothing
 *
 * Rotates the subtree of a given node to help balance out a tree.
 */
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

/*
 * @brief Performs a right rotation on the subtree of a given node
 *
 * @param x a pointer to a node for where a rotation will occur
 *
 * @return nothing
 *
 * Rotates the subtree of a given node to help balance out a tree.
 */
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

/*
 * @brief Fixes up the tree after an insert is made to keep the tree
 * properties correct and true
 *
 * @param z a pointer to the node that was just inserted
 *
 * @return nothing
 *
 * After a node is inserted into the tree the nodes leading to the
 * node are checked for color and the balance of the tree is checked.
 * Rotates are performed if necessary.
 */
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

/*
 * @brief Fixes up the tree after a deletion is performed.
 *
 * @param x a pointer to the node that took the place of the
 * deleted node
 * 
 * @return nothing
 *
 * Goes through the tree and performs rotates and color changes
 * as necessary to make sure the tree conforms to all the
 * red-black tree rules.
 */
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

/*
 * @brief Exchanges one node with another
 * 
 * @param u a pointer to the node to be swapped out of the tree
 * @param v a pointer to the node to take the place of the
 * desired node
 *
 * @return nothing
 *
 * Swaps out node u for node v.
 */
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

/*
 * @brief Inserts a node into the tree
 *
 * @param z a pointer to the node to be inserted into the tree
 *
 * @return nothing
 *
 * Inserts a node into the tree following the rules of a binary
 * search tree, then calls InsertFixup to get the rest of the tree
 * in line with the red-black tree requirements.
 */
void RBTree::rbInsert(Node* z) {
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

/*
 * @brief Deletes a given node from the tree
 *
 * @param z a pointer to the node to be deleted from the tree
 *
 * @return nothing
 *
 * Goes through the tree for the node to be deleted. Performs
 * a transplant to get the correct node into the place of the
 * node to be deleted. Uses the predecessor when the node to
 * be deleted has two children.
 */
void RBTree::rbDelete(Node* z) {
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
   delete z;
}