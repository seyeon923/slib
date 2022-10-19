#include <array>
#include <list>
#include <vector>
#include <source_location>

#include <gtest/gtest.h>

#include "include/slib/list.h"

#include "tests/test_utils.h"

class ListTest : public ::testing::Test {
protected:
    constexpr static int NUM_NODES = 100;
    std::array<slib_list_node_t, NUM_NODES> nodes;
    slib_list_node_t head;

    void SetUp() override { slib_list_init_node(&head); }

    void CheckListOrder(
        const std::list<size_t>& indices,
        const std::source_location location = std::source_location::current()) {
        ASSERT_EQ(slib_list_get_size(&head), indices.size())
            << " from " << ToString(location);
        slib_list_node_t* p = head.next;
        for (auto idx : indices) {
            EXPECT_EQ(p, &nodes[idx]) << " from " << ToString(location);
            p = p->next;
        }
        EXPECT_EQ(p, &head) << " from " << ToString(location);
    }

    void PushBackNodes(const std::vector<size_t>& indices) {
        for (auto i : indices) {
            slib_list_push_back(&head, &nodes[i]);
        }
    }
};

TEST_F(ListTest, NdeInitTest) {
    EXPECT_EQ(head.next, &head);
    EXPECT_EQ(head.prev, &head);
    EXPECT_EQ(slib_list_get_size(&head), 0);
    EXPECT_TRUE(slib_list_is_empty(&head));
}

TEST_F(ListTest, PushPopTest) {
    slib_list_push_back(&head, &nodes[0]);
    CheckListOrder({0});
    slib_list_push_back(&head, &nodes[1]);
    CheckListOrder({0, 1});
    slib_list_push_back(&head, &nodes[2]);
    CheckListOrder({0, 1, 2});

    slib_list_push_front(&head, &nodes[3]);
    CheckListOrder({3, 0, 1, 2});
    slib_list_push_front(&head, &nodes[4]);
    CheckListOrder({4, 3, 0, 1, 2});
    slib_list_push_front(&head, &nodes[5]);
    CheckListOrder({5, 4, 3, 0, 1, 2});

    slib_list_push_back(&head, &nodes[6]);
    CheckListOrder({5, 4, 3, 0, 1, 2, 6});
    slib_list_push_back(&head, &nodes[7]);
    CheckListOrder({5, 4, 3, 0, 1, 2, 6, 7});

    EXPECT_EQ(slib_list_pop_back(&head), &nodes[7]);
    CheckListOrder({5, 4, 3, 0, 1, 2, 6});
    EXPECT_EQ(slib_list_pop_front(&head), &nodes[5]);
    CheckListOrder({4, 3, 0, 1, 2, 6});

    slib_list_push_back(&head, &nodes[10]);
    CheckListOrder({4, 3, 0, 1, 2, 6, 10});
    slib_list_push_front(&head, &nodes[5]);
    CheckListOrder({5, 4, 3, 0, 1, 2, 6, 10});
    slib_list_push_front(&head, &nodes[8]);
    CheckListOrder({8, 5, 4, 3, 0, 1, 2, 6, 10});

    EXPECT_EQ(slib_list_pop_front(&head), &nodes[8]);
    CheckListOrder({5, 4, 3, 0, 1, 2, 6, 10});
    EXPECT_EQ(slib_list_pop_front(&head), &nodes[5]);
    CheckListOrder({4, 3, 0, 1, 2, 6, 10});
    EXPECT_EQ(slib_list_pop_front(&head), &nodes[4]);
    CheckListOrder({3, 0, 1, 2, 6, 10});
    EXPECT_EQ(slib_list_pop_back(&head), &nodes[10]);
    CheckListOrder({3, 0, 1, 2, 6});
    EXPECT_EQ(slib_list_pop_back(&head), &nodes[6]);
    CheckListOrder({3, 0, 1, 2});
    EXPECT_EQ(slib_list_pop_back(&head), &nodes[2]);
    CheckListOrder({3, 0, 1});
    EXPECT_EQ(slib_list_pop_back(&head), &nodes[1]);
    CheckListOrder({3, 0});
    EXPECT_EQ(slib_list_pop_front(&head), &nodes[3]);
    CheckListOrder({0});
    EXPECT_EQ(slib_list_pop_front(&head), &nodes[0]);
    CheckListOrder({});

    std::list<size_t> indices;
    // push backs from 0 to 99
    for (int i = 0; i < NUM_NODES; ++i) {
        slib_list_push_back(&head, &nodes[i]);
        indices.push_back(i);
        CheckListOrder(indices);
    }

    // pop fronts all(0 to 99)
    for (int i = 0; i < NUM_NODES; ++i) {
        EXPECT_EQ(slib_list_pop_front(&head), &nodes[i]);
        indices.pop_front();
        CheckListOrder(indices);
    }

    // push fronts from 0 to 99
    for (int i = 0; i < NUM_NODES; ++i) {
        slib_list_push_front(&head, &nodes[i]);
        indices.push_front(i);
        CheckListOrder(indices);
    }

    // pop backs all(0 to 99)
    for (int i = 0; i < NUM_NODES; ++i) {
        EXPECT_EQ(slib_list_pop_back(&head), &nodes[i]);
        indices.pop_back();
        CheckListOrder(indices);
    }
}

