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

## Composition

## Constructor

## Encapsulation

## Friend

## Inheritance

## Instance Variable

## Member Variable

## Method

## Multiple Inheritance

## Object

## Overloading

## Polymorphism

## Static

## Virtual
