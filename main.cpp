
//William Wong
 //3/17/23
 //This project is called the Shunting Yard Algoirthm which helps to take a math expression and convert it to postifx notation

 #include <cstring>
 #include <iostream>
 #include "node.h"
 using namespace std;

 //Function prototypes below

 int precedence(char* p);
 void enqueue(Node*& front, Node*& rear, char* value);
 void dequeue(Node*& front, Node*& rear);
 bool isEmpty(Node* front, Node* rear);
 void displayFront(Node* front, Node* rear);
 void displayQueue(Node* front, Node* rear);
 
 void pushTree(Node*& tree, Node*& add);
 void popTree(Node*& tree);

 void push(Node*& top, char* value);
 void pop(Node*& top);
 Node* peek(Node* top);
 
 void treeInfix(Node* Infixt);
 void treePrefix(Node* Prefixt);
 void treePostfix(Node* Postfixt);

 int main() {
   
    //Helps to stack, putting the newest node in stack
    Node* top = NULL;
    //First node implemneted in queue
    Node* front = NULL;
    //Last node implmeneted in queue
    Node* rear = NULL; 

    bool running = true;
    char command[10];
    char input[100];

    cout << "This is the Shunting Yard Algorithm!" << endl;

    while (running == true) {cout << endl << "Please Choose to --> Translate or Quit" << endl;
       cin.get(command, 10);
       cin.clear();
       cin.ignore(1000, '\n');
       if (strcmp(command, "Translate") == 0 || strcmp(command, "translate") == 0) {
	 cout << "Program running..." << endl;
	 cout << "Please input your equation in the infix notation: ";
	 cin.get(input, 100);
	 cin.clear();
	 cin.ignore(1000, '\n');
	 char** modifyIf = new char* [100];

	 //Helping to clear the stack and queues

	 top = NULL;
	 front = NULL;
	 rear = NULL;
	 int initial = 0; 
	 int inputCount = 0; 
	 for (int i = 0; i < strlen(input); i++) {
	   if (input[i] == ' ') {
	     if (initial == 1) {
	       char* temp = new char[10];
	       //Helping to remove the temporary memory 
	       for (int j = 0; j < sizeof(temp); j++) { 
		 temp[j] = 0;
	       }
	       temp[0] = input[i - 1];
	       modifyIf[inputCount] = temp;
	       inputCount++;
	       initial = 0;
	     }
	     else {
	       char* temp = new char[10];
	       //Helping to remove the temporary memory
	       for (int j = 0; j < sizeof(temp); j++) { 
		 temp[j] = 0;
	       }
	       for (int j = 0; j < 1; j++) {
		 temp[j] = input[i - 1 + j];
	       }
	       modifyIf[inputCount] = temp;
	       inputCount++;
	       initial = 0;
	     }
	   }
	   else {
	     char* temp = new char[10];
	     //Helps to remove the temporary memory
	     for (int j = 0; j < sizeof(temp); j++) { 
	       temp[j] = 0;
	     }
	     initial++;
	     //Checking for the last pair of the charachter
	     if (i == strlen(input) - 1) { 
	       for (int j = 0; j < 1; j++) {
		 temp[j] = input[i + j + 1 - initial];
	       }
	       modifyIf[inputCount] = temp;
	       inputCount++;
	     }
	   }
	 }
	 cout << "Input Recieved" << endl << endl << "Tokens: " << endl;;
	 //Helps to print out the tokens with precedence
	 for (int j = 0; j < inputCount; j++) { 
	   cout << modifyIf[j] << " precedence: " << precedence(modifyIf[j]) << endl;
	 }
	 int run = 0;
	 
	 while (run < inputCount) {
	   //If the token is that of a num
	   if (precedence(modifyIf[run]) == 0) {
	     enqueue(front, rear, modifyIf[run]);
	   }
	   //Helps to check if the token is an operator
	   if (precedence(modifyIf[run]) == 1 || precedence(modifyIf[run]) == 2 || precedence(modifyIf[run]) == 3) {
	     if (top != NULL) {
	       while (precedence(top->getData()) >= precedence(modifyIf[run]) && *top->getData() != '(') {
		 //Helps to pop from the stacn/enqeue
		 enqueue(front, rear, top->getData());
		 pop(top);
		 if (top == NULL) {
		   break;
		 }
	       }
	     }
	     //Helps to stack
	     push(top, modifyIf[run]);
	   }
	   //If the token is the left parenthesis
	   if (*modifyIf[run] == '(') { 
	     //Below helps to push to stack
	     push(top, modifyIf[run]); //Push to stack
	   }
	   //Making sure the token is within the correct parenthesis
	   if (*modifyIf[run] == ')') { 
	     while (*top->getData() != '(') {
	       enqueue(front, rear, top->getData());
	       pop(top);
	     }
	     if (*top->getData() == '(') {
	       //Below helps to pop from stack
	       pop(top); 
	     }
	   }
	   //Going into the next token
	   run++; 
	 }
	 if (run == inputCount) {
	   while (top != NULL) {
	     enqueue(front, rear, top->getData());
	     pop(top);
	   }
	 }
	 cout << "Binary Tree Created From: " << endl;
	 displayQueue(front, rear);
	 cout << endl << "Created with " << inputCount << " tokens." << endl << endl;
	 //Below is the top of the tree stack
	 Node* tree = NULL; 
	 //Helps to make the queue into tree stack
	 while (front != rear) {
	   Node* t = new Node();
	   t->setData(front->getData());
	   pushTree(tree, t);
	   front = front->getNext();
	 }
	 
	 Node* t = new Node();
	 t->setData(rear->getData());
	 pushTree(tree, t);

	 //Helps to display the final result
	 
	 cout << "infix for infix notation --> prefix for prefix notation --> postfix for postfix notation" << endl;
	 char display[10];
	 cin.get(display, 10);
	 cin.clear();
	 cin.ignore(10000, '\n');
	 cout << "Outputting-" << endl;
	 //If user asks for infix notation
	 if (strcmp(display, "infix") == 0) { 
	   treeInfix(tree);
	 }
	 //If user asks for prefix notation
	 else if (strcmp(display, "prefix") == 0) { 
	   treePrefix(tree);
	 }
	 //If user asks for postfix notation
	 else if (strcmp(display, "postfix") == 0) {
	   treePostfix(tree);
	 }
	 else {
	   cout << "Ivalid Input!" << endl;
	 }
	 cout << endl << endl;
       }
       //Helps to quit
       else if (strcmp(command, "Quit") == 0 || strcmp(command, "quit") == 0) { 
	 cout << "Shutting down Shunting Yard Algor...i..th..m.." << endl;
	 running = false;
       }
       //Invalid input below
       else { 
	 cout << endl << "Invalid input! Please try again!" << endl;
       }
    }
 }

 //Precedence function below determining importance

 int precedence(char* p) {
   if (*p == '^') {
     //Highest
     return 3;
   }
   else if (*p == '*' || *p == '/') {
     //The second highest
     return 2; 
   }
   else if (*p == '+' || *p == '-') {
     //The second lowest
     return 1; 
   }
   else if (*p == '(' || *p == ')') {
     return 5; 
   }
   else {
     //The lowerst (nums)
     return 0; 
   }
 }

 //Adds node to queue

 void enqueue(Node*& front, Node*& rear, char* value) { 
   Node* temp = new Node();
   temp->setData(value);
   temp->setNext(NULL);
   if (front == NULL) { 
     front = temp;
     rear = temp;
   }
   //Making sure a node occurs
   else { 
     rear->setNext(temp);
     rear = temp;
   }
 }

 //Removes first node in queue
 void dequeue(Node*& front, Node*& rear) { 
   if (isEmpty(front, rear)) {
     cout << "Empty queue" << endl;
   }
   //If there is only one node
   else if (front == rear) { 
     // Below helps to delete the node
     front == NULL;
     rear == NULL;
   }
   else {
     Node* temp = front;
     front = front->getNext();
     temp->setNext(NULL);
   }
 }

 //Look for empty queue below

 bool isEmpty(Node* front, Node* rear) {
   if (front == NULL && rear == NULL) {
     return true;
   }
   else {
     return false;
   }
 }

 //Below is the showfront function

 void displayFront(Node* front, Node* rear) {
   if (isEmpty(front, rear)) {
     cout << "Empty queue" << endl;
   }
   else {
     cout << front->getData();
   }
 }

 //Below is the displayqueue function

 void displayQueue(Node* front, Node* rear) {
   if (isEmpty(front, rear)) {
     cout << "Empty queue" << endl;
   }
   else {
     Node* temp = front;
     while (temp != NULL) {
       cout << temp->getData() << " ";
       temp = temp->getNext();
     }
     cout << endl;
   }
 }

 // Below is the pushtree function

 void pushTree(Node*& tree, Node*& add) {
   //If there is an empty tree
   if (tree == NULL) { 
     add->setNext(tree);
     tree = add;
   }
   else {
     //Below helps to identify numbers
     if (precedence(add->getData()) == 0) {
       add->setNext(tree);
       tree = add;
     }
     //If the toek is an operator
     else { 
       Node* left = tree;
       popTree(tree);
       left->setNext(NULL);
       Node* right = tree;
       popTree(tree);
       right->setNext(NULL);
       //Below helps to push the operator node
       add->setNext(tree);
       tree = add;
       //Below helps the two popped numbers to be within the left and right pointers of operator node
       tree->setLeft(left);
      tree->setRight(right);
     }
   }
 }

 //Below is the poptree function

 void popTree(Node*& tree) { 
   if (tree == NULL) {
     cout << "Tree stack is empty" << endl;
   }
   else {
     Node* temp = tree;
     tree = tree->getNext();
     temp->setNext(NULL);
   }
 }

 //Help to show the infix function

 void treeInfix(Node* Infixt) {
   if (Infixt != NULL) {
     if (precedence(Infixt->getData()) != 0) {
       cout << "( ";
     }
     treeInfix(Infixt->getLeft());
     cout << Infixt->getData() << " ";
     treeInfix(Infixt->getRight());
     if (precedence(Infixt->getData()) != 0) {
       cout << ") ";
     }
   }
 }

 //Help to show the prefix function

 void treePrefix(Node* Prefixt) { 
   if (Prefixt != NULL) {
     cout << Prefixt->getData() << " ";
     treePrefix(Prefixt->getLeft());
     treePrefix(Prefixt->getRight());
   }
 }

 //Help to show the postfic function

 void treePostfix(Node* Postfixt) {
   if (Postfixt != NULL) {
     treePostfix(Postfixt->getLeft());
     treePostfix(Postfixt->getRight());
     cout << Postfixt->getData() << " ";
   }
 }

 //Adds new elements at the end of stack                                                                                    
 void push(Node*& top, char* value) { //Push function                                                                       
   Node* temp = new Node();
   temp->setData(value);
   temp->setNext(top);
   top = temp;
 }

 //Pop function which helps to remove that of the  newest added element                                                     
 void pop(Node*& top) {
   if (top == NULL) {
     cout << "Empty" << endl;
   }
   else {
     Node* temp = top;
     top = top->getNext();
     temp->setNext(NULL);
   }
 }

 //Peek function below                                                                                                      

 Node* peek(Node* top) {
   if (top == NULL) {
     cout << "Stack is empty" << endl;
     Node* none = new Node();
     return none;
   }
   else {
     return top;
   }
 }
