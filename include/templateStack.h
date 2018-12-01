#ifndef __TEMPLATESTACK_H__
#define __TEMPLATESTACK_H__

template<class T>
class Stack
{
private:
  T *pMem;
  int top;
  int size;
public:
  Stack(int size = 1)
  {
    if (size <= 0)
      throw -1;
    top = 0;
    this->size = size;
    pMem = new T[size];
  }
  ~Stack()
  {
    delete[] pMem;
  }
  void Push(const T &val)
  {
    if (top >= size)
      throw "stack_is_full";
    pMem[top++] = val;
  }
  T Pop()
  {
    if (top <= 0)
      throw "stack_is_empty";
    return pMem[--top];
  }
  bool IsEmpty()
  {
    return top == 0;
  }
  bool IsFull()
  {
    return top == size;
  }
};


#endif // !__TEMPLATESTACK_H__
