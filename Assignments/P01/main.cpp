/*****************************************************************************
*                    
*  Author:           Nathan Groves
*  Email:            nathanbg7676@gmail.com
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Fall 2022
* 
*  Description:
*        This program implements a linked list vector class that allows for 
*        popping and pushing various integer values at specific locations as 
*        well as reading in from numerous inputs to fill a list of Nodes. 
*
*  Usage:
*        A class instance may be hard-coded in main
* 
*  Files:           
        main.cpp    : driver program
        test.out    : output file for vector instances
        input.dat   : input file to fill list
*****************************************************************************/


//C++ Libraries
#include <iostream>
#include <fstream>
#include <string>



using namespace std;



/**
 * Node
 * 
 * Description:
 *      A Node struct to store data and the pointers for the previous and
 *      next Nodes.
 *
 * Member Variables:
 *
 *    int                 data
 *                    
 *    Node*               next
 *
 *    Node*               previous
 *
 * 
 * Public Methods:
 *                       Node (int data)
 *                       Node ()
 *
 * Usage:
 * 
 * Node ()              //create empty node 
 *
 *
 * Node (data)         //create node with given data
 *
 *
 * Node (d)
*/

struct Node
{
int data;
Node * next;
Node * previous;

Node (int d)
{
  data = d;
  next = NULL;
  previous =  NULL;
}

Node ()
{
data = 0;
next = NULL;
previous = NULL;
}

};

/*
__   _____ ___ _____ ___  ___    ___ _      _   ___ ___
 \ \ / / __/ __|_   _/ _ \| _ \  / __| |    /_\ / __/ __|
  \ V /| _| (__  | || (_) |   / | (__| |__ / _ \\__ \__ \
   \_/ |___\___| |_| \___/|_|_\  \___|____/_/ \_\___/___/

*/





/**
 * Vector
 * 
 * Description:
 *       A class that allows for a list of nodes, which hold integer values
 *      
 *
 * Private Members:
 *   Node*         head
 *   Node*         tail
 * 
 * 
 * Public Methods:
 * 
 *                Vector();                         // default constructor                        
 *                Vector(const Vector &);           // copy constructor                           
 *                Vector(int *, int);               // create vector given array of items         
 *                Vector(string);                   // create vector given input file
 * void           PushFront(int);                   // add item to front of vector                 
 * void           PushFront(const Vector &);        // add vector to front of other vector         
 * void           PushRear(int);                    // add item to front of vector                
 * void           PushRear(const Vector &);         // add vector to back of other vector          
 * int            PopFront();                       // remove item from front of vector            
 * int            PopRear();                        // remove item from back of vector             
 * int            PopAt(int);                       // remove item at certain location             
 * int            Find(int);                        // return position of value if it exists       
 * void           displayList();                    // print the vector                           
 * void           PushAt(int, int);                 // push value at specific location              
 * void           inOrderPush(int);                 // add item to list in order                     
 * void           SortList();                       // used to sort before adding an item in order    
 *   
 *     
 *
 * Usage:
 *  
 *  PushRear(5)              // Push 5 to rear of list
 *                                 
 * 
 *  Vector(a, 5)             // create vector given an array                 
 *                                     
 *  PopFront()               // remove front item from list
 *
 *                           
 */



class Vector 
{

Node * head;
Node * tail;

public:


 Vector();                                                       
 Vector(const Vector &);                                        
 Vector(int *, int);                           
 Vector(string);                                   


  void PushFront(int);                               
  void PushFront(const Vector &);              
  void PushRear(int);                                  
  void PushRear(const Vector &);                 
  int PopFront();                                  
  int PopRear();                                  
  int PopAt(int);                                 
  int Find(int);                          
  void displayList();                                         
  void PushAt(int, int);                         
  void inOrderPush(int);                               
  void SortList();                 


  friend ostream &operator<<(ostream &, const Vector &);    //overloaded ostream operator



};

