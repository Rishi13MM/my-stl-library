// Singly Linked List

#include <iostream>
#include "custom_exception"

#define OUT_OF_RANGE "Invalid position!"

template <typename T>
class SLL
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(T value)
    {
      data = value;
      next = nullptr;
    }
  };

  Node *head;
  Node *tail;

protected:
  void clear();
  bool isNodePresent(const Node *) const;

public:
  SLL();
  SLL(const SLL &);
  SLL &operator=(const SLL &);
  ~SLL();

  void pushFront(T);
  void pushBack(T);
  void insertAt(T, int);
  void insertAfter(T, Node *);
  void popFront();
  void popBack();
  void removeAt(int);
  bool isEmpty() const;
  Node *findByValue(T) const;
  Node *findByIndex(int) const;
  void printList() const;
};

template <typename T>
SLL<T>::SLL()
{
  head = nullptr;
  tail = nullptr;
}

template <typename T>
SLL<T>::~SLL()
{
  clear();
  head = nullptr;
  tail = nullptr;
}

template <typename T>
SLL<T>::SLL(const SLL &obj)
{
  head = tail = nullptr;

  if (*this != &obj)
  {
    Node *currentNode = obj.head;
    while (currentNode)
    {
      pushBack(currentNode->data);
      currentNode = currentNode->next;
    }
  }
}

template <typename T>
SLL<T> &SLL<T>::operator=(const SLL &obj)
{
  if (this != &obj)
  {
    clear();

    Node *currentNode = obj.head;
    while (currentNode)
    {
      pushBack(currentNode->data);
      currentNode = currentNode->next;
    }
  }

  return *this;
}

template <typename T>
void SLL<T>::pushFront(T value)
{
  Node *newNode = new Node(value);
  newNode->next = head;

  if (head == nullptr)
  {
    tail = newNode;
  }

  head = newNode;
}

template <typename T>
void SLL<T>::pushBack(T value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    head = tail = newNode;
  }
  else
  {
    tail->next = newNode;
    tail = newNode;
  }
}

template <typename T>
void SLL<T>::insertAt(T value, int pos)
{
  if (pos < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE);
  }

  // insert node at start if position is 0
  if (pos == 0)
  {
    pushFront(value);
    return;
  }

  Node *currentNode = head;
  int i = 1;

  // trying to get the previous node to the relative of given position
  while (i < pos && currentNode != nullptr)
  {
    currentNode = currentNode->next;
    i++;
  }

  // throw exception if position is out of range
  if (currentNode == nullptr)
  {
    throw std::out_of_range(OUT_OF_RANGE);
  }

  // insert as a last node
  if (currentNode->next == nullptr)
  {
    pushBack(value);
  }
  else
  {
    // insert node at middle of the list
    Node *newNode = new Node(value);
    newNode->next = currentNode->next;
    currentNode->next = newNode;
  }
}

template <typename T>
void SLL<T>::insertAfter(T value, Node *node)
{
  if (isNodePresent(node) == false)
  {
    throw InvalidNodePointer();
  }

  Node *newNode = new Node(value);
  newNode->next = node->next;
  node->next = newNode;
}

template <typename T>
void SLL<T>::popFront()
{
  if (isEmpty())
  {
    throw Underflow();
  }

  Node *temp = head;
  head = head->next;

  if (head == nullptr)
  {
    tail = nullptr;
  }

  delete temp;
}

template <typename T>
void SLL<T>::popBack()
{
  if (isEmpty())
  {
    throw Underflow();
  }

  if (head == tail)
  {
    delete tail;
    head = tail = nullptr;
    return;
  }

  Node *prevNode = head;
  while (prevNode->next != tail)
  {
    prevNode = prevNode->next;
  }

  prevNode->next = nullptr;
  delete tail;
  tail = prevNode;
}

template <typename T>
void SLL<T>::removeAt(int pos)
{
  if (pos < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE);
  }

  if (isEmpty())
  {
    throw Underflow();
  }

  if (pos == 0)
  {
    popFront();
    return;
  }

  Node *prevNode = head;
  for (int i = 1; i < pos && prevNode->next != nullptr; i++)
  {
    prevNode = prevNode->next;
  }

  if (prevNode->next == nullptr)
  {
    throw std::out_of_range(OUT_OF_RANGE);
  }

  Node *temp = prevNode->next;
  prevNode->next = prevNode->next->next;
  delete temp;
}

template <typename T>
bool SLL<T>::isEmpty() const
{
  return head == nullptr;
}

template <typename T>
SLL<T>::Node *SLL<T>::findByValue(T value) const
{
  Node *currentNode = head;
  while (currentNode)
  {
    if (currentNode->data == value)
    {
      return currentNode;
    }
    currentNode = currentNode->next;
  }

  return nullptr;
}

template <typename T>
SLL<T>::Node *SLL<T>::findByIndex(int pos) const
{
  Node *currentNode = head;
  for (int i = 0; i < pos && currentNode != nullptr; i++)
  {
    currentNode = currentNode->next;
  }

  if (currentNode != nullptr && pos >= 0)
  {
    return currentNode;
  }

  return nullptr;
}

template <typename T>
void SLL<T>::printList() const
{
  Node *currentNode = head;

  while (currentNode != nullptr)
  {
    std::cout << currentNode->data << " ";
    currentNode = currentNode->next;
  }

  if (head == nullptr)
  {
    std::cout << "Linked list is empty!\n";
  }
}

template <typename T>
bool SLL<T>::isNodePresent(const Node *node) const
{
  Node *currentNode = head;

  while (currentNode)
  {
    if (currentNode==node)
    {
      return true;
    }
    currentNode = currentNode->next;
  }

  return false;
}

template <typename T>
void SLL<T>::clear()
{
  while (head)
  {
    popFront();
  }
}

int main()
{
  SLL<int> list;
  list.pushBack(10);
  list.pushFront(20);
  list.popFront();
  list.popBack();
  // list.removeAt(9);
  list.printList();
  return 0;
}