/*****************************************************************************
 *
 *  Author:           Nathan Groves
 *  Title:            Singly Linked List with Overloaded Operators
 *  Course:           2143
 *  Semester:         Fall 2022
 *
 *  Description:
            Implements a singly linked list to allow for overloaded operators
            to add, subtract, mulitply, divide, and check for equality with 
            different vectors
 *        
 *
 *  Usage:
 *    Use to create a linked list, as well as perform numerous operations on them
 *
 *  Files: main.cpp
 *****************************************************************************/

//necessary libraries
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000 // infinity

using namespace std;

// Node for our linked list
struct Node {
  int data;

  Node *next;

  Node(int x) {
    data = x;
    next = NULL;
  }
};

class MyVector {
private:
  Node *head; // base pointer of list
  Node *tail;
  int size;
  static ofstream fout;
  string fileName;
  bool sorted;

  /**
   * Private version of inOrder push.
   *
   * param:  int   x - number to add
   */
  void _inorderPush(int x) {
    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (curr->data > x) { // loop to find proper location
      prev = curr;
      curr = curr->next;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
  }

public:

  /**
   * Default constructor
   *
   */
  MyVector() { init(); }

  /**
   *  Overloaded Constructor
   *
   *
   * params:  int   *A - pointer to array
   *          int   aSize - size of array
   */
  MyVector(int A[], int aSize) {
    init();

    for (int i = 0; i < aSize; i++) {
      pushRear(A[i]);
    }
  }

  /**
   * Overloaded Constructor
   *
   * param: string FileName - file to open and read
   *
   * Assumes infile will contain numbers only delimited by spaces or
   * new lines.
   */
  MyVector(string FileName) {
    init();

    ifstream fin;
    int x = 0;

    fin.open(FileName);
    while (!fin.eof()) {
      fin >> x;
      pushRear(x);
    }
  }

  /**
   * Copy Constructor
   *
   * param: MyVector &other
   */
  MyVector(const MyVector &other) {
    init();

    Node *temp = other.head;

    while (temp) {
      pushRear(temp->data);
      temp = temp->next;
    }
  }

  /**
   *  Initialize the data members so we don't
   *   have duplicate lines in each constructor.
   *
   */
  void init() {
    head = tail = NULL;
    fileName = "";
    size = 0;
    sorted = 0;
  }

  /**
   * Public version of inOrder push.
   *
   * param:  int x - number to add
   */
  void inorderPush(int x) {
    if (!sorted) {
      sortList();
    }

    if (!head) {
      pushFront(x); // call push front for empty list (or pushRear would work)
    } else if (x < head->data) {
      pushFront(x); // call push front if x is less than head
    } else if (x > tail->data) {
      pushRear(x); // call push rear if x > tail
    } else {
      _inorderPush(x); // call private version of push in order
    }
  }

  /**
   * Sort the current values in the linked list.
   *
   * returns: None
   */
  void sortList() {
    Node *newFront = head;
    while (newFront->next) {
      Node *smallest = newFront;
      Node *current = newFront;
      int minimum = INF;
      while (current) {
        if (current->data < minimum) {
          smallest = current;
          minimum = current->data;
        }
        current = current->next;
      }
      smallest->data = newFront->data;
      newFront->data = minimum;
      newFront = newFront->next;
    }
    sorted = true;
  }

  /**
   * Add value to front of list.
   *
   * param: int x - number to add
   */
  void pushFront(int x) {
    Node *tempPtr = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
      head = tail = tempPtr;
      // otherwise adjust head pointer
    } else {
      tempPtr->next = head;
      head = tempPtr;
    }
    size++;
  }

