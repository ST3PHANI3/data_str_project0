#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

/*
 * Author: Stephanie Alvord
 * Assignment Title: Project 0
 * Assignment Description: Create a stack data structure.
 * Due Date: 01/18/2018
 * Date Created: 01/11/2018
 * Date Last Modified: 01/17/2018
 */

#include "containerInterface.h"
#include <iostream>
using namespace std;

template <typename T>
class myVector : public containerInterface<T> {
public:
    myVector();
    ~myVector();
    myVector(myVector<T>&);
    myVector(myVector<T>&&);
    myVector<T>& operator=(myVector<T>&);
    myVector<T>& operator=(myVector<T>&&);

    containerInterface <T>& pushFront(T);
    containerInterface <T>& pushBack(T);
    containerInterface <T>& popFront() throw(BADINDEX);
    containerInterface <T>& popBack() throw(BADINDEX);
    int getSize() const;
    bool full() const;
    bool empty() const;
    T front() const throw(BADINDEX);
    T back() const throw(BADINDEX);
    T& operator[](int) throw(BADINDEX);
    void erase();

private:
    T *data; //data - points to an array of type T.
    int size, capacity;
    void grow();
    void shiftRight();
    void shiftLeft();
};

/*
 * description: class constructor
 * return: nothing
 * precondition: none
 * postcondition: class object created with size = 0, capacity = 10, data
 *      points to an array of size capacity and type T
 *
 */
template <typename T>
myVector<T>::myVector() {
    this->size = 0;
    this->capacity = 10;
    this->data = new T[this->capacity];
}

 /*
  * description: class destructor
  * return: nothing
  * precondition: a myVector object exists
  * postcondition: all memory allocated to the myVector is deleted
  *
  */
template <typename T>
myVector<T>::~myVector() {
    if (this->data) {
        delete[] this->data;
        this->data = NULL;
    }
}

/*
 * description: class copy constructor
 * return: nothing
 * precondition: a myVector object exists
 * postcondition: a copy of the class object v is made
 *
 */
template <typename T>
myVector<T>::myVector(myVector<T>& v) {
    this->size = v.size;
    this->capacity = v.capacity;
    this->data = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->data[i] = v.data[i];
}

/*
 * description: move constructor
 * return: nothing
 * precondition: a myVector object exists
 * postcondition: a copy of the class object v is made
 *
 */
template <typename T>
myVector<T>::myVector(myVector<T> &&v)
    : size(v.size), capacity(v.capacity){
    swap(this->data,v.data);
    v.size = 0;
    v.capacity = 0;
    v.data = NULL;
}

/*
 * description: add data element e to the front of the vector
 * return: a reference to self
 * precondition: a myVector object exists
 * postcondition: if size == capacity, double capacity shifts all elements in
 *      data to the right; data element e has been added to the front of the
 *      array; increrment size
 *
 */
template <typename T>
containerInterface<T>& myVector<T>::pushFront(T e) {
    if (this->size == this->capacity)
        grow();
    //cout << "--pushing " << e << endl;
    shiftRight();
    this->data[0] = e;
    //cout << "front = " << this->data[0] << endl;
    this->size++;
    return *this;
}

/*
 * description: store data element e in end of the vector
 * return: a reference to self
 * precondition: a myVector object exists
 * postcondition: if size == capacity, double capacity; data element e has been
 *      added to the end of the array; increment size
 *
 */
template <typename T>
containerInterface<T>& myVector<T>::pushBack(T e) {
    if (this->size == this->capacity)
        grow();
    //cout << "--pushing " << e << endl;
    this->data[this->size] = e;
    //cout << "back = " << this->data[this->size] << endl;
    this->size++;
    return *this;
}

/*
 * description: removes a data element from the front of the data structure
 *      (myVector)
 * return: a reference to self
 * precondition: an object exists
 * postcondition: the first element has been removed from the front of the
 *      myVector; decrement size
 * error: if the list is empty throw a BADINDEX exception
 *
 */
template <typename T>
containerInterface<T>& myVector<T>::popFront() throw(BADINDEX){
    try {
        if (empty())
            throw BADINDEX();
        shiftLeft();
        this->size--;
        return *this;
    }
    catch (BADINDEX) {
        return *this;
    }
}

/*
 * description: removes a data element from the rear (end) of the data
 *      structure (myVector)
 * return: a reference to self
 * precondition: an object exists
 * postcondition: a data element has been removed from the rear of the
 *      myVector; decrement current size
 * error: if the list is empty throw a BADINDEX exception
 *
 */
template <typename T>
containerInterface<T>& myVector<T>::popBack() throw(BADINDEX){
    try {
        if (empty())
            throw BADINDEX();
        this->size--;
        return *this;
    }
    catch (BADINDEX) {
        return *this;
    }
}