/*
      ___ ___  _  _ ___ _____ ___ _   _  ___ _____ ___  ___  ___
   / __/ _ \| \| / __|_   _| _ \ | | |/ __|_   _/ _ \| _ \/ __|
  | (_| (_) | .` \__ \ | | |   / |_| | (__  | || (_) |   /\__ \
   \___\___/|_|\_|___/ |_| |_|_\\___/ \___| |_| \___/|_|_\|___/

*/

/**
     * Constructor : Vector()
     * 
     * Description:
     *      creates empty vector
     * 
     * Params:
     *      N/A
     * 
     
     */

  Vector::Vector()
   {
    head = NULL;
    tail = NULL;
   }


/**
     * Constructor : Vector(string)
     * 
     * Description:
     *      takes in input from file and creates list
     * 
     * Params:
     *      string
     * 
     */

   Vector::Vector(string textInput)
  {

    int inputValue = 0;
    ifstream infile;
    head = NULL;
    tail = NULL;
    
    infile.open(textInput);
    
    while (!infile.eof())
      {
        infile >> inputValue;
        PushRear(inputValue);
      }
  }


/**
     * Constructor : Vector(Vector &)
     * 
     * Description:
     *      create copy constructor
     * 
     * Params:
     *      Vector &
     * 
     */

  Vector::Vector(const Vector & v)
  {
    
  head = v.head;
  tail = v.tail;
    
  }

/**
     * Constructor : Vector(int *, int)
     * 
     * Description:
     *      create list given an array
     * 
     * Params:
     *      int *
     *      int
     */

  Vector::Vector(int * n, int size)
  {
     head = NULL;
     tail = NULL;
    
     for (int i = 0; i < size; i++)
       {
          PushRear(n[i]);
       }

  }



/*   
  __  __ ___ _____ _  _  ___  ___  ___
  |  \/  | __|_   _| || |/ _ \|   \/ __|
  | |\/| | _|  | | | __ | (_) | |) \__ \
  |_|  |_|___| |_| |_||_|\___/|___/|___/
  
*/


/**
     * Public : PushRear (int)
     * 
     * Description:
     *     add item to back of list
     * 
     * Params:
     *      int
     * 
     */

  void Vector::PushRear(int d)
   {
     
     Node * temp = new Node (d);
     
     if (head == NULL)
     {
       head = temp;
       tail = temp;
     }
       
    else 
     {
       
        tail-> next = temp;
        temp -> previous = tail;
        tail = temp;
     }

   }

/**
     * Public : PushFront (int)
     * 
     * Description:
     *      add item to front of list
     * 
     * Params:
     *      int
     * 
     */

void Vector::PushFront(int d)
  {
    
  Node * temp = new Node (d);
    if (head == NULL)
    {
      head = temp;
      tail = temp;
    }
    else
      
    {
      head -> previous = temp;
      temp -> next = head;
      head = temp;
    }
    
  }

/**
     * Public : PushFront (Vector &)
     * 
     * Description:
     *     add list to front of other list
     * 
     * Params:
     *     Vector &
     * 
     */

void Vector::PushFront(const Vector & v)
{
  
   v.tail -> next = head;
  head -> previous = v.tail;
  head = v.head;
    
}

/**
     * Public : PushRear (Vector &)
     * 
     * Description:
     *     add list to back of other list
     * 
     * Params:
     *      Vector &
     * 
     */

void Vector::PushRear(const Vector & v)
{
    tail -> next = v.head;
    tail = v.tail;
}

/**
     * Public : PopFront
     * 
     * Description:
     *     remove item from front of list
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      int 		  // item removed
     */

int Vector::PopFront()
{
  if (head == NULL)
  {
    return -1;
  }
    
  Node * temp = head;
  int removedNum = head -> data;
  head = head -> next;
  head -> previous = NULL;
  temp = nullptr;
  delete temp;

  return removedNum;
  
}

