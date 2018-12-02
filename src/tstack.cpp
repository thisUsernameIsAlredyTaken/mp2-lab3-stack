#include"tstack.h"

#include<iostream>
#include<algorithm>

TStack::TStack(int Size) : TDataRoot(Size)
{
  top = 0;
}

void TStack::Put(const TData &Val)
{
  if (TDataRoot::DataCount < TDataRoot::MemSize)
  {
    TDataRoot::pMem[top++] = Val;
    TDataRoot::DataCount++;
  }
  else
    throw DataFull;

  if (TDataRoot::DataCount == TDataRoot::MemSize)
    TDataCom::SetRetCode(DataFull);
}

TData TStack::Get()
{
  if (TDataRoot::DataCount > 0)
  {
    TDataRoot::DataCount--;
    top--;
  }
  else
    throw DataEmpty;

  if (TDataRoot::DataCount == 0)
    TDataCom::SetRetCode(DataEmpty);

  return TDataRoot::pMem[top];
}

TData TStack::TopElem() const
{
  if (TDataRoot::DataCount <= 0)
    throw DataEmpty;
  
  return TDataRoot::pMem[top - 1];
}

int TStack::IsValid()
{
  return 1;
}

void TStack::Print()
{
  std::cout << "{ ";
  for (int i = 0; i < top; ++i)
    std::cout << TDataRoot::pMem[i] << "; ";
  std::cout << "}";
}