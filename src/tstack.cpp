#include"tstack.h"

#include<iostream>

TStack::TStack(int Size) : TDataRoot(Size)
{
  top = 0;
}

void TStack::Put(const TData &Val)
{
  int err;
  switch (err = TDataCom::GetRetCode())
  {
  case DataFull:
  case DataNoMem:
  case DataErr:
    throw err;
  case DataEmpty:
  case DataOK:
    TDataRoot::DataCount++;
    TDataRoot::pMem[top++] = Val;

    if (TDataRoot::DataCount == TDataRoot::MemSize)
      TDataCom::SetRetCode(DataFull);
    break;
  }
}

TData TStack::Get()
{
  int err;
  switch (err = TDataCom::GetRetCode())
  {
  case DataEmpty:
  case DataNoMem:
  case DataErr:
    throw err;
  case DataFull:
  case DataOK:
    TDataRoot::DataCount--;

    if (TDataRoot::DataCount == 0)
      TDataCom::SetRetCode(DataEmpty);

    return TDataRoot::pMem[--top];
  }
}

TData TStack::TopElem()
{
  int err;
  switch (err = TDataCom::GetRetCode())
  {
  case DataErr:
  case DataEmpty:
  case DataNoMem:
    throw err;
  case DataOK:
  case DataFull:
    return TDataRoot::pMem[top - 1];
  }
}

int TStack::IsValid()
{
  return 1;
}

void TStack::Print()
{
  switch (TDataCom::GetRetCode())
  {
  case DataErr:
    std::cout << "DATA_ERROR";
    break;
  case DataNoMem:
    std::cout << "DATA_NO_MEM";
    break;
  case DataEmpty:
    std::cout << "{ ";
    for (int i = 0; i < top; ++i)
      std::cout << TDataRoot::pMem[i] << "; ";
    std::cout << "}";
    break;
  }
}