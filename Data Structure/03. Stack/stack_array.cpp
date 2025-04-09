#include <iostream>
#include "custom_exception.hpp"

template <typename T>
class Stack
{
private:
  int capacity;
  int top;
  T *ptr;

protected:
  // Copy elements from the given object to caller object
  void copyFrom(const Stack &);

  // It release the memory of a stack object
  void clear();

public:
  Stack(int);
  ~Stack();
  Stack(const Stack &);
  Stack &operator=(const Stack &);

  void push(const T &);
  T pop();
  T peek() const;
  bool isEmpty() const;
  bool isFull() const;
  int getCapacity() const;

  // friend functions
  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const Stack<U> &);
};

template <typename T>
Stack<T>::Stack(int size)
{
  if (size < 1)
  {
    throw InvalidCapacity("Size of an array must be greater than zero.");
  }

  ptr = new T[size];
  capacity = size;
  top = -1;
}

template <typename T>
Stack<T>::~Stack()
{
  clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &obj)
{
  ptr = nullptr;
  copyFrom(obj);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &obj)
{
  copyFrom(obj);
  return *this;
}

template <typename T>
void Stack<T>::push(const T &value)
{
  if (isFull())
  {
    throw Overflow("Stack is full!");
  }

  top++;
  ptr[top] = value;
}

template <typename T>
T Stack<T>::pop()
{
  if (isEmpty())
  {
    throw Underflow("Stack is empty!");
  }

  T popped = ptr[top];
  top--; 
  return popped;
}

template <typename T>
T Stack<T>::peek() const
{
  if (isEmpty())
  {
    throw Underflow("Stack is empty!");
  }

  return ptr[top];
}

template <typename T>
bool Stack<T>::isEmpty() const
{
  return top == -1;
}

template <typename T>
bool Stack<T>::isFull() const
{
  return top == capacity - 1;
}

template <typename T>
int Stack<T>::getCapacity() const
{
  return capacity;
}

template <typename T>
void Stack<T>::copyFrom(const Stack<T> &obj)
{
  if (this == &obj)
  {
    throw SelfAssignmentException("Self assignment is an invalid operation.");
  }

  // releasing memory of caller object if memory is allocated.
  if (ptr != nullptr)
    clear();

  // update the state of caller object
  ptr = new T[obj.capacity];
  capacity = obj.capacity;
  top = obj.top;

  int i = 0;
  while (i <= obj.top)
  {
    ptr[i] = obj.ptr[i];
    i++;
  }
}

template <typename T>
void Stack<T>::clear()
{
  delete[] ptr;
}

template <typename T>
std::ostream &operator<<(std::ostream &dout, const Stack<T> &obj)
{
  if (obj.isEmpty())
  {
    dout << "Stack is empty!";
    return dout;
  }

  int i = obj.top;
  std::cout<<"Top--> ";
  while (i >= 0)
  {
    dout << obj.ptr[i]<<" ";
    i--;
  }

  return dout;
}

int main(int argc, char const *argv[])
{
  Stack<int> st(5);
  st.push(100);
  st.push(200);
  st.push(70);
  st.pop();
  std::cout<<st;
  return 0;
}
