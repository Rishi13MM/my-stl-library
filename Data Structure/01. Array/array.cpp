#include <iostream>
#include <stdexcept>
#include "custom_exception"

using namespace std;

template <typename T>
class Array
{
  private:
    int capacity;
    int lastIndex;
    T *ptr;
  protected:
    void clear();
  public:
    Array(int);
    ~Array();
    Array(const Array&);
    Array& operator=(const Array&);

    void append(T);
    void insert(T, int);
    void remove(int);
    void replace(T, int);
    
    T getItem(int) const;
    int findIndex(T) const;
    bool isFull() const;
    bool isEmpty() const;
    int countItems() const;
    void display() const;
};


template <typename T>
Array<T>::Array(int size)
{
  if (size < 1)
  {
    throw InvalidCapacity("Size of array must be 1 or more.");
  }

  ptr = new T[size];

  capacity = size;
  lastIndex = -1;
}

template <typename T>
Array<T>::~Array()
{
  clear();
}

template <typename T>
Array<T>::Array(const Array &obj)
{
  if (this == &obj)
  {
    throw SelfAssignment("Cannot assign an object to itself.");
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
Array<T>& Array<T>::operator=(const Array &obj)
{
  if(this!=&obj){
    // freeing memory of array
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
void Array<T>::clear()
{
  if (ptr != nullptr)
  {
    delete[] ptr;
    ptr = nullptr;
  }
}

template <typename T>
bool Array<T>::isEmpty() const
{
  return lastIndex == -1;
}

template <typename T>
bool Array<T>::isFull() const
{
  return capacity == lastIndex + 1;
}

template <typename T>
void Array<T>::append(T item)
{
  if (isFull())
  {
    throw ArrayOverflow("Cannot append an item because array is full!.");
  }

  lastIndex++;
  ptr[lastIndex] = item;
}

template <typename T>
void Array<T>::insert(T item, int index)
{

  if (isFull())
  {
    throw ArrayOverflow("Cannot append an item because array is full!.");
  }

  if (index < 0 || index > lastIndex + 1)
  {
    throw out_of_range("Index is out of range.");
  }

  for (int i = lastIndex; i >= index; i--)
  {
    ptr[i + 1] = ptr[i];
  }

  ptr[index] = item;
  lastIndex++;
}

template <typename T>
void Array<T>::remove(int index)
{
  if (isEmpty())
  {
    throw ArrayUnderflow("Cannot remove an item because array is empty.");
  }

  if (index < 0 || index > lastIndex)
  {
    throw out_of_range("Index is out of range.");
  }

  for (int i = index; i < lastIndex; i++)
  {
    ptr[i] = ptr[i + 1];
  }

  lastIndex--;
}

template <typename T>
int Array<T>::countItems() const
{
  return lastIndex + 1;
}

template <typename T>
int Array<T>::findIndex(T item) const
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
T Array<T>::getItem(int index) const
{
  if (index < 0 || index > lastIndex)
  {
    throw out_of_range("Index is out of range.");
  }

  return ptr[index];
}

template <typename T>
void Array<T>::replace(T item, int index)
{
  if (index < 0 || index > lastIndex)
  {
    throw out_of_range("Index is out of range.");
  }

  ptr[index] = item;
}

template <typename T>
void Array<T>::display() const{
  cout<<"[";
  for (int i = 0; i <= lastIndex; i++)
  {
    if(i==lastIndex){
      cout<<ptr[i]<<"]";
    }else{
      cout<<ptr[i]<<", ";
    }
  }
}

int main(){
  Array<int> arr(5);
  arr.append(10);
  arr.append(10);
  arr.append(10);
  arr.append(10);
  arr.append(10);
  arr.remove(0);
  cout<<arr.isFull();
  arr.display();
  return 0;
}