TEST_F(ListTest, PopEmptyListTest) {
    ASSERT_EQ(slib_list_get_size(&head), 0);
    EXPECT_EQ(slib_list_pop_back(&head), nullptr);
    EXPECT_EQ(slib_list_pop_front(&head), nullptr);
    EXPECT_EQ(slib_list_pop_front(&head), nullptr);
    EXPECT_EQ(slib_list_pop_nth(&head, 0), nullptr);
}

TEST_F(ListTest, HasNodeTest) {
    for (int i = 0; i < NUM_NODES; ++i) {
        EXPECT_FALSE(slib_list_has_node(&head, &nodes[i]));
    }

    slib_list_push_back(&head, &nodes[0]);
    slib_list_push_back(&head, &nodes[10]);
    slib_list_push_back(&head, &nodes[20]);
    slib_list_push_back(&head, &nodes[30]);

    EXPECT_TRUE(slib_list_has_node(&head, &nodes[0]));
    EXPECT_TRUE(slib_list_has_node(&head, &nodes[10]));
    EXPECT_TRUE(slib_list_has_node(&head, &nodes[20]));
    EXPECT_TRUE(slib_list_has_node(&head, &nodes[30]));

    for (int i = 0; i < NUM_NODES; ++i) {
        if (i == 0 || i == 10 || i == 20 || i == 30) {
            continue;
        }
        EXPECT_FALSE(slib_list_has_node(&head, &nodes[i]));
    }
}

TEST_F(ListTest, UnlinkTest) {
    PushBackNodes({0, 1, 2, 3, 4});
    CheckListOrder({0, 1, 2, 3, 4});

    slib_list_unlink(&nodes[2]);
    CheckListOrder({0, 1, 3, 4});
    slib_list_unlink(&nodes[4]);
    CheckListOrder({0, 1, 3});
    slib_list_unlink(&nodes[1]);
    CheckListOrder({0, 3});
    slib_list_unlink(&nodes[0]);
    CheckListOrder({3});
    slib_list_unlink(&nodes[3]);
    CheckListOrder({});
}

TEST_F(ListTest, UnlinkEmptyHeadTest) {
    slib_list_unlink(&head);
    CheckListOrder({});
}

