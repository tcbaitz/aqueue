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

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

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
    int START_SIZE = 32768;
    int INCREMENT_FACTOR = 2;
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

            for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();

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
                 //x.enqueue(256);
                 //algorithm(i, x);
               }
                timer1.stop();
                stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            stats[i].report(cout);
            stats[i].report(ofs);
        }

        cout << endl;
        ofs << endl;
        current_size *= INCREMENT_FACTOR;
    }
    return 0;
}




/*
//attempt 2
using namespace std;

// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

const int number_of_algorithms = 1;
const int number_of_trials = 7;

// NOTICE factor is going to influence the "extra" time
const int factor = 5000;

void polulate(queue<int> &, int);

// This template function is to specify which algorithms are used in the timing experiment
template <class container>
inline void algorithm(int k, container &x, int some_size)
{
    switch (k)
    {
        //case 0: populate(x, some_size);
        case 0: x.push(256);
    }
}

// STABLE SORT: sorts the elements in the range [first,last), like sort, but preserves the relative order of the elements with equivalent values-from STL
// SORT: (the Quicksort algorithm, using the median-of-3 method of choosing pivot elements for partitioning)-from STL
// Quick sort: Our user written sorting algorithm

const char* headings[number_of_algorithms] =
{"| push time      "};

int main()
{
    int START_SIZE = 2;
    int INCREMENT_FACTOR = 2;
    int current_size = START_SIZE;
    int max_size = START_SIZE^(INCREMENT_FACTOR*number_of_trials);
// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the queues x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    queue<U> x;

    //int repetitions = START_SIZE * (INCREMENT_FACTOR^number_of_trials);

    cout << "____";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "Size";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;



    for (int count = 0; count < number_of_trials; count ++)
    {
        //int current_size = START_SIZE * (INCREMENT_FACTOR^count);
        cout << setw(4) << current_size << flush;
        ofs << setw(4) << current_size;

        //resets stats
        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

// Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
// (The repetitions factor is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();
               for (int k = 0; k < current_size; ++k)
               {
                 algorithm(i, x, k);
               }
               timer1.stop();
               stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            stats[i].report(cout, current_size);
            stats[i].report(ofs, current_size);
        }

        cout << endl;
        ofs << endl;
        current_size *= 4;
    }
    return 0;
}

void populate(queue<int> &x, int some_size){
    for(int count = 0; count < some_size; count++){
        x.push(count);
    }
}

//example implementation
// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

// experiment will involve timing of 3 algorithms and that the number of "trials" will be 7.
// By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median.
// (The median computation is done in class recorder.)
// The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.

const int number_of_algorithms = 2;
const int number_of_trials = 7;

// NOTICE factor is going to influence the "extra" time
const int factor = 5000;

// This template function is to specify which algorithms are used in the timing experiment
template <class container>
inline void algorithm(int k, container &q, int append_this)
{
    switch (k)
    {
        case 0: q.push(append_this);
            break;
        case 1: q.pop();
    }
}

// STABLE SORT: sorts the elements in the range [first,last), like sort, but preserves the relative order of the elements with equivalent values-from STL
// SORT: (the Quicksort algorithm, using the median-of-3 method of choosing pivot elements for partitioning)-from STL
// Quick sort: Our user written sorting algorithm

const char* headings[number_of_algorithms] =
{"| Enqueue time   ",
 "| Degueue Time   "};

int main()
{

    //int add_to_queue = 0;
    //int multiplier = 2;
    //int queue_start_size = 2;
    //int queue_size = 0;
    //int max_queue_size = (queue_start_size ^ number_of_trials);


    int N0, N1, N2, N, K = 0;
    N1 = 1;    // smallest sequence
    N2 = 1000; // largest sequence

// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

    //declare aqueue
    //AQueue<int> s1;
    queue<U> s1;

    //
    int repetitions = max(32/N1, 1);

    //the number of times the queue size will increase
    //int repetitions = number_of_trials;

    //writes table headings
    cout << "____";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "Size";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;

    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        N = N0 * factor;

        K = N/2;
        cout << setw(4) << N0 << flush;
        ofs << setw(4) << N0;

        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

// Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
// (The repetitions factor is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               timer1.restart();
               for (int k = 0; k < repetitions; ++k)
               {
                 algorithm(i, s1, K);
               }
               timer1.stop();
               stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << endl;
        ofs << endl;

        //s1.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }
}
*/
