#include <iostream>
#include "custom_exception.hpp"

template <typename T>
class PriorityQueue
{
public:
  enum Priority
  {
    LOW = 1,
    MEDIUM,
    HIGH
  };

private:
  struct Node
  {
    Priority priority;
    T data;
    Node *next;
    Node(const T &value, const Priority nodePriority, Node *nextNode = nullptr) : data(value), priority(nodePriority), next(nextNode) {}

  };

  Node *front; // Pointer to the front (highest-priority element)
  Node *rear; // // Pointer to the rear (lowest-priority element)
  std::size_t size;

protected:
  void clear();
  void copyFrom(const PriorityQueue &);

public:
  PriorityQueue() : front(nullptr), rear(nullptr), size(0) {}
  PriorityQueue(const PriorityQueue &);
  PriorityQueue &operator=(const PriorityQueue &);
  ~PriorityQueue();

  void enqueue(const T &, const Priority);
  void dequeue();
  // Return the highest-priority element
  T getFront() const;
  // Return the lowest-priority element
  T getRear() const;
  bool isEmpty() const;
  std::size_t getSize() const;
};

template <typename T>
void PriorityQueue<T>::enqueue(const T &value, const Priority priority)
{
  Node *newNode = new Node(value, priority);

  if (isEmpty())
  {
    front = rear = newNode;
    size++;
    return;
  }

  if (priority > front->priority)
  {
    newNode->next = front;
    front = newNode;
    size++;
    return;
  }

  Node *currentNode = front;

  while (currentNode->next != nullptr && priority <= currentNode->next->priority)
  {
    currentNode = currentNode->next;
  }

  newNode->next = currentNode->next;
  currentNode->next = newNode;

  if (currentNode == rear)
  {
    rear = newNode;
  }

  size++;
}

template <typename T>
void PriorityQueue<T>::dequeue()
{
  if (isEmpty())
  {
    throw Underflow("PriorityQueue is empty. Cannot remove the front.");
  }

  if (front == rear)
  {
    delete front;
    front = rear = nullptr;
  }
  else
  {
    Node *tempNode = front;
    front = front->next;
    delete tempNode;
  }

  size--;
}

template <typename T>
T PriorityQueue<T>::getFront() const
{
  if (isEmpty())
  {
    throw Underflow("PriorityQueue is empty. Cannot return the front.");
  }

  return front->data;
}

template <typename T>
T PriorityQueue<T>::getRear() const
{
  if (isEmpty())
  {
    throw Underflow("PriorityQueue is empty. Cannot return the rear.");
  }

  return rear->data;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
std::size_t PriorityQueue<T>::getSize() const
{
  return size;
}

template <typename T>
void PriorityQueue<T>::clear()
{
  Node *currentNode = front;

  while (currentNode)
  {
    Node *tempNode = currentNode;
    currentNode = currentNode->next;
    delete tempNode;
  }

  front = rear = nullptr;
  size = 0;
}

template <typename T>
void PriorityQueue<T>::copyFrom(const PriorityQueue &obj)
{
  if (this != &obj)
  {
    clear();

    Node *currentNode = obj.front;
    while (currentNode != nullptr)
    {
      Node *newNode = new Node(currentNode->data, currentNode->priority);
      if (isEmpty())
      {
        front = rear = newNode;
      }
      else
      {
        rear->next = newNode;
        rear = newNode;
      }

      currentNode = currentNode->next;
    }
    size = obj.size;
  }
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
  clear();
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue &obj) : front(nullptr), rear(nullptr), size(0)
{
  copyFrom(obj);
}

template <typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue &obj)
{
  if (this != &obj)
  {
    copyFrom(obj);
  }

  return *this;
}