  /**
   *         This method loads values from 'other' list in 'this' list.
   *          It loads an array first so we can process the values in
   *          reverse so they end up on 'this' list in the proper order.
   *          If we didn't use the array, we would reverse the values
   *          from the 'other' list.
   *
   * depends - Uses `pushFront(int)`
   * param: MyVector& other
   * returns: None
   */
  void pushFront(const MyVector &other) {
    Node *otherPtr = other.head;         // get copy of other lists head
    int *tempData = new int[other.size]; // allocate memory to hold values

    // load other list into array
    int i = 0;
    while (otherPtr) {
      tempData[i] = otherPtr->data;
      otherPtr = otherPtr->next;
      ++i;
    }

    // process list in reverse in order to keep them
    // in their original order.
    for (int i = other.size - 1; i >= 0; i--) {
      pushFront(tempData[i]);
    }
  }

  /**
   * Add 'other' list's values to end of 'this' list.
   * note - Uses `pushRear(int)`
   * param: MyVector& other
   * returns: None
   */
  void pushRear(const MyVector &other) {
    Node *otherPtr = other.head; // get copy of other lists head

    while (otherPtr) { // traverse and add
      pushRear(otherPtr->data);
      otherPtr = otherPtr->next;
    }
  }

  /**
   * Push value onto list at specified position, if it exists.
   *
   * param int i - location index
   * param int x - value to add
   * returns: bool - true add successful / false add failed
   */
  bool pushAt(int i, int x) {
    if (i >= size) {
      return false;
    }

    Node *tempPtr = new Node(x); // allocate new node
    Node *prev = head;           // get previous and next pointers
    Node *curr = head;

    while (i > 0) { // loop to find proper location
      prev = curr;
      curr = curr->next;
      i--;
    }

    tempPtr->next = prev->next; // add new node in its proper position
    prev->next = tempPtr;

    size++; // add to size :)
    return true;
  }

  /**
   *  Add value to rear of list
   *
   * param: int x - value to be added
   * returns: None
   */
  void pushRear(int x) {
    Node *tempPtr = new Node(x);

    if (!head) {
      head = tail = tempPtr;

    } else {
      tail->next = tempPtr;
      tail = tempPtr;
    }
    size++; // add to size of list
  }

 /**
   * gets the size of a list
   *
   * param: none
   * returns: size
   */
int getSize()
{
  return size;
}


 /**
   *  overload brackets to change/display value 
   *  at position
   *
   * param: int index - position of value
   * returns: number at specificed index
   */
  int& operator[](int index) {

    int invalidIndex = 0;
		Node* traverse = head;
    //makes sure the position exists
		if (index >= getSize() || index < 0) {
			cout << "index does not exist" << endl << endl;
			return invalidIndex;
		}
		else {
			// finds the position in the vector
			for (int i = 0; i < index; i++) {
				traverse = traverse->next;

			}

			return traverse -> data;
		}
	}

/**
   *  assignment overloaded to allow for vector
   * to be copied
   *
   * param: MyVector& vectorToCopy
   * returns: vector after change
   */
MyVector& operator=(const MyVector& vectorToCopy) {
		// makes sure there is no self-assignment
		if (this == & vectorToCopy) {
			return *this;
		}

    this->head = vectorToCopy.head;
    this->tail = vectorToCopy.tail;

			return *this;
	}

/**
   *  output stream overloaded to allow for
   *  printing vector to output file
   *
   * param: MyVector& rhs
   * param: ofstream & of
   * returns: ofstream &
   */
	friend ofstream& operator<<(ofstream & of, const MyVector& rhs) {
 Node *temp = rhs.head; // temp pointer copies head

    of << "[";

    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      of << temp->data; // print data from Node
      if (temp->next) {
        of << ",";
      }
      temp = temp->next; // move to next Node
    }

    of << "]";
    of << endl;
    return of;
  }

/**
   *  console stream overloaded to allow for
   *  printing vector to console
   *
   * param: MyVector& rhs
   * param: ostream & os
   * returns: ostream &
   */
 friend ostream & operator<<(ostream &os, const MyVector &rhs) {
    Node *temp = rhs.head; // temp pointer copies head

   os << "[";

    while (temp) { // this loops until temp is NULL
                   // same as `while(temp != NULL)`

      os << temp->data; // print data from Node
      if (temp->next) {
        os << ",";
      }
      temp = temp->next; // move to next Node
    }
    os << "]";
    os << endl;
    return os;
  }


