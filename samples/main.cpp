// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - тестирование стека

#ifdef STACK

#include <iostream>
#include "tstack.h"

using namespace std;

int main()
{
  TStack st(2);
  int temp;

  //setlocale(LC_ALL, "RU-ru");
  //cout << "Тестирование программ поддержки структуры типа стека" << endl;
  cout << "Stack data structure programm testing" << endl;
  for (int i = 0; i < 35; i++)
  {
    int retcode;
    try {
      st.Put(i);
      retcode = st.GetRetCode();
    }
    catch (int err)
    {
      retcode = err;
    }
    //cout << "Положили значение " << i << " Код " << retcode << endl;
    cout << "Puted value " << i << " Code " << retcode << endl;
  }
  while (!st.IsEmpty())
  {
    temp = st.Get();
    //cout << "Взяли значение " << temp << " Код " << st.GetRetCode() << endl;
    cout << "Taken value is " << temp << " Code " << st.GetRetCode() << endl;
  }
  return 0;
}


#endif // STACK


#ifndef STACK

#include<iostream>
#include"tformula.h"

using namespace std;

int main()
{
  char str[] = "956.83 + 568.274 - 978.4054 * 7.584 * 7.5945 / 0.4394 / 23.323";
  TFormula tf(str);

  //try {
    tf.FormulaConverter();

    cout << tf.getpostfix() << endl << endl;
    cout << tf.FormulaCalculator() << endl;
  //}
  //catch (char *e)
  //{
  //  cerr << "\tERR:: " << e << endl << endl;
  //}
  //catch (int e)
  //{
  //  cerr << "\tERR:: " << e << endl << endl;
  //}

  return 0;
}

#endif // !STACK
