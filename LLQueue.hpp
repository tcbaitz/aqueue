#ifndef LLQUEUE_HPP
#define LLQUEUE_HPP

// the struct for individual node
struct Node
{
  int data;
  Node* next;

  Node(const int& num) { data = num; next = 0; }
};

// the class itself
class LLQueue
{
 public:
  /* MEMBERS */
  Node* front;
  Node* rear;

  /* FUNCTIONS */

  // constructor
  LLQueue();

  // destructor
  ~LLQueue();

  // enqueue
  void enqueue(const int&);

  // dequeue
  bool dequeue();

  // peek
  bool peek(int&);

  // isEmpty
  bool isEmpty();
};

LLQueue::LLQueue()
{
  front = rear = 0;
}

LLQueue::~LLQueue()
{
  //int temp;
  while (dequeue()) {}
}

void LLQueue::enqueue(const int& num)
{
  Node* newNode = new Node(num);
  if (front == 0)
    front = rear = newNode;
  else
    {
      // add the node to the end of the list
      rear->next = newNode;
      rear = newNode;
    }
}

bool LLQueue::dequeue()
{
  if (isEmpty())
    return false;

  Node* temp = front;
  // set the value
  int num = 0;
  num = front->data;
  // move the front pointer
  front = front->next;
  delete temp;
  return true;
}

bool LLQueue::peek(int& num)
{
  if (isEmpty())
    return false;

  // set the value
  num = front->data;
  return true;
}

bool LLQueue::isEmpty()
{
  // the list is empty when front us null
  return front == 0;
}

#endif
