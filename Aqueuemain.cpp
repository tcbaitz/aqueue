// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Test program for the array-based queue class

#include "book.hpp"
#include "aqueue.hpp"
#include "EMaqueue.hpp"
#include "LLQueue.hpp"

//#include "QueueTest.hpp"
#include <queue>
#include <deque>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle

#include "Complexity_Timer.hpp"

#include "Complexity_Recorder.hpp"

using namespace std;

// timer
timer timer1;

// U can be any type we want to test.
typedef int U;

//total number of algorithims being tested
const int number_of_algorithms = 10;
//the number times the number of elements will be multiplied
const int number_of_trials = 11;

const char* headings[number_of_algorithms] =
{"| EM Array Queue ",
 "| Book ArrayQueue",
 "| STL Queue      ",
 "| LinkedListQueue",
 "| STL Deque      ",
 "| EM Dequeue     ",
 "| Book Dequeue   ",
 "| STL Queue Pop  ",
 "| LinkedListQueue",
 "| STL Deque"};

int main()
{
    const int START_SIZE = 32768;
    const int INCREMENT_FACTOR = 2;
    int current_size = START_SIZE;
//    int max_size = START_SIZE^(INCREMENT_FACTOR*number_of_trials);
// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the queues x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    //EMAQueue<U> x(current_size);

    cout << "________";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "  Size  ";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;



    for (int count = 0; count < number_of_trials; count ++)
    {
        //displays the number of elements that will be added to the data structures
        cout << setw(8) << current_size << flush;
        ofs << setw(8) << current_size;
        //resets stats
        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        //start of testing
        for (int j = 0; j < number_of_trials; ++j)
        {
            //initialize data structures each trial
            EMAQueue<U> EMQ(current_size);
            AQueue<U> AQ(current_size);
            queue<U> STLQ;
            LLQueue LLQ;
            deque<int> DQ;
            //does test for each algorithm
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               //resets timer
               timer1.restart();
                //completes the test "current_size" times
               for (int k = 0; k < current_size; ++k)
               {
                 //data type operations to be tested
                 switch (i)
                {
                    case 0: EMQ.enqueue(256);
                        break;
                    case 1: AQ.enqueue(256);
                        break;
                    case 2: STLQ.push(256);
                        break;
                    case 3: LLQ.enqueue(256);
                        break;
                    case 4: DQ.push_back(256);
                        break;
                    case 5: EMQ.dequeue();
                        break;
                    case 6: AQ.dequeue();
                        break;
                    case 7: STLQ.pop();
                        break;
                    case 8: LLQ.dequeue();
                        break;
                    case 9: DQ.pop_front();
                }
               }
                //stops timer
                timer1.stop();
                //records stats
                stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            //outputs results console
            stats[i].report(cout);
            //outputs results to file
            stats[i].report(ofs);
        }

        cout << endl;
        ofs << endl;
        //multiply the number of elements to be tested by "INCREMENT_FACTOR"
        current_size *= INCREMENT_FACTOR;
    }
    return 0;
}
