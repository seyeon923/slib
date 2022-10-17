#include <gtest/gtest.h>

#include "include/slib/list.h"

TEST(SampleTest, Test1) {
    slib_list_node node;
    slib_list_init_node(&node);
    EXPECT_EQ(node.next, &node);
    EXPECT_EQ(node.prev, &node);
}