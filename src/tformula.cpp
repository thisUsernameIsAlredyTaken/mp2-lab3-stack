#include"tformula.h"
#include"tstack.h"
#include"templateStack.h"
#include<cstring>
#include<locale>
#include<vector>

int op_prior(char);
bool piece_of_number(char);
bool must_operator_push(const TStack &, int);

TFormula::TFormula(char *form)
{
  if (strlen(form) >= MaxLen)
    throw "buffer_overflow";
  strcpy(Formula, form);
  for(int i = 0; i < MaxLen; ++i)
    PostfixForm[i] = 0;
}

int TFormula::FormulaChecker(int Brackets[], int Size)
{
  int err = 0, index = 0, number = 1;
  char *pCh = Formula;
  TStack st(Size);

  for (int i = 0; i < Size; ++i)
    Brackets[i] = -1;

  do
  {
    switch (*pCh)
    {
    case '(':
      st.Put(number++);
      break;
    case ')':
      if (st.IsEmpty())
      {
        Brackets[index++] = 0;
        Brackets[index++] = number++;
        ++err;
      }
      else
      {
        Brackets[index++] = st.Get();
        Brackets[index++] = number++;
      }
      break;
    }
  } while (*++pCh);

  while (!st.IsEmpty())
  {
    Brackets[index++] = st.Get();
    Brackets[index++] = 0;
    ++err;
  }

  return err;
}

int TFormula::FormulaConverter()
{
  char *pCh = Formula;
  int index = 0;
  TStack st(MaxLen);

  int brackets[MaxLen * 2];
  if (FormulaChecker(brackets, MaxLen * 2) != 0)
    return 0;

  do
  {
    int prior = op_prior(*pCh);

    if (prior == -2)
      continue;       //если встречаем пробел в исходной строке - едем дальше

    if (prior == 2 || prior == 3)
      PostfixForm[index++] = ' ';    //разделяем операнды пробелом в выходной строке

    if (*pCh == ')')          //обработка закрывающей скобки
    {
      while (st.TopElem() != '(')
        PostfixForm[index++] = st.Get();  //выписываем все операторы из стека до открывающей скобки
      st.Get();        //выталкиваем саму скобку
    }
    else if (prior == -1)
      PostfixForm[index++] = *pCh;    //записываем операнд в выходную строку
    else if (must_operator_push(st, prior))
      st.Put(*pCh);                   //пушим оператор в стек
    else
    {
      while (op_prior(st.TopElem()) >= prior)
        PostfixForm[index++] = st.Get();     //достаем из стека операторы, пока приоритет больше либо равен текущему
      st.Put(*pCh);
    }

  } while (*++pCh);

  while (!st.IsEmpty())
    PostfixForm[index++] = st.Get();

  return 1;
}

double TFormula::FormulaCalculator()
{
  char *pCh = PostfixForm;
  Stack<double> operands(MaxLen);

  do
  {
    if (op_prior(*pCh) == -2)
      continue;

    if (piece_of_number(*pCh))
    {
      std::vector<char> tmpV;
      do
      {
        tmpV.push_back(*pCh);
      } while (piece_of_number(*++pCh));
      --pCh;

      size_t s = tmpV.size();
      char *tmpC = new char[s + 1];

      tmpC[s] = 0;
      for (int i = 0; i < s; ++i)
        tmpC[i] = tmpV[i];

      double d = atof(tmpC);
      operands.Push(d);

      delete[] tmpC;
    }
    else
    {
      double op2 = operands.Pop();
      double op1 = operands.Pop();

      double result;

      switch (*pCh)
      {
      case '+':
        result = op1 + op2;
        break;
      case '-':
        result = op1 - op2;
        break;
      case '/':
        result = op1 / op2;
        break;
      case '*':
        result = op1 * op2;
        break;
      }

      operands.Push(result);
    }

  } while (*++pCh);

  return operands.Pop();
}



int op_prior(char ch)
{
  switch (ch)
  {
  case '(':
    return 0;
  case ')':
    return 1;
  case '+':
  case '-':
    return 2;
  case '*':
  case '/':
    return 3;
  case ' ':
  case '\t':
    return -2;
  default:
    return -1;
  }
}

bool piece_of_number(char ch)
{
  return isdigit(ch) || ch == '.';
}

bool must_operator_push(const TStack &st, int prior)
{
  if (st.IsEmpty() || prior == 0)
    return true;
  if (!st.IsEmpty())
    if (op_prior(st.TopElem()) < prior)
      return true;
  return false;
}