//friend prototypes to allow access for overloaded operators
	friend bool operator==(const MyVector&, const MyVector&);

	friend MyVector& operator/(const MyVector&, const MyVector&);

	friend MyVector& operator*(const MyVector&, const MyVector&);

	friend MyVector& operator-(const MyVector&, const MyVector&);

	friend MyVector& operator+(const MyVector&, const MyVector&);


};


/**
   *  overloaded equality operator made to compare
   *  the value of vectors to see if they are equal
   *
   * param: MyVector & firstVector
   * param: MyVector & secondVector
   * returns: bool - 1 if equal, 0 if false
   */
bool operator==(const MyVector& firstVector, const MyVector& secondVector)
{
  bool isEqual = true;
  
  Node * firstTemp = firstVector.head;
  Node * secondTemp = secondVector.head;

  //while both lists still have values, compare them
  while (firstTemp && secondTemp && isEqual)
    {


      //exit loop if unequal value found
      if (!(firstTemp -> data == secondTemp -> data))
      {
        isEqual = false;
      }

      firstTemp = firstTemp -> next;
      secondTemp = secondTemp -> next;

    }

  //make false if size is not equal
    if (firstTemp && !secondTemp)
    {
      isEqual = false;
    }

  //make false if size is not equal
    else if (!firstTemp && secondTemp)
    {
      isEqual = false;
    }



  return isEqual;

}


/**
   *  overloaded division operator to allow for
   *  vectors to be divided with each other
   *
   * param: MyVector & firstVector
   * param: MyVector & secondVector
   * returns: MyVector &
   */
MyVector& operator/(const MyVector& firstVector, const MyVector& secondVector)
{
   MyVector newVector;
	  Node* copyVectorOne = firstVector.head;
	  Node* copyVectorTwo = secondVector.head;
  
//while both vectors still have values, divide them
  while (copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data / copyVectorTwo -> data);
      copyVectorOne = copyVectorOne -> next;
      copyVectorTwo = copyVectorTwo -> next;
    }

  //if only one vector value exists, copy value from existent vector
   while (copyVectorOne || copyVectorTwo)
     {
    if (copyVectorOne && !copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data);
      copyVectorOne = copyVectorOne -> next;
    }
      
    else if (!copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorTwo -> data);
        copyVectorTwo = copyVectorTwo -> next;

    }
       }

    
  return newVector;
}


/**
   *  overloaded multiplication operator to allow for
   *  vectors to be multiplied with each other
   *
   * param: MyVector & firstVector
   * param: MyVector & secondVector
   * returns: MyVector &
   */
MyVector& operator*(const MyVector& firstVector, const MyVector& secondVector)
{
   MyVector newVector;
	  Node* copyVectorOne = firstVector.head;
	  Node* copyVectorTwo = secondVector.head;

  //while both vectors still have values, multiply them
  while (copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data * copyVectorTwo -> data);
      copyVectorOne = copyVectorOne -> next;
      copyVectorTwo = copyVectorTwo -> next;
    }

  //if only one vector value exists, copy value from existent vector
   while (copyVectorOne || copyVectorTwo)
     {
    if (copyVectorOne && !copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data);
      copyVectorOne = copyVectorOne -> next;
    }

    else if (!copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorTwo -> data);
        copyVectorTwo = copyVectorTwo -> next;

    }
       }

    
  return newVector;
}


/**
   *  overloaded subtraction operator to allow for
   *  vectors to be subtracted with each other
   *
   * param: MyVector & firstVector
   * param: MyVector & secondVector
   * returns: MyVector &
   */
