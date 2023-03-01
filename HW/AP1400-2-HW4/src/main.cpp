#include <gtest/gtest.h>

#include <iostream>

#include "shared_ptr.h"
#include "unique_ptr.h"

int main(int argc, char **argv) {
    if (false)  // make false to run unit-tests
    {
        SharedPtr<int> ptr1{make_shared<int>(10)};
        SharedPtr<int> ptr2{ptr1};
        // EXPECT_EQ(*ptr1, 10);
        // EXPECT_EQ(*ptr2, 10);
        // EXPECT_EQ(ptr1.get(), ptr2.get());
        // EXPECT_EQ(ptr1.use_count(), 2);
        // EXPECT_EQ(ptr2.use_count(), 2);
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