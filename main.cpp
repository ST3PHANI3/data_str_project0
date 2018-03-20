/*
 * Author: Stephanie Alvord
 * Assignment Title: Project 2
 * Assignment Description: Program trace verification
 * Due Date: 02/01/2018
 * Date Created: 01/30/2018
 * Date Last Modified: 01/31/2018
 */
#include <iostream>
#include <string>
#include "myStack.h"
#include <cassert>
#include <sstream>
using namespace std;

const int CALL_LENGTH = 5;
const int RETURN_LENGTH = 7;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  Determines whether or not a trace is valid
 */
int main(int argc, char **argv) { //argc is the # of arguments from the
                                  //command line
                                  //argv is the command line argument values
    string line;
    string temp;

    myStack<string> callStack;

    size_t lineNumber = 0; //an unsigned integer type commonly used for counts
    size_t maximumDepth = 0;

    int depth = 0;
    bool last = true;

    while (getline(cin, line)) { //istream
        lineNumber++;

        if(line[0] == 'c'){ //checks if call or return
            line.erase(0,CALL_LENGTH);
            callStack.push(line); //pushes into stack
            depth++;
        }
        else { //return
            line.erase(0,RETURN_LENGTH);

            //checks if stack is empty or not
            if(!callStack.empty()){ //not empty
                temp = callStack.top();

                if(temp != line){ //if matches, exits statement & pops,
                    cout << "Invalid trace at line " << lineNumber << endl;

                    bool found = false;
                    string arr[100000]; int i = 0;
                    while(found == false && !callStack.empty()){
                        arr[i] = callStack.top();
                        callStack.pop();
                        if(arr[i] == line)
                            found = true;
                        i++;
                    }
                    if(found == true){
                        cout << "Returning from " << line << " instead of "
                             << temp << endl;
                        cout << "Stack trace:" << endl;
                        for(int j = 0; j < i; j++)
                            cout << arr[j] << endl;
                        while(!callStack.empty()){
                            cout << callStack.top() << endl;
                            callStack.pop();
                        }
                    }
                    else{
                        cout << "Returning from " << line << " which was not"
                             << " called" << endl;
                        cout << "Stack trace: " << endl;
                        for(int j = 0; j < i; j++)
                            cout << arr[j] << endl;
                    }

                    return 0;
                }
            }
            else{ //empty stack
                cout << "Invalid trace at line " << lineNumber << endl;
                cout << "Returning from " << line << " which was not called"
                    << endl;
                cout << "Stack trace:" << endl;

                return 0;
            }

            callStack.pop();
            depth--;
        }

        if(depth > maximumDepth)
            maximumDepth = depth;
    }

    if(!callStack.empty()){ //checks if there's still stuff in the stack
        cout << "Invalid trace at line " << lineNumber << endl;
        cout << "Not all functions returned" << endl;
        cout << "Stack trace:" << endl;
        while(!callStack.empty()){
            cout << callStack.top() << endl;
            callStack.pop();
        }
    }
    else{ //if there isn't stuff in the stack
        cout << "Valid trace" << endl;
        cout << "Maximum call depth was " << maximumDepth << endl;
    }

    return 0;
}