MyVector& operator-(const MyVector& firstVector, const MyVector& secondVector)
{
    MyVector newVector;
	  Node* copyVectorOne = firstVector.head;
	  Node* copyVectorTwo = secondVector.head;

  //while both vectors still have values, subtract them
  while (copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data - copyVectorTwo -> data);
      copyVectorOne = copyVectorOne -> next;
      copyVectorTwo = copyVectorTwo -> next;
    }

  //if only one vector value exists, copy value from existent vector
   while (copyVectorOne || copyVectorTwo)
     {
    if (copyVectorOne && !copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data);
      copyVectorOne = copyVectorOne -> next;
    }

    else if (!copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorTwo -> data);
        copyVectorTwo = copyVectorTwo -> next;

    }
       }

    
  return newVector;

}


/**
   *  overloaded addition operator to allow for
   *  vectors to be added to each other
   *
   * param: MyVector & firstVector
   * param: MyVector & secondVector
   * returns: MyVector &
   */
 MyVector& operator+(const MyVector& firstVector, const MyVector& secondVector) {
	  
    MyVector newVector;
	  Node* copyVectorOne = firstVector.head;
	  Node* copyVectorTwo = secondVector.head;

  //while both vectors still have values, add them
  while (copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data + copyVectorTwo -> data);
      copyVectorOne = copyVectorOne -> next;
      copyVectorTwo = copyVectorTwo -> next;
    }

  //if only one vector value exists, copy value from existent vector
   while (copyVectorOne || copyVectorTwo)
     {
    if (copyVectorOne && !copyVectorTwo)
    {
      newVector.pushRear(copyVectorOne -> data);
      copyVectorOne = copyVectorOne -> next;
    }

    else if (!copyVectorOne && copyVectorTwo)
    {
      newVector.pushRear(copyVectorTwo -> data);
        copyVectorTwo = copyVectorTwo -> next;

    }
       }

    
  return newVector;

}





int main() {


  
int a1[] = { 1, 2, 3, 4, 5 };
int a2[] = { 10, 20, 30 };

MyVector v1(a1,5);
MyVector v2(a2,3);

ofstream fout;
fout.open("output.txt");

cout << v1[2] << endl << endl;
fout << v1[2] << endl << endl;

// writes out 3

v1[4] = 9;
// v1 now = [1,2,3,4,9]

cout << v1 << endl;
// writes out [1,2,3,4,9] to console.

fout << v1 << endl;
// writes out [1,2,3,4,9] to output file.

MyVector v3 = v1 + v2;
cout << v3 << endl;
// writes out [11,22,33,4,9] to console.

  fout << v3 << endl;
//writes out [11,22,33,4,9] to output file


v3 = v1 - v2;
cout << v3 << endl;
// writes out [-9,-18,-27,4,9] to console.

  fout << v3 << endl;
// writes out [-9,-18,-27,4,9] to output file.

v3 = v2 - v1;
cout << v3 << endl;
// writes out [9,18,27,4,9] to console.

  fout << v3 << endl;
// writes out [9,18,27,4,9] to output file.

v3 = v2 * v1;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

  fout << v3 << endl;
// writes out [10,40,90,4,9] to output file.
  
v3 = v1 * v2;
cout << v3 << endl;
// writes out [10,40,90,4,9] to console.

  fout << v3 << endl;
// writes out [10,40,90,4,9] to output file.

v3 = v1 / v2;
cout << v3 << endl;
// writes out [0,0,0,4,9] to console.

  fout << v3 << endl;
// writes out [0,0,0,4,9] to output file.

v3 = v2 / v1;
cout << v3 << endl;
// writes out [10,10,10,4,9] to console.

  fout << v3 << endl;
// writes out [10,10,10,4,9] to output file.

cout << (v2 == v1) << endl << endl;
// writes 0 to console (false).

  fout << (v2 == v1) << endl << endl;
// writes 0 to output file (false).

MyVector v4 = v1;
cout << (v4 == v1) << endl;
// writes 1 to console (true).

  fout << (v4 == v1) << endl;
// writes 1 to output file (true).

  
}
