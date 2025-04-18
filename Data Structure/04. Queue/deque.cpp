#include <iostream>
#include "custom_exception.hpp"

template <typename T>
class Deque
{
private:
  struct Node
  {
    Node *prev;
    T data;
    Node *next;

    // It initializes all member variables of node
    Node(const T &value, Node *prevNode = nullptr, Node *nextNode = nullptr) : data(value), prev(prevNode), next(nextNode) {};
  };

  Node *front;
  Node *rear;
  std::size_t size;

protected:
  // Release the memory of an object
  void clear();

  // Deep Copy the the values from given object to caller object
  void copyFrom(const Deque &);

public:
  Deque() : front(nullptr), rear(nullptr), size(0) {};
  Deque(const Deque &);
  Deque &operator=(const Deque &);
  ~Deque();

  void enqueueFront(const T &);
  void enqueueRear(const T &);
  void dequeueFront();
  void dequeueRear();
  bool isEmpty() const;
  T peekFront() const;
  T peekRear() const;
  std::size_t getSize() const;
};

template <typename T>
void Deque<T>::enqueueFront(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    front = rear = newNode;
  }
  else
  {
    newNode->next = front;
    front->prev = newNode;
    front = newNode;
  }

  size++;
}

template <typename T>
void Deque<T>::enqueueRear(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    front = rear = newNode;
  }
  else
  {
    newNode->prev = rear;
    rear->next = newNode;
    rear = newNode;
  }

  size++;
}

template <typename T>
void Deque<T>::dequeueFront()
{
  if (isEmpty())
  {
    throw Underflow("Deque is empty. Cannot remove the front element.");
  }

  // if only one element is present
  if (front == rear)
  {
    delete front;
    front = rear = nullptr;
  }
  else
  {
    front = front->next;
    delete front->prev; // font->prev is the original front element.
    front->prev = nullptr;
  }

  size--;
}

template <typename T>
void Deque<T>::dequeueRear()
{
  if (isEmpty())
  {
    throw Underflow("Deque is empty. Cannot remove the rear element.");
  }

  // if only one element is present
  if (front == rear)
  {
    delete front;
    front = rear = nullptr;
  }
  else
  {
    rear = rear->prev;
    delete rear->next; // rear->next is the original last (rear) element.
    rear->next = nullptr;
  }

  size--;
}

template <typename T>
bool Deque<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
T Deque<T>::peekFront() const
{
  if (isEmpty())
  {
    throw Underflow("Deque is empty. Cannot peek the front element.");
  }

  return front->data;
}

template <typename T>
T Deque<T>::peekRear() const
{
  if (isEmpty())
  {
    throw Underflow("Deque is empty. Cannot peek the rear element");
  }

  return rear->data;
}

template <typename T>
std::size_t Deque<T>::getSize() const
{
  return size;
}

template <typename T>
void Deque<T>::clear()
{
  while (front != nullptr)
  {
    Node *tempNode = front;
    front = front->next;
    delete tempNode;
  }

  // Reset dequeue to empty state
  rear = nullptr; // front is already pointing to nullptr
  size = 0;
}

template <typename T>
void Deque<T>::copyFrom(const Deque &obj)
{
  if (this != &obj)
  {
    clear();

    // Copying the values from given deque object to caller queue object
    Node *currentNode = obj.front;
    while (currentNode)
    {
      Node *newNode = new Node(currentNode->data);
      if (isEmpty())
      {
        front = rear = newNode;
      }
      else
      {
        newNode->prev = rear;
        rear->next = newNode;
        rear = newNode;
      }
      currentNode = currentNode->next;
    }
    size = obj.size;
  }
}

template <typename T>
// Initialize the member variables to prevent the undefined behaviour in clear function.
Deque<T>::Deque(const Deque &obj) : front(nullptr), rear(nullptr), size(0)
{
  copyFrom(obj);
}

template <typename T>
Deque<T> &Deque<T>::operator=(const Deque &obj)
{
  copyFrom(obj);
  return *this;
}

template <typename T>
Deque<T>::~Deque()
{
  clear();
}
