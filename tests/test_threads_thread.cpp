//
// Created by Ivan Shynkarenka on 27.01.2016.
//

#include "catch.hpp"

#include "threads/thread.h"
#include "time/timestamp.h"

using namespace CppCommon;

TEST_CASE("Thread", "[CppCommon][Threads]")
{
    REQUIRE(Thread::CurrentThreadId() > 0);

    // Test Sleep() method
    for (int64_t i = 1; i < 10; ++i)
    {
        int64_t start = Timestamp::now();
        Thread::Sleep(i);
        int64_t stop = Timestamp::now();
        REQUIRE(((stop - start) >= 0));
    }

    // Test SleepFor() method
    for (int64_t i = 1; i < 1000000; i *= 10)
    {
        int64_t start = Timestamp::now();
        Thread::SleepFor(CppCommon::Timespan::nanoseconds(i));
        int64_t stop = Timestamp::now();
        REQUIRE(((stop - start) >= 0));
    }

    // Test SleepUntil() method
    for (int64_t i = 1; i < 1000000; i *= 10)
    {
        int64_t start = Timestamp::now();
        Thread::SleepUntil(CppCommon::Timestamp() + CppCommon::Timespan::nanoseconds(i));
        int64_t stop = Timestamp::now();
        REQUIRE(((stop - start) >= 0));
    }

    // Test Yield() method
    for (int64_t i = 0; i < 10; ++i)
    {
        int64_t start = Timestamp::now();
        Thread::Yield();
        int64_t stop = Timestamp::now();
        REQUIRE(((stop - start) >= 0));
    }
}
