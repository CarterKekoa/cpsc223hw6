// Carter Mooring
// Dr. Bowers
// CPSC 223
// Oct. 30th, 2019
// linked_list_collection.h
// This code sorts linked lists using merge, quick, and insertion sort

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

template <typename K, typename V>
class LinkedListCollection : public Collection <K ,V>{
public :

    // create an empty linked list
    LinkedListCollection();

    // copy a linked list
    LinkedListCollection(const LinkedListCollection <K,V >& rhs);

    // assign a linked list
    LinkedListCollection <K,V>& operator=(const LinkedListCollection <K,V>& rhs);

    // delete a linked list
    ~LinkedListCollection();

    // insert a key - value pair into the collection
    void insert(const K& key, const V& val);

    // remove a key - value pair from the collection
    void remove(const K& key);

    // find the value associated with the key
    bool find(const K& key, V& val) const;

    // find the keys associated with the range
    void find(const K& k1, const K& k2, std::vector<K>& keys) const;

    // return all keys in the collection
    void keys(std::vector <K>& keys) const ;

    // return collection keys in sorted order
    void sort(std::vector <K>& keys) const ;

    // return the number of keys in collection
    int size() const ;

    // in place sorting
    void insertion_sort();
    void merge_sort();
    void quick_sort();

    private :
        // linked list node structure
        struct Node {
            K key ;
            V value ;
            Node* next ;
        };
        Node* head ; // pointer to first list node
        Node* tail ; // pointer to last list node
        int length ; // number of linked list nodes in list

        // merge sort helper
        Node* merge_sort(Node* left, int len);

        // quick sort helper
        Node* quick_sort(Node* start, int len);
    };

// create an empty linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection() {
  head = nullptr;
  tail = nullptr;
  length = 0;
}

// copy a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection& rhs) {
  *this = rhs;
}

// assign a linked list
template <typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection <K,V>& rhs) {
  Node* ptr = head;
  Node* temp = rhs.head;

  while(temp != nullptr){ //while the node is not empty
    ptr = temp;
    temp = temp->next;
    ptr->next = temp;
  }
}

// delete a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection() {
  Node* ptr = head;

  while(ptr != nullptr){  //while the node is not empty
    Node* temp = ptr;
    ptr = ptr->next;
    delete temp;
    temp = nullptr;
    length--;
  }
}

// insert a key - value pair into the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& key, const V& val) {
  Node* ptr = new Node;
  ptr->key = key;
  ptr->value = val;
  ptr->next = nullptr;
  length += 1;

  if(head == nullptr){ //if nothing is in the node, need to insert different
    head = ptr;
    tail = ptr;
  }else{  //else insert a different way
    tail->next = ptr;
    tail = tail->next;
  }
}

// remove a key - value pair from the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& key) {
  Node* ptr = head;
  Node* temp = ptr;

  if (ptr == head && ptr->key == key){  //if the right node
    if (length == 1){     //if the length is one
      head = nullptr;
      tail = nullptr;
    } else {    //else the length is longer than one
      head = ptr->next;
    }
    delete ptr;
    length--;
  } else {
    while(ptr != nullptr) {
      if (ptr->key == key) {
        if (ptr->next == nullptr) {
          tail = temp;
          temp = temp->next;
          delete ptr;
          ptr = nullptr;
        } else {
          temp->next = ptr->next;
          delete ptr;
          ptr = nullptr;
        }
      length--;
      break;
      }
      temp = ptr;
      ptr = ptr->next;
    }
  }
}

// find the value associated with the key
template <typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& key, V& val) const{
  Node* ptr = head;

  while(ptr != nullptr) { //while node is not empty
    if (ptr->key == key) {  //if contains the key value
      val = ptr->value;
      return true;
    } else {
      ptr = ptr->next;
    }
  }
  return false;
}

// find the keys associated with the range
template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const {
Node* ptr = head;

  while(ptr != nullptr){ //while not empty
    if (ptr->key >= k1 && ptr->key <= k2) {
      keys.push_back(ptr->key);
    }
    ptr = ptr->next;
  }
}

// return all keys in the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector <K>& keys) const {
  Node* ptr = head;

  for (int i = 0; i < length; i++) {  //for loop until at the end of the length
    keys.push_back(ptr->key);
    ptr = ptr->next;
  }
  std::sort(keys.begin(), keys.end());
}

// return collection keys in sorted order
template <typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector <K>& keys) const{
  Node* ptr = head;

  while (ptr != nullptr) {  //while the node exists
    keys.push_back(ptr->key);
    ptr = ptr->next;
  }
  std::sort (keys.begin(), keys.end());
}

