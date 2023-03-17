 #ifndef NODE_H
 #define NODE_H
 using namespace std;

 class Node {
  public:
   
   //Constructor below
   
   Node();
   
   //Destructor Below
   
   ~Node();
   
   //Setters Below!
   
   void setRight(Node*);
   void setLeft(Node*);
   void setNext(Node*);
   void setData(char*);
   
   //Getters Below!
   
   Node* getRight();
   Node* getLeft();
   Node* getNext();
   char* getData();
  private:
   Node* left;
   Node* right;
   Node* next;
   char* data;
 
 };
 #endif
