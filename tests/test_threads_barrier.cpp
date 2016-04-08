//
// Created by Ivan Shynkarenka on 17.03.2016.
//

#include "catch.hpp"

#include "threads/barrier.h"
#include "threads/thread.h"

#include <atomic>
#include <thread>

using namespace CppCommon;

TEST_CASE("Barrier single thread", "[CppCommon][Threads]")
{
    Barrier barrier(1);
    REQUIRE(barrier.Wait());
}

TEST_CASE("Barrier multiple threads", "[CppCommon][Threads]")
{
    int concurrency = 8;
    std::atomic<bool> failed = false;
    std::atomic<int> count = 0;
    std::atomic<int> last = 0;
    Barrier barrier(concurrency);

    // Start some threads
    std::vector<std::thread> threads;
    for (int thread = 0; thread < concurrency; ++thread)
    {
        threads.push_back(std::thread([&barrier, &count, &last, &failed, concurrency, thread]()
        {
            // Increment threads counter
            ++count;

            // Sleep for a while...
            CppCommon::Thread::SleepFor(std::chrono::milliseconds(thread * 100));

            // Wait for all other threads at the barrier
            if (barrier.Wait())
                ++last;

            // Check result in each thread
            if (count != concurrency)
                failed = true;
        }));
    }

    // Wait for all threads to complete
    for (auto& thread : threads)
        thread.join();

    // Check results
    REQUIRE(count == concurrency);
    REQUIRE(last == 1);
    REQUIRE(!failed);
}
