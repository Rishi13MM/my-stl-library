#include <iostream>
#include "custom_exception.hpp"

// Cirular Queue (a queue using circular array under the hood is called circular queue).
template <typename T>
class Queue
{
private:
  int capacity;
  int itemCount;
  T *ptr;
  int front;
  int rear;

protected:
  void clear(); // it releases the memory
  void copyFrom(const Queue &);

public:
  Queue(int);
  Queue(const Queue &);
  Queue &operator=(const Queue &);
  ~Queue();

  void enqueue(const T &);
  void dequeue();
  T getFront() const;
  T getRear() const;
  int getItemCount() const;
  bool isEmpty() const;
  bool isFull() const;
};

template <typename T>
Queue<T>::Queue(int size)
{
  if (size < 1)
  {
    throw InvalidQueueSize("Size of queue using array must be a natural number.");
  }

  ptr = new T[size];
  capacity = size;
  itemCount = 0;
  front = 0;
  rear = -1;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &obj)
{
  if(this == &obj){
    throw SelfAssignmentException("Cannot perform the self assignment operation during declaration (object creation).");
  }

  copyFrom(obj);
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &obj)
{
  copyFrom(obj);
  return *this;
}

template <typename T>
Queue<T>::~Queue()
{
  clear();
}

template <typename T>
void Queue<T>::enqueue(const T &data)
{
  if (isFull())
  {
    throw Overflow("Queue is full!");
  }

  rear = (rear + 1) % capacity;
  ptr[rear] = data;

  itemCount++;
}

template <typename T>
void Queue<T>::dequeue()
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty!");
  }

  front = (front + 1) % capacity;
  itemCount--;

  if(itemCount==0){
    front=0;
    rear = -1;
  }
}

template <typename T>
bool Queue<T>::isEmpty() const
{
  return itemCount == 0;
}

template <typename T>
bool Queue<T>::isFull() const
{
  return itemCount == capacity;
}

template <typename T>
T Queue<T>::getFront() const
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty!");
  }

  return ptr[front];
}

template <typename T>
T Queue<T>::getRear() const
{
  if (isEmpty())
  {
    throw Underflow("Queue is empty!");
  }

  return ptr[rear];
}

template <typename T>
int Queue<T>::getItemCount() const
{
  return itemCount;
}

template <typename T>
void Queue<T>::clear()
{
  delete[] ptr;
  ptr = nullptr;
  itemCount = 0;
  front = 0;
  rear = -1;
  capacity = 0;
}

template <typename T>
void Queue<T>::copyFrom(const Queue<T> &obj)
{
  if (this == &obj)
  {
    return;
  }

  if (capacity != obj.capacity)
  {
    clear();
    ptr = new T[obj.capacity];
  }

  capacity = obj.capacity;
  itemCount = obj.itemCount;
  front = obj.front;
  rear = obj.rear;

  if (!obj.isEmpty())
  {
    int i = front;
    do
    {
      ptr[i] = obj.ptr[i];
      i = (i + 1) % capacity;
    } while (i != (rear + 1) % capacity);
  }
}
