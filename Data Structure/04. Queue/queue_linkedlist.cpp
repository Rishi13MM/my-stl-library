#include <iostream>
#include "custom_exception.hpp"

template <typename T>
class Queue
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(const T &value, Node *nextNode = nullptr) : data(value), next(nextNode) {}
  };

  Node *front;
  Node *rear;
  std::size_t itemCount;

protected:
  void clear();
  void copyFrom(const Queue &);

public:
  Queue() : front(nullptr), rear(nullptr), itemCount(0) {}
  Queue(const Queue&);
  Queue& operator=(const Queue&);
  ~Queue();
  void enqueue(const T &);
  void dequeue();
  T getFront() const;
  T getRear() const;
  bool isEmpty() const;
  std::size_t getItemCount() const;
};

template <typename T>
void Queue<T>::enqueue(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    front = rear = newNode;
  }
  else
  {
    rear->next = newNode;
    rear = newNode;
  }

  itemCount++;
}

template <typename T>
void Queue<T>::dequeue()
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty. Cannot remove an item.");
  }

  if (front == rear)
  {
    delete front;
    front = rear = nullptr;
  }
  else
  {
    Node *temp = front;
    front = front->next;
    delete temp;
  }

  itemCount--;
}

template <typename T>
T Queue<T>::getFront() const
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty. Cannot return front of the queue");
  }

  return front->data;
}

template <typename T>
T Queue<T>::getRear() const
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty. Cannot return rear of the queue");
  }

  return rear->data;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
  return itemCount == 0;
}

template <typename T>
std::size_t Queue<T>::getItemCount() const
{
  return itemCount;
}

template <typename T>
void Queue<T>::clear()
{
  while (itemCount != 0)
  {
    dequeue();
  }
}

template <typename T>
void Queue<T>::copyFrom(const Queue &obj)
{
  if (this != &obj)
  {
    clear();

    Node *currentNode = obj.front;
    while (currentNode != nullptr)
    {
      enqueue(currentNode->data);
      currentNode = currentNode->next;
    }
  }
}

template <typename T>
Queue<T>::Queue(const Queue<T>& obj): front(nullptr), rear(nullptr), itemCount(0){
  copyFrom(obj);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& obj){
  copyFrom(obj);
  return *this;
}

template <typename T>
Queue<T>::~Queue(){
  clear();
}