#pragma once
#include <iostream>
#include <stdlib.h>
#include "LinkedListExceptions.h"

using namespace std;

template < class T >
class LinkedList
{
 public:
  LinkedList();
  ~LinkedList();

  void insert(const T& elem);

  bool removeFromFront(T& elem);

  T at(int pos);
  T operator [] (int pos);

  bool first(T& elem);
  bool next(T& elem);

  int size();
  bool isEmpty();
  void print();
 private:
  
  struct Node
  {
    T data;
    Node* p_next;
  };

  Node* p_head;
  Node* p_current;
  int numElements;

};

//ctor
template < class T >
LinkedList < T > :: LinkedList()
{
  p_head = 0;
  p_current = 0;
  numElements = 0;
}

//dtor
template <class T>
LinkedList <T> :: ~LinkedList()
{
  Node* p_temp;

  //while the list is not empty
  while(!isEmpty()){
    
    //create a pointer to the head
    p_temp = p_head;

    //move the head forward
    p_head = p_head->p_next;

    //print out the value we're deleting
    //cout << "Deleting: " << p_temp->data << endl;

    //free up the memory for that node
    delete p_temp;

    //we now have one less element
    numElements--;
  }
}

//insert
template < class T > 
void LinkedList < T > :: insert(const T& elem)
{

  //create a new node on the heap
  Node* p_temp = new Node;
  
  //fill in the data of the new node
  p_temp->data = elem;

  //set new node's link to point to
  //whatever the head points to (old head)
  p_temp->p_next = p_head;

  //set the head to point to the new node (new head)
  p_head = p_temp;

  //increase number of elements
  numElements++;

}

//removeFromFront
template <class T>
bool LinkedList <T> :: removeFromFront(T& elem)
{
  //assume we haven't removed anything
  bool retVal = false;

  if(!isEmpty()){

    //create Node temp pointer
    Node* p_temp;

    //let temp point to head
    p_temp = p_head;

    //adjust p_head
    p_head = p_head->p_next;
    
    //set elem removing using p_temp
    elem = p_temp->data;
    
    //delete the old p_head using p_temp
    delete p_temp;
    p_temp = 0;

    //switch retVal
    retVal = true;

    //decrement numElements
    numElements--;

  }

  return retVal;

}

//at
template <class T>
T LinkedList <T> :: at(int pos)
{
  //object to return eventually
  T retVal;

  //search helper node
  Node* p_search = p_head;

  int count = 0;
  
  //if pos isn't a valid index
  if(pos >= size() ||
     pos < 0){
    LinkedListOutOfBoundsException error;
    throw error;
  }
  //if pos is within bounds
  else{
      while(p_search != 0){

	  if(count == pos){
	      retVal = p_search->data;
	      break;
	  }

	  count++;
	  //send p_search towards tail
	  p_search = p_search->p_next;
      }
  }

  return retVal;

}

//operator []
template <class T>
T LinkedList <T> :: operator [] (int pos)
{
  //call and return result of at() function
  return at(pos);
}

//first
template <class T>
bool LinkedList <T> :: first(T& elem)
{
  bool retVal = false;

  //if the list is not empty
  if(!isEmpty()){

    //indicate there is a first item
    retVal = true;

    //copy the data into reference parameter
    elem = p_head->data;

    //store current node that is being processed
    p_current = p_head;

  }

  return retVal;

}

//next
template <class T>
bool LinkedList <T> :: next(T& elem)
{
  bool retVal = false;

  //if we have not processed all the elements
  if(p_current->p_next != 0){
    
    //move the current pointer forward one element
    p_current = p_current->p_next;

    //indicate there is a first item
    retVal = true;

    //copy the data into the reference parameter
    elem = p_current->data;
  }

  return retVal;

}

//size
template <class T>
int LinkedList <T> :: size()
{
  return numElements;
}

//isEmpty
template <class T>
bool LinkedList <T> :: isEmpty()
{
  return (size() == 0);
}

//print
template <class T>
void LinkedList <T> :: print()
{
  //helper T object
  T val;

  if(isEmpty()){
    
    cout << "Not printing because list is empty" << endl;

  }
  else{

    //if there is a last item (list is not empty)
    //store the element in val
    if(first(val)){

      cout << val << endl;

      //while we are not at the end, store each element in val
      while(next(val)){

	cout << val << endl;

      }
    }

  }

}