TEST_F(ListTest, PushPopNthTest) {
    PushBackNodes({1, 2, 3, 4, 5});

    slib_list_push_nth(&head, &nodes[6], 2);
    CheckListOrder({1, 2, 6, 3, 4, 5});

    slib_list_push_nth(&head, &nodes[7], 4);
    CheckListOrder({1, 2, 6, 3, 7, 4, 5});

    slib_list_push_nth(&head, &nodes[8], 3);
    CheckListOrder({1, 2, 6, 8, 3, 7, 4, 5});

    slib_list_push_nth(&head, &nodes[9], 0);
    CheckListOrder({9, 1, 2, 6, 8, 3, 7, 4, 5});

    slib_list_push_nth(&head, &nodes[10], 9);
    CheckListOrder({9, 1, 2, 6, 8, 3, 7, 4, 5, 10});

    EXPECT_EQ(slib_list_pop_nth(&head, 2), &nodes[2]);
    CheckListOrder({9, 1, 6, 8, 3, 7, 4, 5, 10});

    EXPECT_EQ(slib_list_pop_nth(&head, 4), &nodes[3]);
    CheckListOrder({9, 1, 6, 8, 7, 4, 5, 10});

    EXPECT_EQ(slib_list_pop_nth(&head, 7), &nodes[10]);
    CheckListOrder({9, 1, 6, 8, 7, 4, 5});

    EXPECT_EQ(slib_list_pop_nth(&head, 0), &nodes[9]);
    CheckListOrder({1, 6, 8, 7, 4, 5});

    EXPECT_EQ(slib_list_pop_nth(&head, 3), &nodes[7]);
    CheckListOrder({1, 6, 8, 4, 5});

    EXPECT_EQ(slib_list_pop_nth(&head, 3), &nodes[4]);
    CheckListOrder({1, 6, 8, 5});

    EXPECT_EQ(slib_list_pop_nth(&head, 3), &nodes[5]);
    CheckListOrder({1, 6, 8});

    EXPECT_EQ(slib_list_pop_nth(&head, 2), &nodes[8]);
    CheckListOrder({1, 6});

    EXPECT_EQ(slib_list_pop_nth(&head, 1), &nodes[6]);
    CheckListOrder({1});

    EXPECT_EQ(slib_list_pop_nth(&head, 0), &nodes[1]);
    CheckListOrder({});
}

TEST_F(ListTest, PushPopInvalidNthTest) {
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(slib_list_pop_nth(&head, i), nullptr);
    }

    slib_list_push_nth(&head, &nodes[0], 1000);
    CheckListOrder({0});

    slib_list_push_nth(&head, &nodes[10], 1000);
    CheckListOrder({0, 10});

    EXPECT_EQ(slib_list_pop_nth(&head, 1000), nullptr);
    CheckListOrder({0, 10});
}

TEST_F(ListTest, GetNthTest) {
    PushBackNodes({5, 21, 2, 34, 46});

    EXPECT_EQ(slib_list_get_nth(&head, 0), &nodes[5]);
    EXPECT_EQ(slib_list_get_nth(&head, 1), &nodes[21]);
    EXPECT_EQ(slib_list_get_nth(&head, 2), &nodes[2]);
    EXPECT_EQ(slib_list_get_nth(&head, 3), &nodes[34]);
    EXPECT_EQ(slib_list_get_nth(&head, 4), &nodes[46]);
}

TEST_F(ListTest, GetInvalidNthTest) {
    EXPECT_EQ(slib_list_get_nth(&head, 0), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, 1), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, 2), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, 10000), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, static_cast<size_t>(-1)), nullptr);

    PushBackNodes({5, 21, 2, 34, 46});
    EXPECT_EQ(slib_list_get_nth(&head, 5), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, 10000), nullptr);
    EXPECT_EQ(slib_list_get_nth(&head, static_cast<size_t>(-1)), nullptr);
}

TEST_F(ListTest, IsEmptyTest) {
    EXPECT_TRUE(slib_list_is_empty(&head));
    slib_list_push_back(&head, &nodes[0]);
    EXPECT_FALSE(slib_list_is_empty(&head));
}