/*
 * description: returns the number of elements currently in myVector
 * return: an integer value representing the number of elements in the list
 * precondition: an object exists
 * postcondition: the myVector is unchanged
 *
 */
template <typename T>
int myVector<T>::getSize() const {
    return this->size;
}

/*
 * description: returns state information about the list
 * return: true if the myVector cannot grow; false otherwise
 * precondition: an object exists
 * postcondition: object is unchanged
 *
 */
template <typename T>
bool myVector<T>::full() const {
    if (this->size != this->capacity)
        return false;
    else
        return true;
}

/*
 * description: returns state information about the list
 * return: true if the myVector is empty; false otherwise
 * precondition: an object exists
 * postcondition: the myVector is unchanged
 *
 */
template <typename T>
bool myVector<T>::empty() const {
    if (this->size != 0)
        return false;
    else
        return true;
}

/*
 * description: returns a copy of the first data item in myVector
 * return: type T - first item (top) on stack
 * precondition: an object exists
 * postcondition: the object is unchanged
 * error: throw BADINDEX if the myVector is empty
 *
 */
template <typename T>
T myVector<T>::front() const throw(BADINDEX) {
    try {
        if (empty())
            throw BADINDEX();
        return this->data[0];
    }
    catch (BADINDEX) {
        T thing;
        return thing;
    }
}

/*
 * description: returns a copy of the last data item in myVector
 * return: type T - last item on stack
 * precondition: an object exists
 * postcondition: the object is unchanged
 * error: throw BADINDEX if the myVector is empty
 *
 */
template <typename T>
T myVector<T>::back() const throw(BADINDEX) {
    try {
        if (empty())
            throw BADINDEX();
        return this->data[this->size - 1];
    }
    catch (BADINDEX) {
        T thing;
        return thing;
    }
}

/*
 * description: returns a reference to data element n in myVector
 * return: type T - number where element n is found
 * precondition: an object exists
 * postcondition: the object is unchanged
 * error: throw BADINDEX if n >= capacity or n < 0
 *
 */
template <typename T>
T& myVector<T>::operator[](int n) throw(BADINDEX) {
    try {
        if (n < 0 || n > this->capacity)
            throw BADINDEX();
        return this->data[n];
    }
    catch (BADINDEX) {
        cout << "invalid input" << endl;
    }
    return this->data[0];
}

/*
 * description: erases the vector
 * return: void
 * precondition: an object exists
 * postcondition: the object size is set to 0
 *
 */
template <typename T>
void myVector<T>::erase() {
    for(int i = 0; i < this->size; i++)
        shiftLeft();
    this->size = 0;
}

/*
 * description: overloaded assignment operator
 * return: *this
 * precondition: an object exists
 * postcondition: the object n is unchanged and *this is an exact copy of n
 *
 */
template <typename T>
myVector<T>& myVector<T>::operator=(myVector<T> &n) {
    this->capacity = n.capacity;
    this->size = n.size;
    if (this->data)
        delete[] this->data;
    this->data = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->data[i] = n.data[i];
    return *this;
}

/*
 * description: overloaded move assignment operator
 * return: *this
 * precondition: an object exists
 * postcondition: the object n is unchanged and *this is moved to n
 *
 */
template <typename T>
myVector<T>& myVector<T>::operator=(myVector<T> &&n) {
    if (this != &n) {
        delete[] this->data;
        this->size = n.size;
        this->capacity = n.capacity;
        swap(this->data,n.data);

        n.size = 0;
        n.capacity = 0;
        n.data = NULL;
    }
    return *this;
}

/*
 * description: doubles the capacity of the vector
 * return: void
 * precondition: an object exists
 * postcondition: capacity is doubled, new memory is allocated and the
 *      information stored in data is copied in the new memory; old memory is
 *      deallocated; data points to the new memory
 *
 */
template <typename T>
void myVector<T>::grow() {
    this->capacity *= 2;
    T *temp = new T[this->size];
    for(int i = 0; i < this->size; i++)
        temp[i] = this->data[i];
    this->data = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->data[i] = temp[i];
}

/*
 * description: shifts all the information stored in data one position to the
 *      right, increments size, and grows the vector if size > capacity
 * return: void
 * precondition: an object exists
 * postcondition: data values are shifted right one spot
 *
 */
template <typename T>
void myVector<T>::shiftRight() {
    if (this->size == this->capacity)
        grow();
    T *temp = new T[this->size];
    for(int i = 0; i < this->size; i++)
        temp[i] = this->data[i];
    this->data = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->data[i] = temp[i - 1];
}

/*
 * description: if size > 0, it shifts all the information stored in data one
 *      position to the left, removing the first element, and decrements size
 * return: void
 * precondition: an object exists
 * postcondition:
 *
 */
template <typename T>
void myVector<T>::shiftLeft() {
    for (int i = 0; i < this->size; i++)
        this->data[i] = this->data[i + 1];
}

#endif // MYVECTOR_H_INCLUDED
