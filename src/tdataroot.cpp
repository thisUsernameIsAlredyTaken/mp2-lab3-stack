// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdataroot.cpp - Copyright (c) Гергель В.П. 28.07.2000 (06.08)
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - базовый (абстрактный) класс - версия 3.1
//   память выделяется динамически или задается методом SetMem

#include <stdio.h>
#include "tdataroot.h"

TDataRoot::TDataRoot(int Size): TDataCom()
{
  DataCount = 0;
  MemSize = Size;
  if (Size <= 0) // память будет установлена методом SetMem
  {
    pMem = NULL;
    MemType = MEM_RENTER;
    TDataCom::SetRetCode(DataNoMem);
  }
  else // память выделяется объектом
  {
    pMem = new TElem[MemSize];
    MemType = MEM_HOLDER;
    TDataCom::SetRetCode(DataEmpty);
  }
} /*-------------------------------------------------------------------------*/

TDataRoot::~TDataRoot()
{
  if (MemType == MEM_HOLDER)
    delete [] pMem;
} /*-------------------------------------------------------------------------*/

void TDataRoot::SetMem(void *p, int Size) // задание памяти
{
  if (MemType == MEM_HOLDER)
    delete [] pMem; // ! информация не сохраняется
  pMem = (TElem*) p;
  MemType = MEM_RENTER;
  MemSize = Size;
  DataCount = 0;
  TDataCom::SetRetCode(DataEmpty);
} /*-------------------------------------------------------------------------*/

bool TDataRoot::IsEmpty(void) const // контроль пустоты СД
{
  return DataCount == 0;
} /*-------------------------------------------------------------------------*/

bool TDataRoot::IsFull(void) const // контроль переполнения СД
{
  return DataCount == MemSize;
} /*-------------------------------------------------------------------------*/
