#include <gtest/gtest.h>

#include <iostream>

#include "cappuccino.h"
#include "espresso_based.h"
#include "ingredient.h"
#include "mocha.h"
#include "sub_ingredients.h"
using std::cout;
using std::endl;
int main(int argc, char** argv) {
    if (false)  // make false to run unit-tests
    {
        Cappuccino cappuccino;
        cappuccino.add_side_item(new Chocolate{2});
        Cappuccino copy{cappuccino};
        // EXPECT_EQ(copy.get_name(), "Cappuccino");
        // EXPECT_DOUBLE_EQ(copy.price(), 65);

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