// Doubly Linked List
#include <iostream>
#include "custom_exception"

template <typename T>
class DLL
{
private:
  struct Node
  {
    Node *prev;
    T data;
    Node *next;

    Node(const T &data) : data(data), prev(nullptr), next(nullptr) {}
  };

  int size;
  Node *head;
  Node *tail;

protected:
  void clear();
  Node *search(const T &) const;
  void copy(const DLL &);

public:
  DLL() : size(0), head(nullptr), tail(nullptr) {}
  inline ~DLL();
  DLL(const DLL &);
  DLL &operator=(const DLL &);

  inline void insertFront(const T &);
  inline void insertBack(const T &);
  inline void insertAfter(const T &, const T &);
  inline void insertBefore(const T &, const T &);
  inline void removeFront();
  inline void removeBack();
  inline void remove(const T &, bool = true);
  inline bool isEmpty() const;
  inline int getSize() const;

  friend std::ostream &operator<<(std::ostream &dout, const DLL &obj)
  {
    DLL<T>::Node *currentNode = obj.head;
    while (currentNode)
    {
      dout << currentNode->data;
      if (currentNode != obj.tail)
      {
        dout << " <--> ";
      }

      currentNode = currentNode->next;
    }

    if (obj.isEmpty())
    {
      std::cout << "List is empty!";
    }

    return dout;
  }
};

template <typename T>
DLL<T>::~DLL()
{
  clear();
}

template <typename T>
DLL<T>::DLL(const DLL &obj) : size(0), head(nullptr), tail(nullptr)
{
  copy(obj);
}

template <typename T>
DLL<T> &DLL<T>::operator=(const DLL &obj)
{
  copy(obj);

  return *this;
}

template <typename T>
void DLL<T>::insertFront(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    head = tail = newNode;
  }
  else
  {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }

  size++;
}

template <typename T>
void DLL<T>::insertBack(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    head = tail = newNode;
  }
  else
  {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }

  size++;
}

template <typename T>
void DLL<T>::insertAfter(const T &prevValue, const T &value)
{
  Node *prevNode = search(prevValue);

  if (prevNode == nullptr)
  {
    throw NodeNotFound("Node not found of given data!");
  }

  Node *newNode = new Node(value);
  newNode->prev = prevNode;
  newNode->next = prevNode->next;
  prevNode->next = newNode;

  if (newNode->next == nullptr)
  {
    tail = newNode;
  }
  else
  {
    newNode->next->prev = newNode;
  }

  size++;
}

template <typename T>
void DLL<T>::insertBefore(const T &afterValue, const T &value)
{
  Node *afterNode = search(afterValue);
  if (afterNode == nullptr)
  {
    throw NodeNotFound("Node not found of given data!");
  }

  Node *newNode = new Node(value);
  newNode->next = afterNode;
  newNode->prev = afterNode->prev;

  if (afterNode->prev == nullptr)
  {
    head = newNode;
  }
  else
  {
    afterNode->prev->next = newNode;
  }

  afterNode->prev = newNode;

  size++;
}

template <typename T>
void DLL<T>::removeFront()
{
  if (isEmpty())
  {
    throw Underflow("DLL is empty!");
  }

  if (head == tail)
  {
    delete head;
    head = tail = nullptr;
  }
  else
  {
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
  }
  size--;
}

template <typename T>
void DLL<T>::removeBack()
{
  if (isEmpty())
  {
    throw Underflow("DLL is empty!");
  }

  if (head == tail)
  {
    delete head;
    head = tail = nullptr;
  }
  else
  {
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
  }

  size--;
}

template <typename T>
void DLL<T>::remove(const T &value, bool isALL)
{
  Node *currentNode = head, *temp = nullptr;
  while (currentNode)
  {
    Node *nextNode = currentNode->next;
    if (currentNode->data == value)
    {
      if (currentNode == head)
      {
        removeFront();
      }
      else if (currentNode == tail)
      {
        removeBack();
      }
      else
      {
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;
        delete currentNode;
        size--;
      }

      if (!isALL)
      {
        break;
      }
    }

    currentNode = nextNode;
  }
}

template <typename T>
bool DLL<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
int DLL<T>::getSize() const
{
  return size;
}

template <typename T>
typename DLL<T>::Node *DLL<T>::search(const T &value) const
{
  Node *targetNode = head;
  while (targetNode)
  {
    if (targetNode->data == value)
    {
      return targetNode;
    }

    targetNode = targetNode->next;
  }

  return nullptr;
}

template <typename T>
void DLL<T>::clear()
{
  while (head)
  {
    removeFront();
  }

  size = 0;
}

template <typename T>
void DLL<T>::copy(const DLL &obj)
{
  if (this != &obj)
  {
    clear();
    Node *currentNode = obj.head;
    while (currentNode)
    {
      insertBack(currentNode->data);
      currentNode = currentNode->next;
    }
  }
}
