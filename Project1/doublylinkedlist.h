/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Katherine Jouzapaitis
 * @date 1/1/16
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {

 public:
   DoublyLinkedList();
   ~DoublyLinkedList();
   void append(T* data);
   bool empty() const { return (head == nullptr); }
   T* remove();
   T* first();
   T* next();

 private:
   class Node {
    public:
      Node();
      Node(T* data);
      Node* next;
      Node* prev;
      T* data;
   };
   Node* head;
   Node* tail;
   Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node() {

   // Your code here...
   next = prev = nullptr;
}

/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

   // Your code here...
   Node* toDelete = head;
   
   while (toDelete != nullptr) {
    head = head->next();
    delete toDelete;
    toDelete = head;
   }
   
   head = tail = current = nullptr;
}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

   // Your code here...
   head = tail = current = nullptr;
}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {

   // Your code here...
   current = new Node();
   current->data = data;
   
   if (head == nullptr) {
      head = current;
      current->next = nullptr;
      current->prev = nullptr;
   } else {
      tail = head;
    
      while (tail->next != nullptr) {
         tail = tail->next;
      }
    
      tail->next = current;
      current->prev = tail;
      current->next = nullptr;
   }
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {

   // Your code here...
   current = head;
   
   if (head == nullptr) {
      return (nullptr);
   } else {
      return (head->data);
   }
}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {

   // Your code here...
   if (current->next != nullptr) {
      current = current->next;
      return (current->data);
   } else {
      return (nullptr);
   }
   
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {

   // Your code here...
   Node* tempNode = current;
   
   if (head == nullptr || current == nullptr) {
      return (nullptr);
   }
   
   if (current == head) {
      if (current->next != nullptr) {
         head = current = current->next;
         head->prev = nullptr;
         current->prev = nullptr;
         delete tempNode;
         return (current->data);
      } else {
         head = current = nullptr;
         return (nullptr);
      }
   }
   
   if (current->next == nullptr) {
      tail = current;
      current = current->prev;
      delete tail;
      tail = current;
      tail->next = current->next = nullptr;
      return (nullptr);
   } else {
      Node* prevNode = current->prev;
      current = current->next;
      tempNode->next = tempNode->prev = nullptr;
      prevNode->next = current;
      current->prev = prevNode;
      delete tempNode;
      return (current->data);
   }
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
