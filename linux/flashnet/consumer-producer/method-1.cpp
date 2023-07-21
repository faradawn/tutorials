/*
    Method 1: Simple Queue
    
    A single producer pushes 10 workloads to a queue from the back, 
    and 3 consumers take turns to clear the queue from the front. 

    The consumers wait when the queue is empty, and exit when 
    the producer is done.

    g++ -std=c++14 method-1.cpp -o method-1; ./method-1
    
    Estimated time: 2020 ms
    Actual time: 745 ms, num_consumers: 3

*/

#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

struct Workload {
    int id;
    int time_needed;
};

std::queue<Workload> global_queue;
std::mutex queue_mutex;
std::condition_variable queue_cond;
bool producer_finished = false;
bool consumers_finished = false;
const int NUM_WORKLOADS = 10;
const int NUM_CONSUMERS = 3;
const int wait_time = 0; // Wait time of producer before issuing a workload
int producer_wait_time = 0;
int estimate_time = 0;

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
        // std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulating workload production
        std::this_thread::sleep_for(std::chrono::milliseconds(0)); // Simulating workload production
        producer_wait_time += wait_time;
        estimate_time += workloads[i].time_needed;

        std::unique_lock<std::mutex> lock(queue_mutex);
        global_queue.push(workloads[i]);
        // std::cout << "Producer pushed id " << workloads[i].id << std::endl;

        consumers_finished = false;
        lock.unlock();
        queue_cond.notify_all();
    }

    std::unique_lock<std::mutex> lock(queue_mutex);
    producer_finished = true;
    lock.unlock();
    queue_cond.notify_all();
}

void consumer(int consumer_id) {
    while (true) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cond.wait(lock, [] { return !global_queue.empty() || producer_finished; });

        if (!global_queue.empty()) {
            Workload workload = global_queue.front();
            global_queue.pop();
            // std::cout << "Consumer " << consumer_id << " start on id " << workload.id << std::endl;
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(workload.time_needed));

            // std::cout << "Consumer " << consumer_id << " finished id " << workload.id << std::endl;
        }
        else if (producer_finished) {
            if (consumers_finished) {
                // std::cout << "All consumers finished processing workloads. Simulation complete." << std::endl;
                break;
            }
            else {
                consumers_finished = true;
                lock.unlock();
                queue_cond.notify_all();
            }
        }
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_threads[NUM_CONSUMERS];

    auto start_time = std::chrono::high_resolution_clock::now(); // Record start time

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_threads[i] = std::thread(consumer, i + 1);
    }

    producer_thread.join();

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_threads[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    int total_time = duration.count();

    std::cout << "Method 1: Simple Queue" << std::endl;
    std::cout << "Estimated time: " << estimate_time << " ms" << std::endl;
    std::cout << "Actual time: " << total_time  << " ms, num_consumers: " << NUM_CONSUMERS << "\n";

    return 0;
}