/**
     * Public : PushAt
     * 
     * Description:
     *      add item at specified location
     * 
     * Params:
     *      int
     *      int
     * 
     */

  void Vector::PushAt(int location, int val)
  {

  Node * temp = new Node (val);

    if (head == NULL || location == 0)
    {
      PushFront(val);
    }

    int index = location;
    int count = 0;
    
    
      Node * traverse = head;
      while (count < index)
        {
          traverse = traverse -> next;
          count++;
        }

    if (traverse -> next == NULL)
    {
       PushRear(val);
    }

    temp->next = traverse;
			temp->previous = traverse->previous;
			traverse->previous->next = temp;
			traverse->previous = temp;
    
  }

/**
     * Public : SortList
     * 
     * Description:
     *     put the values in the list in order
     * 
     * Params:
     *      N/A
     * 
     */

  void Vector::SortList ()
  {
    
    bool changesMade = true;

    //if no changes are made, the function is complete as the list is already sorted
    while (changesMade)
      {
       
        changesMade = false;
        Node * traverse = head;

        
			while (traverse-> next != NULL && traverse != NULL) 
      {	
				if (traverse->data > traverse->next->data) 
        {  
          int leftValue = traverse -> data;
          int rightValue = traverse -> next -> data;
          traverse -> data = rightValue;			
					traverse->next->data = leftValue;
				  leftValue = 0;
          rightValue = 0;
					changesMade = true;
				}

            traverse = traverse -> next;

        }

  }

    }

/**
     * Public : inOrderPush
     * 
     * Description:
     *     add item to list in order
     * 
     * Params:
     *      int
     * 
     */

  void Vector::inOrderPush(int d)
  {

    Node * temp = new Node (d);
    if (head == NULL)
    {
      PushRear(d);
    }

    else if (head -> data > d)
    {
      PushFront(d);
    }

    else if (tail -> data < d)
    {
      PushRear(d);
    }

    else 
    {
        Node * traverse = head;
      while (traverse -> data > d)
        {
          traverse = traverse -> next;
          temp->next = traverse;
			    temp->previous = traverse->previous;
			    traverse->previous->next = temp;
			    traverse->previous = temp;
        }

      traverse = traverse -> next;
          temp->next = traverse;
			    temp->previous = traverse->previous;
			    traverse->previous->next = temp;
			    traverse->previous = temp;
      
    }

    SortList();
    
  }

/**
     * Public : PopAt
     * 
     * Description:
     *      remove item at certain location
     * 
     * Params:
     *      int
     * 
     * Returns:
     *      int      // return item removed
     */

  int Vector::PopAt(int location)
  {

     if (head == NULL || location < 0)
    {
      return -1;
    }

    int index = location;
    int count = 0;
    

    if (index == 0)
    {
      return PopFront();
    }
    
      Node * traverse = head;
      while (count < index)
        {
          traverse = traverse -> next;
          count++;
        }

    if (traverse -> next == NULL)
    {
      return PopRear();
    }

    int poppedNum = traverse -> data;
    traverse -> previous -> next = traverse -> next;
    traverse -> next -> previous = traverse -> previous;

    return poppedNum;

    }


/**
     * Public : Find
     * 
     * Description:
     *      check list for item
     * 
     * Params:
     *      int
     * 
     * Returns:
     *      int      // return item if found
     */

  int Vector::Find(int val)
  {

    int index;
    
    if (head == NULL)
    {
      return -1;
    }
      
    else
  
    {
      Node * traverse = head;
      while (traverse && traverse -> data != val)
        {
          traverse = traverse -> next;
          index++;
        }

      if (!traverse && traverse -> data != val)
      {
        return -1;
      }
    }
    
  return index;
    
  }

/**
     * Public : PopRear
     * 
     * Description:
     *     remove item from back of list
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      int       // return item removed
     */

int Vector::PopRear()
{
  if (head == NULL)
  {
    return -1;
  }

  Node * temp = tail;
  int removedNum = tail -> data;
  tail = tail-> previous;
  tail -> next = NULL;
  temp = nullptr;
  delete temp;
  
  return removedNum;
  
}

