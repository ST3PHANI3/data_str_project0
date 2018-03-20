#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED

/*
 * Author: Stephanie Alvord
 * Assignment Title: Project 1
 * Assignment Description: Create a stack data structure.
 * Due Date: 01/25/2018
 * Date Created: 01/24/2018
 * Date Last Modified: 01/25/2018
 */

 #include "myVector.h"

template<class T, class C = myVector<T> >
class myStack{
public:
    myStack();
    myStack(const myStack<T,C>&);
    myStack(myStack<T,C>&&);
    myStack<T,C>& operator=(myStack<T,C>&);
    myStack<T,C>& operator=(myStack<T,C>&&);
    ~myStack();
    bool empty();
    T top();
    myStack<T,C>& push(T x);
    myStack<T,C>& pop();
private:
    C container;
};

template<class T, class C>
myStack<T,C>::myStack(){

}

template<class T, class C>
myStack<T,C>::myStack(const myStack<T,C>&that){
    this->container = that.container;
}

template<class T, class C>
myStack<T,C>::myStack(myStack<T,C>&&that){
    swap(this->container, that.container);
}

template<class T, class C>
myStack<T,C>& myStack<T,C>::operator=(myStack<T,C>&that){
    this->container = that.container;
    return *this;
}

template<class T, class C>
myStack<T,C>& myStack<T,C>::operator=(myStack<T,C>&&that){
    swap(this->container, that.container);
    return *this;
}

template<class T, class C>
myStack<T,C>::~myStack(){

}

template<class T, class C>
bool myStack<T,C>::empty(){
    if(container.empty())
        return true;
    else
        return false;
}

/*
 * description: top
 * return: T - the top of the stack
 * precondition: an object exists
 * postcondition: the object is unchanged
 *
 */
template<class T, class C>
T myStack<T,C>::top(){
    return container.back();
}

/*
 * description: push
 * return: *this
 * precondition: an object exists
 * postcondition: the object x is pushed onto the stack
 *
 */
template<class T, class C>
myStack<T,C>& myStack<T,C>::push(T x){
    container.pushBack(x);
    return *this;
}

/*
 * description: pop
 * return: *this
 * precondition: an object exists
 * postcondition: the back object is removed
 *
 */
template<class T, class C>
myStack<T,C>& myStack<T,C>::pop(){
    container.popBack();
    return *this;
}

#endif // MYSTACK_H_INCLUDED
