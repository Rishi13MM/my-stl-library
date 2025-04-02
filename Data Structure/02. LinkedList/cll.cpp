#include <iostream>
#include "custom_exception"

template <typename T>
class CLL
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(T value) : data(value), next(nullptr) {}
  };

  Node *tail;
  int size;

protected:
  void clear();
  void copy(const CLL &);

public:
  CLL() : tail(nullptr), size(0) {}
  ~CLL();
  CLL(const CLL &);
  CLL &operator=(const CLL &);
  template <typename U>
  friend std::ostream &operator<<(std::ostream &, const CLL<U> &);


  inline void insertFront(const T &);
  inline void insertBack(const T &);
  // Using 0 based indexing
  void insert(const T &, const int &);
  inline void removeFront();
  void removeBack();
  // Removes the first occurrence of the specified data if 'false' is passed; removes all occurrences if 'true' is passed.
  void remove(const T &, const bool = true);
  inline int getSize() const;
  inline bool isEmpty() const;
};

template <typename T>
CLL<T>::~CLL()
{
  clear();
}

template <typename T>
CLL<T>::CLL(const CLL &obj) : tail(nullptr), size(0)
{
  copy(obj);
}

template <typename T>
CLL<T> &CLL<T>::operator=(const CLL &obj)
{
  copy(obj);
  return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &dout, const CLL<T> &obj)
{
  if (obj.isEmpty())
  {
    dout << "List is empty";
  }
  else
  {
    typename CLL<T>::Node *currentNode = obj.tail->next;

    do
    {
      dout << currentNode->data;
      if (currentNode != obj.tail)
      {
        dout << " --> ";
      }
      currentNode = currentNode->next;
    } while (currentNode != obj.tail->next);
  }
  return dout;
}

template <typename T>
void CLL<T>::copy(const CLL &obj)
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
void CLL<T>::clear()
{
  while (tail)
  {
    removeFront();
  }
}

template <typename T>
void CLL<T>::insertFront(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    newNode->next = newNode;
    tail = newNode;
    size++;
    return;
  }

  newNode->next = tail->next;
  tail->next = newNode;
  size++;
}

template <typename T>
void CLL<T>::insertBack(const T &value)
{
  Node *newNode = new Node(value);

  if (isEmpty())
  {
    newNode->next = newNode;
    tail = newNode;
    size++;
    return;
  }

  newNode->next = tail->next;
  tail->next = newNode;
  tail = newNode;
  size++;
}

template <typename T>
void CLL<T>::insert(const T &value, const int &pos)
{

  if (pos < 0 || pos > size)
  {
    throw std::out_of_range("Insertion position is out of range.");
  }

  if (pos == 0)
  {
    insertFront(value);
    return;
  }

  if (pos == size)
  {
    insertBack(value);
    return;
  }

  Node *newNode = new Node(value), *currentNode = tail;
  for (int i = 0; i < pos; i++)
  {
    currentNode = currentNode->next;
  }

  newNode->next = currentNode->next;
  currentNode->next = newNode;
  size++;
}

template <typename T>
void CLL<T>::removeFront()
{
  if (isEmpty())
  {
    throw Underflow("List is empty!");
  }

  if (tail == tail->next)
  {
    delete tail;
    tail = nullptr;
    size--;
    return;
  }

  Node *temp = tail->next;
  tail->next = tail->next->next;
  delete temp;
  size--;
}

template <typename T>
void CLL<T>::removeBack()
{
  if (isEmpty())
  {
    throw Underflow("List is empty!");
  }

  if (tail == tail->next)
  {
    delete tail;
    tail = nullptr;
    size--;
    return;
  }

  // finding the second last node to bypass the last node
  Node *currentNode = tail->next;
  while (currentNode->next != tail)
  {
    currentNode = currentNode->next;
  }

  currentNode->next = currentNode->next->next;
  delete tail;
  tail = currentNode;
  size--;
}

template <typename T>
void CLL<T>::remove(const T &value, const bool isRemoveAll)
{
  Node *currentNode = nullptr;

  if (!isEmpty())
  {
    currentNode = tail;
    do
    {
      if (currentNode->next->data == value)
      {
        size--;

        // if only one element is present
        if (tail->next == tail)
        {
          delete tail;
          tail = nullptr;
          return;
        }

        // if more than one element
        Node *temp = currentNode->next;
        currentNode->next = currentNode->next->next;

        delete temp;
        if (temp == tail)
        {
          tail = currentNode;
          return;
        }

        if (isRemoveAll==false)
        {
          
          break;
        }

        // To check if one element remain after removal
        if (tail == tail->next)
        {
          if (tail->data == value)
          {
            removeFront();
          }
          return;
        }

        continue;
      }

      currentNode = currentNode->next;

      if(currentNode==tail){
        break;
      }

    } while (1);
  }
}

template <typename T>
int CLL<T>::getSize() const
{
  return size;
}

template <typename T>
bool CLL<T>::isEmpty() const
{
  return size == 0;
}
