#include"tformula.h"
#include"tstack.h"
#include"templateStack.h"
#include<cstring>
#include<locale>
#include<vector>

int op_prior(char);

TFormula::TFormula(char *form)
{
  if (strlen(form) >= MaxLen)
    throw "buffer_overflow";
  strcpy(Formula, form);
  PostfixForm[0] = 0;
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

  do
  {
    int prior = op_prior(*pCh);
    if (*pCh == '+' || *pCh == '-' || *pCh == '/' || *pCh == '*')
      PostfixForm[index++] = ' ';
    if (prior == -1)
      PostfixForm[index++] = *pCh;
    else if(prior == 0 || prior > st.TopElem() || st.IsEmpty())
      st.Put(*pCh);
    else if (*pCh == ')')
    {
      while (st.TopElem() != '(')
        PostfixForm[index++] = st.Get();
      st.Get();
    }
    else
    {
      while (op_prior(st.TopElem()) >= prior)
      {
        PostfixForm[index++] = st.Get();
      }
    }

  } while (*++pCh);

  while (!st.IsEmpty())
    PostfixForm[index++] = st.Get();
}

double TFormula::FormulaCalculator()
{
  char *pCh = PostfixForm;
  Stack<double> operands(MaxLen);

  do
  {
    if (isdigit(*pCh))
    {
      std::vector<char> tmpV;
      do
      {
        if (!isdigit(*pCh) && *pCh != '.')
          throw -2;

        tmpV.push_back(*pCh);
      } while (*++pCh != ' ');

      size_t s = tmpV.size();
      char *tmpC = new char[s + 1];

      tmpC[s] = 0;
      for (int i = 0; i < s; ++i)
        tmpC[i] = tmpV[i];

      double d = atof(tmpC);

      delete[] tmpC;
    }
    else if (*pCh == '+')
    {
      double op2 = operands.Pop();
      double op1 = operands.Pop();

      operands.Push(op1 + op2);
    }
    else if (*pCh == '-')
    {
      double op2 = operands.Pop();
      double op1 = operands.Pop();

      operands.Push(op1 - op2);
    }
    else if (*pCh == '*')
    {
      double op2 = operands.Pop();
      double op1 = operands.Pop();

      operands.Push(op1 * op2);
    }
    else if (*pCh == '/')
    {
      double op2 = operands.Pop();
      double op1 = operands.Pop();

      operands.Push(op1 / op2);
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
    return -2;
  default:
    return -1;
  }
}