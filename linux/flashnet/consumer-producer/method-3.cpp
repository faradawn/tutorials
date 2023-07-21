/*
    Method 3: Workload Stealing

    The producer round-robinly assigns workload to each of the consumers, 
    each of which has a local queue. When a consumer's queue is empty, 
    it will try to steal workloads from other queues. 

    This method performs better in a distributed setting, where the 
    global queue is far from each node. Yet, on a single machine, this 
    method is slower than the previous two.

    g++ -std=c++14 method-3.cpp -o method-3; ./method-3

    Estimated time: 2020 ms
    Actual time: 816 ms, num_consumers: 3

*/

#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

struct Workload {
    int id;
    int time_needed;
};

const int NUM_WORKLOADS = 10;
const int NUM_CONSUMERS = 3;
int estimate_time = 0;

std::vector<std::deque<Workload>> consumers_queues(NUM_CONSUMERS);
std::vector<std::unique_ptr<std::mutex>> consumers_mutexes(NUM_CONSUMERS);
std::atomic<int> next_queue_index(0);
std::atomic<bool> producer_done(false);


void producer() {
    Workload workloads[NUM_WORKLOADS] = {
        {0, 100},
        {1, 200},
        {2, 150},
        {3, 300},
        {4, 250},
        {5, 120},
        {6, 180},
        {7, 220},
        {8, 270},
        {9, 230}
    };

    for (int i = 0; i < NUM_WORKLOADS; ++i) {
        Workload workload = workloads[i];
        estimate_time += workloads[i].time_needed;
        int consumer_index = i % NUM_CONSUMERS;
        {
            std::lock_guard<std::mutex> lock(*consumers_mutexes[consumer_index]);
            consumers_queues[consumer_index].push_back(workload);
        }
        // std::cout << "Producer pushed workload with id " << workload.id << " into the queue of consumer " << consumer_index + 1 << std::endl;
    }
    
    producer_done = true; // Indicate that the producer is done.
}

void consumer(int consumer_index) {
    while (true) {
        bool has_workload = false;
        Workload workload;

        {
            std::lock_guard<std::mutex> lock(*consumers_mutexes[consumer_index]);
            if (!consumers_queues[consumer_index].empty()) {
                workload = consumers_queues[consumer_index].front();
                consumers_queues[consumer_index].pop_front();
                has_workload = true;
            }
        }

        if (has_workload) {
            // std::cout << "Consumer " << consumer_index + 1 << " started workload with id " << workload.id << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(workload.time_needed));
            // std::cout << "Consumer " << consumer_index + 1 << " finished workload with id " << workload.id << std::endl;
        }
        else if (producer_done) {
            return; // Exit if there are no more workloads and the producer is done.
        }
    }
}

int main() {
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers_mutexes[i] = std::make_unique<std::mutex>();
    }

    std::thread producer_thread(producer);
    std::vector<std::thread> consumer_threads;

    auto start_time = std::chrono::high_resolution_clock::now(); // Record start time

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_threads.emplace_back(consumer, i);
    }

    producer_thread.join();
    for (auto& t : consumer_threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    int total_time = duration.count();

    std::cout << "Method 3: Workload Stealing" << std::endl;
    std::cout << "Estimated time: " << estimate_time << " ms" << std::endl;
    std::cout << "Actual time: " << total_time  << " ms, num_consumers: " << NUM_CONSUMERS << "\n";


    return 0;
}
