#include <iostream>
#include "custom_exception"

template <typename T>
class CDLL
{
private:
  struct Node
  {
    Node *prev;
    T data;
    Node *next;

    // Constructor
    Node(const T &value) : data(value), prev(nullptr), next(nullptr) {};
  };

  Node *tail;
  std::size_t size;

protected:
  // Releases the memory of the list
  void clear();

  // copies the data from the specified list
  void copy(const CDLL &);

  // Check if node is exists in the list or not
  bool isNodeExist(const Node *) const;

public:
  CDLL() : tail(nullptr), size(0) {};
  ~CDLL();
  CDLL(const CDLL &);
  CDLL &operator=(const CDLL &);
  
  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const CDLL<U> &);

  void insertFront(const T &);
  void insertBack(const T &);
  void insertAfter(const T &, Node *);
  void insertBefore(const T &, Node *);
  void insert(const T &, const int);

  void removeFront();
  void removeBack();

  // Deletes node from list if exists; otherwise it will throw an NodeNotFound exception.
  void removeNode(const Node *);

  // Removes the first occurrence of specified data from the list if second argument is false; otherwise delete all the data from list.
  void remove(const T &, const bool = true);

  // Returns the first occurrence that match with specified data; otherwise nullptr.
  Node *search(const T &) const;
  std::size_t getSize() const;
  bool isEmpty() const;

  // It is used to print list using standard output stream (cout).
  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const CDLL<T> &);
};

template <typename T>
void CDLL<T>::insertFront(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    newNode->prev = newNode;
    newNode->next = newNode;
    tail = newNode;
  }
  else
  {
    newNode->prev = tail;
    newNode->next = tail->next;
    tail->next->prev = newNode;
    tail->next = newNode;
  }

  size++;
}

template <typename T>
void CDLL<T>::insertBack(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    newNode->prev = newNode;
    newNode->next = newNode;
    tail = newNode;
  }
  else
  {
    newNode->prev = tail;
    newNode->next = tail->next;
    tail->next->prev = newNode;
    tail->next = newNode;

    tail = newNode;
  }

  size++;
}

template <typename T>
void CDLL<T>::insertAfter(const T &value, Node *node)
{
  if (node == nullptr)
  {
    throw InvalidNodePointer("Node is a nullptr.");
  }

  if (!isNodeExist(node))
  {
    throw NodeNotFound("Node not exist in the list.");
  }

  if (node == tail)
  {
    insertBack(value);
    return;
  }

  Node *newNode = new Node(value);
  newNode->prev = node;
  newNode->next = node->next;
  node->next->prev = newNode;
  node->next = newNode;

  size++;
}

template <typename T>
void CDLL<T>::insertBefore(const T &value, Node *node)
{
  if (node == nullptr)
  {
    throw InvalidNodePointer("Node is a nullptr.");
  }

  if (!isNodeExist(node))
  {
    throw NodeNotFound("Node not exist in the list.");
  }

  if (tail->next == node)
  {
    insertFront(value);
    return;
  }

  Node *newNode = new Node(value);
  newNode->prev = node->prev;
  newNode->next = node;
  node->prev->next = newNode;
  node->prev = newNode;

  size++;
}

template <typename T>
void CDLL<T>::insert(const T &value, const int index)
{
  if (index < 0 || index > size)
  {
    throw std::out_of_range("Index is out of range (not valid).");
  }

  if (index == 0)
  {
    insertFront(value);
    return;
  }

  Node *currentNode = tail;

  for (size_t i = 0; i < index; i++)
  {
    currentNode = currentNode->next;
  }

  insertAfter(value, currentNode);
}

template <typename T>
void CDLL<T>::removeFront()
{
  if (isEmpty())
  {
    throw Underflow("List is empty!");
  }

  if (size == 1)
  {
    delete tail;
    tail = nullptr;
  }
  else
  {
    tail->next = tail->next->next;
    delete tail->next->prev;
    tail->next->prev = tail;
  }

  size--;
}

template <typename T>
void CDLL<T>::removeBack()
{
  if (isEmpty())
  {
    throw Underflow("List is empty!");
  }

  if (size == 1)
  {
    delete tail;
    tail = nullptr;
  }
  else
  {
    tail->prev->next = tail->next;
    tail = tail->prev;
    delete tail->next->prev;
    tail->next->prev = tail;
  }

  size--;
}

template <typename T>
void CDLL<T>::removeNode(const Node *node)
{
  if (!isNodeExist(node))
  {
    throw NodeNotFound("Node not exist in the list.");
  }

  if (tail->next == node)
  {
    removeFront();
    return;
  }

  if (tail == node)
  {
    removeBack();
    return;
  }

  node->prev->next = node->next;
  node->next->prev = node->prev;
  delete node;

  size--;
}

template <typename T>
void CDLL<T>::remove(const T &value, const bool isRemoveAll)
{
  if (!isEmpty())
  {
    int count = 0;
    Node *currentNode = tail->next;

    do
    {
      count++;
      if (currentNode->data == value)
      {
        Node *deleteNode = currentNode;
        currentNode = currentNode->next;
        removeNode(deleteNode);

        if (isRemoveAll == false)
        {
          return;
        }

        continue;
      }

      currentNode = currentNode->next;
    } while (count < size);
  }
}

template <typename T>
typename CDLL<T>::Node *CDLL<T>::search(const T &value) const
{
  if (!isEmpty())
  {
    Node *currentNode = tail;
    do
    {
      if (currentNode->data == value)
      {
        return currentNode;
      }

      currentNode = currentNode->next;
    } while (currentNode != tail);
  }

  return nullptr;
}

template <typename T>
std::size_t CDLL<T>::getSize() const
{
  return size;
}

template <typename T>
bool CDLL<T>::isEmpty() const
{
  return size == 0;
}

template <typename T>
bool CDLL<T>::isNodeExist(const Node *node) const
{
  if (!isEmpty())
  {
    Node *currentNode = tail;
    do
    {
      if (currentNode == node)
      {
        return true;
      }
      currentNode = currentNode->next;
    } while (currentNode != tail);
  }

  return false;
}

template <typename T>
void CDLL<T>::clear()
{
  while (tail)
  {
    removeFront();
  }
}

template <typename T>
void CDLL<T>::copy(const CDLL &obj)
{
  if (this != &obj)
  {
    clear();
    if (!obj.isEmpty())
    {
      Node *currentNode = obj.tail->next;
      do
      {
        insertBack(currentNode->data);
        currentNode = currentNode->next;
      } while (currentNode != obj.tail->next);
    }
  }
}

template <typename T>
CDLL<T>::~CDLL()
{
  clear();
}

template <typename T>
CDLL<T>::CDLL(const CDLL &obj) : size(0), tail(nullptr)
{
  copy(obj);
}

template <typename T>
CDLL<T> &CDLL<T>::operator=(const CDLL &obj)
{
  copy(obj);
  return *this;
}

// Definition of friend function
template <typename T>
std::ostream &operator<<(std::ostream &dout, const CDLL<T> &obj)
{
  if (obj.isEmpty())
  {
    dout << "List is empty!";
  }
  else
  {

    typename CDLL<T>::Node *currentNode = obj.tail->next;

    do
    {
      dout << currentNode->data;
      if (currentNode != obj.tail)
      {
        dout << " <--> ";
      }

      currentNode = currentNode->next;
    } while (currentNode != obj.tail->next);
  }

  return dout;
}