/**
     * Public : displayList
     * 
     * Description:
     *     print out the list
     * 
     * Params:
     *      N/A
     * 
     */

void Vector::displayList()
{
  Node * traverse = head;
  while (traverse)
    {
    cout << traverse->data << " ";
      traverse = traverse-> next;
    }

}



/*
  _____   _____ ___ _    ___   _   ___  ___ ___     ___  ___ ___ ___    _ _____ ___  ___  ___
   / _ \ \ / / __| _ \ |  / _ \ /_\ |   \| __|   \   / _ \| _ \ __| _ \  /_\_   _/ _ \| _ \/ __|
  | (_) \ V /| _||   / |_| (_) / _ \| |) | _|| |) | | (_) |  _/ _||   / / _ \| || (_) |   /\__ \
   \___/ \_/ |___|_|_\____\___/_/ \_\___/|___|___/   \___/|_| |___|_|_\/_/ \_\_| \___/|_|_\|___/

*/



    ostream &operator<<(ostream &os, const Vector &v) 
    {
    
      Node * traverse = v.head;
      while (traverse)
      {
        os << traverse->data << " ";
        traverse = traverse-> next;
      }
    return os;
    }






int main() 
{

  ofstream outfile;
  outfile.open("test.out");



  Vector V1;
  V1.PushRear(3);
  V1.PushRear(9);
  V1.PushRear(1);
  V1.PushRear(7);
  V1.PushFront(2);
  
  cout << "V1 is: " << V1 << endl;
  outfile << "V1 is: " << V1 << endl;

  V1.PopRear();
  
  
  cout << "V1 after popping at rear is: " << V1 << endl;
  outfile << "V1 after popping at rear is: " << V1 << endl;



  cout << "searching for 5 in V1: " << V1.Find(5) << endl;
  outfile << "searching for 5 in V1: " << V1.Find(5) << endl;

  

  cout << "Removed value at index 2: " << V1.PopAt(2) << endl;
  outfile << "Removed value at index 2: " << V1.PopAt(2) << endl;


  cout << "V1 is:  " << V1 << endl;
  outfile << "V1 is:  " << V1 << endl;


  V1.PushAt(1, 7);

  cout << "V1 after push at is: " << V1 << endl;
  outfile << "V1 after push at is: " << V1 << endl;


  Vector V2;
  V2.PushRear(31);
  V2.PushRear(12);
  V2.PushRear(4);
  V2.PushRear(53);
  V2.PushRear(93);
  
  cout << "V2 is: " << V2;
  outfile << "V2 is: " << V2;


  V2.SortList();

  cout << endl << "V2 after sort is: " << V2 << endl;
  outfile << endl << "V2 after sort is: " << V2 << endl;


  
   Vector V3("input.dat");

   cout << "V3 is: " << V3 << endl;
   outfile << "V3 is: " << V3 << endl;


  int arr[] = {3, 6, 9, 3};
  Vector V4(arr, 4);

  cout << "V4 is: " << V4 << endl;
  outfile << "V4 is: " << V4 << endl;


  V4.PushFront(V1);

  cout << "V4 after pushing V1 to front is: " << V4 << endl;
  outfile << "V4 after pushing V1 to front is: " << V4 << endl;



  Vector V5(V2);

  cout << "V5 is: " << V5 << endl;
  outfile << "V5 is: " << V5 << endl;


  V5.PushRear(V4);

  cout << "V5 after pushing V4 to rear is: " << V5 << endl;
  outfile << "V5 after pushing V4 to rear is: " << V5 << endl;


  Vector V6;
  V6.PushFront(36);
  V6.PushFront(89);
  V6.PushRear(2);
  V6.PushRear(12);
  V6.PushRear(41);

  cout << "V6 is: " << V6 << endl;
  outfile << "V6 is: " << V6 << endl;


  V6.SortList();
  V6.inOrderPush(23);

  cout << "V6 after sort and push is: " << V6 << endl;
  outfile << "V6 after sort and push is: " << V6 << endl;


  outfile.close();
  
}
