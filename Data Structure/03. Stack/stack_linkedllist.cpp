#include <iostream>
#include "custom_exception.hpp"

template <typename T>
class Stack
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {};
  };

  Node *top;
  int size;

protected:
  void clear();
  void copyFrom(const Stack &);

public:
  Stack() : top(nullptr), size(0) {}
  ~Stack();
  Stack(const Stack &);
  Stack &operator=(const Stack &);

  void push(const T &);
  T pop();
  T peek() const;
  bool isEmpty() const;
  int getLength() const;

  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const Stack<U> &);
};

template <typename T>
Stack<T>::~Stack(){
  clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &obj) : top(nullptr), size(0)
{
  copyFrom(obj);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &obj)
{
  copyFrom(obj);
  return *this;
}

template <typename T>
void Stack<T>::clear()
{
  if (!isEmpty())
  {
    // 'top' is same as 'top!=nullptr'
    while (top)
    {
      pop();
    }
  }
}

template <typename T>
void Stack<T>::copyFrom(const Stack<T> &obj)
{
  if (this != &obj)
  {
    // It releases the memoy of caller object
    if (!isEmpty())
    {
      clear();
    }

    Stack tempStack;

    // copy to temp stack
    Node *currentNode = obj.top;
    while (currentNode != nullptr)
    {
      tempStack.push(currentNode->data);
      currentNode = currentNode->next;
    }

    tempStack.size = obj.size;

    // copy to caller object
    currentNode = tempStack.top;
    while (currentNode != nullptr)
    {
      push(currentNode->data);
      currentNode = currentNode->next;
    }

    size = tempStack.size;
  }
}

template <typename T>
void Stack<T>::push(const T &value)
{
  Node *newNode = new Node(value);

  newNode->next = top;
  top = newNode;

  size++;
}

template <typename T>
T Stack<T>::pop()
{
  if (isEmpty())
  {
    throw Underflow();
  }

  Node *temp = top;
  top = top->next;
  T popped = temp->data;
  delete temp;

  size--;
  return popped;
}

template <typename T>
T Stack<T>::peek() const
{
  if (isEmpty())
  {
    throw Underflow();
  }

  return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
int Stack<T>::getLength() const
{
  return size;
}

template <typename T>
std::ostream &operator<<(std::ostream &dout, const Stack<T> &obj)
{
  if (obj.isEmpty())
  {
    dout << "Stack is empty!";
    return dout;
  }

  typename Stack<T>::Node *currentNode = obj.top;
  dout << "Top--> ";

  while (currentNode)
  {
    dout << currentNode->data << " ";
    currentNode = currentNode->next;
  }

  return dout;
}
