#include <gtest/gtest.h>
#include "Ownheap.hpp"
#include "vector"
using OwnheapInt = Ownheap<int>;
class HeapTestUnit :public ::testing::Test{
  protected:
    void SetUp() override {
      v = Ownheap<int>(s);
    }

    // void TearDown() override {
    // }

    Ownheap<int> v;
    std::vector<int> s = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
};

TEST_F(HeapTestUnit, ClearAssertions){
  EXPECT_EQ(v.size(),s.size());
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST_F(HeapTestUnit, PopAssertions){
    EXPECT_EQ(v.size(),s.size());
    for(size_t i = 0; i < s.size(); i++){
      EXPECT_EQ(v.pop(), 90 - 10 * i);
    }
    EXPECT_EQ(v.size(), 0);
}

TEST_F(HeapTestUnit, PushAssertions){
     EXPECT_EQ(v.size(),s.size());

     for(size_t i = 100; i <= 200; i+=10){
        v.push(i);
     }

      for(size_t i = 0; i <= 20; i++){
       EXPECT_EQ(v.pop(), 200 - 10 * i);
     }
     EXPECT_EQ(v.size(), 0);
}

// Demonstrate some basic assertions.
// TEST(HeapTest, BasicAssertions) {

//     std::vector<int> s = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
//     OwnheapInt v = OwnheapInt(s);

//     EXPECT_EQ(v.size(), s.size());
//     EXPECT_EQ(0, 0);

// }
