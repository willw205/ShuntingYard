 #include <cstring>
 #include <iostream>
 #include "node.h"
 using namespace std;

 //Constructor below

 Node::Node() {
   left = NULL;
   right = NULL;
   next = NULL;
   data = NULL;
 }

 //Destructor below 

 Node::~Node() {
  
 }

 //Creating the Setters!

 void Node::setRight(Node* newRight) {
   right = newRight;
 }

 void Node::setLeft(Node* newLeft) {
   left = newLeft;
 }

 void Node::setNext(Node* newNext) {
   next = newNext;
 }

 void Node::setData(char* newData) {
   data = newData;
 }

 //Creating the Getters!

 Node* Node::getRight() {
   return right;
 }

 Node* Node::getLeft() {
   return left;
 }

 Node* Node::getNext() {
   return next;
 }

 char* Node::getData() {
  return data;
 }
