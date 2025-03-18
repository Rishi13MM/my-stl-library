#include <iostream>
#include <stdexcept>
#include "custom_exception"

template <typename T>
class DynArray
{
private:
  int capacity;
  int lastIndex;
  T *ptr;

protected:
  bool isFull() const;
  void clear();

public:
  DynArray(int);
  DynArray();
  ~DynArray();
  DynArray(const DynArray &);
  DynArray &operator=(const DynArray &);

  void append(T);
  void insert(T, int);
  void remove(int);
  void replace(T, int);
  void doubleArray();
  void halfArray();

  bool isEmpty() const;
  int countItems() const;
  T getItem(int) const;
  int findIndex(T) const;
  int getCapacity() const;
};

template <typename T>
DynArray<T>::DynArray(int initialSize)
{
  // Set capacity to 1 if initial size is less than 1
  capacity = initialSize < 1 ? 1 : initialSize;
  lastIndex = -1;

  ptr = new T[capacity];
}

template <typename T>
DynArray<T>::DynArray()
{
  capacity = 1;
  lastIndex = -1;
  ptr = new T[capacity];
}

template <typename T>
DynArray<T>::~DynArray()
{
  clear();
}

template <typename T>
DynArray<T>::DynArray(const DynArray &obj)
{
  if (this == &obj)
  {
    throw SelfAssignment();
  }

  capacity = obj.capacity;
  lastIndex = obj.lastIndex;
  ptr = new T[capacity];

  for (int i = 0; i <= lastIndex; i++)
  {
    ptr[i] = obj.ptr[i];
  }
}

template <typename T>
DynArray<T> &DynArray<T>::operator=(const DynArray &obj)
{
  if (this != &obj)
  {
    clear();
    capacity = obj.capacity;
    lastIndex = obj.lastIndex;
    ptr = new T[capacity];
  
    for (int i = 0; i <= lastIndex; i++)
    {
      ptr[i] = obj.ptr[i];
    }
  }

  return *this;
}

template <typename T>
void DynArray<T>::clear()
{
  if (ptr != nullptr)
  {
    delete[] ptr;
    ptr = nullptr
  }
}

template <typename T>
void DynArray<T>::append(T item)
{
  if (isFull())
  {
    doubleArray();
  }

  lastIndex++;
  ptr[lastIndex] = item;
}

template <typename T>
void DynArray<T>::insert(T item, int index)
{
  if (index < 0 || index > lastIndex + 1)
  {
    throw out_of_range("Index of array is out of range.");
  }

  if (isFull())
  {
    doubleArray();
  }

  // Shift each digit to one step right side
  for (int i = lastIndex; i >= 0; i--)
  {
    ptr[i + 1] = ptr[i];
  }

  ptr[index] = item;
  lastIndex++;
}

template <typename T>
void DynArray<T>::replace(T item, int index)
{

  if (index < 0 || index > lastIndex + 1)
  {
    throw out_of_range("Index of array is out of range.");
  }

  ptr[index] = item;
}

template <typename T>
void DynArray<T>::remove(int index)
{
  if (index < 0 || index > lastIndex + 1)
  {
    throw out_of_range("Index of array is out of range.");
  }

  // Shift each digit to one left side
  for (int i = index; i < lastIndex; i++)
  {
    ptr[i] = ptr[i + 1];
  }

  lastIndex--;
}

template <typename T>
bool DynArray<T>::isEmpty() const
{
  return lastIndex == -1;
}

template <typename T>
bool DynArray<T>::isFull() const
{
  return lastIndex + 1 == capacity;
}

template <typename T>
void DynArray<T>::doubleArray()
{
  capacity *= 2;
  T *temp = new T[capacity];

  for (int i = 0; i <= lastIndex; i++)
  {
    temp[i] = ptr[i];
  }

  delete[] ptr;
  ptr = temp;
}

template <typename T>
void DynArray<T>::halfArray()
{
  if (capacity == 1)
  {
    return;
  }

  capacity /= 2;
  T *temp = new T[capacity];

  for (int i = 0; i <= lastIndex; i++)
  {
    temp[i] = ptr[i];
  }

  delete[] ptr;
  ptr = temp;
}

template <typename T>
int DynArray<T>::countItems() const
{
  return lastIndex + 1;
}

template <typename T>
T DynArray<T>::getItem(int index) const
{
  if (index < 0 || index > lastIndex + 1)
  {
    throw out_of_range("Index of array is out of range.");
  }

  return ptr[index];
}

template <typename T>
int DynArray<T>::findIndex(T item) const
{
  for (int i = 0; i <= lastIndex; i++)
  {
    if (ptr[i] == item)
    {
      return i;
    }
  }
  return -1;
}

template <typename T>
int DynArray<T>::getCapacity() const
{
  return capacity();
}