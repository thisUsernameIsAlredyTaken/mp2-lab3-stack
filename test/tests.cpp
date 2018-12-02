#include<gtest.h>

#include"tstack.h"
#include"tformula.h"

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
  EXPECT_NE(0, tf2.FormulaChecker(brackets, SZ));
}

TEST(TFormula, postfix_form_check)
{
  char formula[] = "(2+4)/(7+1-5)";
  const char postfixEXP[] = "2 4+ 7 1 +5-/";
  TFormula tf(formula);

  tf.FormulaConverter();

  EXPECT_STREQ(postfixEXP, tf.getpostfix());
}

TEST(TFormula, throws_if_one_operand_is_missing)
{
  char formula[] = "  (2+  4\t \t)  /(7 + 0.999  -)  ";
  TFormula tf(formula);

  EXPECT_ANY_THROW(tf.FormulaConverter(););
}

TEST(TFormula, calculating_check)
{
  char formula[] = "(2+4)/(7+.999-5.001)";
  TFormula tf(formula);
  const double resultEXP = (2 + 4) / (7 + 0.999 - 5.001);

  tf.FormulaConverter();

  EXPECT_DOUBLE_EQ(resultEXP, tf.FormulaCalculator());
}
