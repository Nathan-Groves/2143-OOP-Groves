# OOP Terms

## Abstraction
One of the three main concepts of OOP. Specifically, it refers to the hiding of all but the relevant data in a class in order to minimize complexity and increase efficiency.

```
class Car {
private:
int gas;

public:

int getGas();

};

```


## Access Modifiers
Are known as access specifiers, and denote the ability of a class to access the members and data of the class. 

###### Private
Can only be accessed my member functions within the class.


###### Public
Can be accessed by any object from the class or a subclass.


###### Protected
Can be accessed by derived subclasses, but not the class itself

```
class Bank {
private:
int money;

protected:
int safePasscode;

public: 
int getMoney ();

};

```

## Attributes & Properties
Refers to the characteristics in a program or Class that may be changed. In classes, attributes are often found in the private section.

```
class Burger {
private:
int ketchup;
int mayo;

public:

void setMayoAmount(int m)
{
mayo = m;
}

};

```

## Class
An aggregate of data members and functions that may be used to create instances, or “objects” from using the class definition.

```
class Basket {
private:
int apples;
int oranges;

public:
int getApples  ();
void setApples ();
int getOranges ();
void setOranges();

};

```

## Class Variable
A variable within a class in which there is only one instance of, regardless of how many objects are made. Made using the static keyword.



![This is an image](https://miro.medium.com/max/1200/1*axRkrkV0erk1dbNlTQ-q6g.png)

## Composition
Similar to inheritance in that it applies attributes of one class to another, but different in how it does so. In composition, an instance of a class is made in the definition of another class.

```
class Parent {
private:
int inheritance = 500;

public:
void printInheritance()
{
cout << inheritance;
}

};

class Child {
private:
Parent P;

public:
Child()
{
P.printInheritance();
}

};

```

## Constructor
Allows the ability to create an instance of a class, typically with already set values for certain members. Always has the same name as the Class and is found in public with no return type.

```
class Person {
private:
int age;

public:
void setAge(int a);
Person()
{
age = 20;
}


};
```

## Encapsulation
The grouping of data together in functions to hide implementation and streamline use, as well as using private access specifiers to restrict access.


![This is an image](https://xperti.io/blogs/wp-content/uploads/2021/12/xblog-Encapsulation.png)

## Friend
Keyword denoting the ability of a class to access data members and functions not defined within itself.

```
class Hotel {
int occupants = 10;

public:
friend void printOccupants();

};

void printOccupants()
{
cout << occupants;
}

```

## Inheritance
The gaining of data members and functions from one class to another, useful when making derivative classes that would need the same functions and data members as the parent class.

```
class Building {
string foundation;
int landArea;
int height;
int occupants;

public:
void printHeight();

};

class Hotel: public Building {
int occupants = 10;

public:
void printOccupants();

};

```

## Instance Variable
Variables made and contained within classes that are unique to each instance of a class.

```
class Aquarium {
private:
int numOfCatfish;
int numOfSquid;
int numOfCrabs;

};

```

## Member Variable
Variables made and contained within classes that are accessible using member methods.

```
class Aquarium {
private:
int numOfCatfish;

public:
void setCatfish();
int getCatfish(int c);

};

```

## Method
A function contained within a class that can be called to modify and fetch data within the class.

```
class Game {
private:
int Score;

public:
void getScore();
int setScore();

};

```

## Multiple Inheritance
Refers to instances wherein a derived class inherits from multiple base classes.

```
class Organism{};
class Human{};
class Child: public Organism, public Human{};

```

## Object

## Overloading

## Polymorphism

## Static

## Virtual