// return the number of keys in collection
template <typename K, typename V>
int LinkedListCollection<K,V>::size() const {
  return length;
}

// insertion sort function returns sorted list
template <typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort() {
  Node* ptr = head;
  Node* temp = ptr -> next;

  if (size() == 1){ //if the size == 1
    return;
  }

  for (int i = 1; i < size(); i++){ //until at the end of the list
    if (temp -> key < head -> key) {  //compare 
      ptr -> next = temp -> next;
      temp -> next = head;
      head = temp;
    } else if (temp -> key >= ptr -> key){
      ptr = ptr -> next;
    } else {
      Node* ptr = head;
      while (ptr -> next-> key < temp ->key){
        ptr = ptr -> next;
      }
      Node* nextNode = ptr -> next;
      ptr -> next = temp -> next;
      ptr -> next = temp;
      temp -> next = nextNode;
    }
    temp = ptr -> next;
  }
}

//merge sort function returns sorted list
template <typename K, typename V>
typename LinkedListCollection<K,V>:: Node* LinkedListCollection<K,V>::merge_sort(Node* left, int len) {
  if (len == 1){
    return left;
  }

  int middle = ((len - 1) / 2) + 1;
  Node* ptr = left;

  for (int i = 0; i < middle - 1; i++){
    ptr = ptr -> next;
  }

  Node* tempLeft = left;
  Node* tempRight = ptr -> next;
  ptr -> next = nullptr;
  tempLeft = merge_sort(tempLeft, middle);
  tempRight = merge_sort(tempRight, len - middle);
  Node* front = nullptr;
  Node* merged = nullptr;

  if (tempLeft -> key > tempRight -> key) {
    front = tempRight;
    tempRight = tempRight -> next;
  } else {
    front = tempLeft;
    tempLeft = tempLeft -> next;
  }

  merged = front;

  while (tempLeft && tempRight) {
    if (tempLeft->key > tempRight->key) {
      merged -> next = tempRight;
      merged = tempRight;
      tempRight = tempRight -> next;
    } else {
      merged -> next = tempLeft;
      merged = tempLeft;
      tempLeft = tempLeft -> next;
    }
  }

  while (tempLeft != nullptr) {
    merged -> next = tempLeft;
    merged = tempLeft;
    tempLeft = tempLeft -> next;
    merged -> next = nullptr;
  }

  while (tempRight != nullptr) {
    merged -> next = tempRight;
    merged = tempRight;
    tempRight = tempRight -> next;
    merged -> next = nullptr;
  }
  return front;
}

// merge sort helper
template <typename K, typename V>
void LinkedListCollection<K,V>::merge_sort() {
  head = merge_sort(head, size());
  Node* ptr = head;

  while(ptr->next != nullptr) {
    ptr = ptr->next;
  }
  tail = ptr;
}

//quick sort function TODO not working yet :((((
template <typename K, typename V>
typename LinkedListCollection<K,V>:: Node* LinkedListCollection<K,V>::quick_sort(Node* start, int len) {
  if (len <= 1) {
    return start;
  } else if (len == 2) {
    Node* nextNode = start->next;
    if (start->key > nextNode->key) {
      nextNode->next = start;
      start->next = nullptr;
      return nextNode;
    } else {
      return start;
    }
  }

  Node* pivot = start;
  Node* ptr = pivot -> next;
  int smallListSize = 0;
  Node* left = nullptr;
  Node* left_tail = nullptr;
  Node* right = nullptr;
  Node* right_tail = nullptr;

  while (ptr != nullptr) {
    if (ptr->key < pivot->key) {
      if (left == nullptr) {
        left = ptr;
        left_tail = ptr;
      } else {
        left_tail->next = ptr;
        left_tail = left_tail->next;
      }
        smallListSize += 1;
    } else {
      if (right == nullptr) {
        right = ptr;
        right_tail = ptr;
      } else {
        right_tail->next = ptr;
        right_tail = right_tail->next;
      }
    }
    ptr = ptr->next;
  }

  if (left_tail){
    left_tail -> next = nullptr;
  }

  if (right_tail){
    right_tail -> next = nullptr;
  }

  left = quick_sort(left, smallListSize);
  right = quick_sort(right, len - smallListSize - 1);
  Node* front = left;
  left_tail->next = pivot;
  pivot->next = right;
  right_tail -> next = nullptr;

  return front;
}

// quick sort helper
template <typename K, typename V>
void LinkedListCollection<K,V>::quick_sort() {
  Node* temp = head;
  head = quick_sort(head, length);
  temp = head;
}

# endif
