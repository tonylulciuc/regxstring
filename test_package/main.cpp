/**
 * @file main.cpp
 * @author Antony Lulciuc (antony@polybean.com)
 * @brief Launches GoogleTest test runner 
 * @version 0.1
 * @date 2021-04-21
 * 
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
