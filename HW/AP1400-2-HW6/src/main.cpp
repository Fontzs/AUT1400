#include <gtest/gtest.h>

#include <iostream>

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char **argv) {
    if (true)  // make false to run unit-tests
    {
        // auto min1 = q1::gradient_descent(0.01, 0.1, cos);
        // EXPECT_NEAR(min1, 3.14, 0.1);

        // auto min2 = q1::gradient_descent(0.01, 0.01, cos);
        // EXPECT_NEAR(min2, 3.14, 0.01);

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