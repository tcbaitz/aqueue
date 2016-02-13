#ifndef AQUEUE_HPP
#define AQUEUE_HPP

template <class T>
class EMAQueue {
public:
  EMAQueue(int size) {
    this->size = size;
    this->start = 0;
    this->count = 0;
    this->array = new T[size];
  }

  ~EMAQueue() { delete [] array; }

  bool enqueue(T t) {
    //Ensure we have enough space to handle a new element
    if (count >= size) return false;
    //Insert the element at start + count, mod size
    //We mod by size to wrap around once our start beings to move forward
    array[(start + count++) % size] = t;
    //Count is incremented by one above
    return true;
  }

  bool dequeue() {
    //Ensure we have something to dequeue
    if (count < 1) return false;
    //Retrieve element from start
    T t;
    t = array[start++];
    //Increment and mod start by size to proceed to next value and wrap wround
    start %= size;
    //Decrement our count
    --count;
    return true;
  }

  int elements() { return count; }

  bool empty() { return count == 0; }

  T operator[](int n) const {
      return (array[n]);
  }

  T &operator[](int n) {
      return (array[n]);
  }

public:
  int size;
  int start;
  int count;
  T *array;
};

#endif
