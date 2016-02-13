#include <iostream>
#include "LLQueue.hpp"

int main()
{
  // create the queue
  LLQueue* llq = new LLQueue();

  // put some vlues in the queue
  for (int i = 0; i < 10; ++i)
    llq->enqueue(i);

  // a temporary value to store the dequeued values in
  int temp;

  // dequeue until empty
  while(!llq->isEmpty())
    {
      llq->dequeue(temp);
      std::cout << temp << " ";
    }
  std::cout << std::endl;
}
