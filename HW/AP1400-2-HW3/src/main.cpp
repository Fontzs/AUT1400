#include <gtest/gtest.h>

#include <iostream>

#include "bst.h"
using std::cout;
using std::endl;
int main(int argc, char** argv) {
    if (false)  // make false to run unit-tests
    {
        BST bst{};
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(65);
        bst.add_node(60);
        bst.add_node(70);
        bst.add_node(5);
        bst.add_node(2);
        bst.add_node(7);
        bst.add_node(75);
        bst.add_node(20);
        bst.add_node(15);

        EXPECT_EQ(bst.length(), 12);
        EXPECT_TRUE(bst.delete_node(10));  // both children exist
        EXPECT_EQ(bst.length(), 11);
        EXPECT_EQ(bst.get_root()->left->value, 7);
        EXPECT_EQ(bst.get_root()->left->left->right, nullptr);
        EXPECT_EQ(bst.get_root()->left->left->value, 5);

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}