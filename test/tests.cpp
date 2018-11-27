#include<gtest.h>

#include"tstack.h"

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

TEST(TStack, get_and_top_value_returns_the_same_value)
{
  TStack st(5);

  st.Put(1);
  int te = st.TopElem();

  EXPECT_EQ(te, st.Get());
}