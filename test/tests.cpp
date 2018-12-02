#include<gtest.h>

#include"tstack.h"
#include"tformula.h"
#include<algorithm>

TEST(TStack, can_create)
{
  EXPECT_NO_THROW(TStack st(5));
}

TEST(TStack, cant_get_element_from_empty_stack)
{
  TStack st(5);

  EXPECT_ANY_THROW(st.Get());
}

TEST(TStack, cant_set_element_in_full_stack)
{
  const int SZ = 5;
  TStack st(SZ);

  for (int i = 0; i < SZ; ++i)
    st.Put(1);

  EXPECT_ANY_THROW(st.Put(1));
}

TEST(TStack, put_get_check)
{
  const int EL = 1;
  TStack st(5);

  st.Put(EL);

  EXPECT_EQ(EL, st.Get());
}

TEST(TStack, get_and_topelement_returns_the_same_value)
{
  TStack st(5);

  st.Put(1);
  int te = st.TopElem();

  EXPECT_EQ(te, st.Get());
}

TEST(TStack, throws_if_put_in_stack_with_no_memory)
{
  TStack st(0);

  EXPECT_ANY_THROW(st.Put(1));
}

TEST(TFormula, brackets_checker_check)
{
  char formula1[] = "(8 + 5) / (9 - 3)",
    formula2[] = "(8 + 5() / (9 - 3)";
  const int SZ = MaxLen;
  int brackets[SZ];
  TFormula tf1(formula1), tf2(formula2);

  EXPECT_EQ(0, tf1.FormulaChecker(brackets, SZ));
  EXPECT_EQ(1, tf2.FormulaChecker(brackets, SZ));
}

TEST(TFormula, postfix_form_check)
{
  char formula[] = "(2+4)/(7+1-5)";
  const char postfixEXP[] = "2 4+ 7 1 +5-/";
  TFormula tf(formula);

  tf.FormulaConverter();

  EXPECT_STREQ(postfixEXP, tf.getpostfix());
}

TEST(TFormula, calculator_check_1)
{
  char formula[] = "(2+4)/(7+.999-5.001)";
  TFormula tf(formula);
  const double resultEXP = (2 + 4) / (7 + 0.999 - 5.001);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_2)
{
  char formula[] = "((234.66 - 43.556) / ((19.435 - 776.141 * 98.01) * (189 / 0.594 - 118.43)))";
  TFormula tf(formula);
  const double resultEXP = ((234.66 - 43.556) / ((19.435 - 776.141 * 98.01) * (189 / 0.594 - 118.43)));

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_3)
{
  char formula[] = "((((98.75 - 123.645 + 213.43 / 54.1) / 98.2 - 8) * 213.54 + 1.01) / 58.7)";
  TFormula tf(formula);
  const double resultEXP = ((((98.75 - 123.645 + 213.43 / 54.1) / 98.2 - 8) * 213.54 + 1.01) / 58.7);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_4)
{
  char formula[] = "956.83 + 568.274 - 9.4054 * 7.584 * 7.5945 / 0.4394 / 23.323";
  TFormula tf(formula);
  const double resultEXP = 956.83 + 568.274 - 9.4054 * 7.584 * 7.5945 / 0.4394 / 23.323;

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_5)
{
  char formula[] = "(9.78 + 2.03) / (1.85 - 5.597) * (9.78 + 2) / (9.5648 - 9.7)";
  TFormula tf(formula);
  const double resultEXP = (9.78 + 2.03) / (1.85 - 5.597) * (9.78 + 2) / (9.5648 - 9.7);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_6)
{
  char formula[] = "(95.5648 - 96.7) / (1.85 - 54.597) / (98.78 + 12) / (9.78 + 2.03)";
  TFormula tf(formula);
  const double resultEXP = (95.5648 - 96.7) / (1.85 - 54.597) / (98.78 + 12) / (9.78 + 2.03);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_7)
{
  char formula[] = "2 + 4 / 7 + 0.999 - 5.001";
  TFormula tf(formula);
  const double resultEXP = 2 + 4.0 / 7 + 0.999 - 5.001;

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_8)
{
  char formula[] = "(7 + 0.999 - 5.001) / (2 + 4)";
  TFormula tf(formula);
  const double resultEXP = (7 + 0.999 - 5.001) / (2 + 4);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_9)
{
  char formula[] = "2 + 2 * 2";
  TFormula tf(formula);
  const double resultEXP = 2 + 2 * 2;

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, calculator_check_10)
{
  char formula[] = "(1 + 2) / (3 + 4 * 6.7) - 5.3*4.4";
  TFormula tf(formula);
  const double resultEXP = (1 + 2) / (3 + 4 * 6.7) - 5.3*4.4;

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}

TEST(TFormula, brackets_table_check)
{
  char formula[] = "((1)3 23  1()3  3) ( )(12)( (3 (3)) 1  6)64((3)(";
  TFormula tf(formula);
  const int bracketsEXP[] = {2, 3, 4, 5,1,6,7,8,9,10,13,14,12,15,11,16,18,19,20,0,17,0};
  const int SZ = sizeof bracketsEXP / sizeof(int);
  int brackets[MaxLen];

  tf.FormulaChecker(brackets, MaxLen);

  int r = std::mismatch(bracketsEXP, bracketsEXP + SZ, brackets).second - brackets;
  EXPECT_EQ(SZ, r);
}