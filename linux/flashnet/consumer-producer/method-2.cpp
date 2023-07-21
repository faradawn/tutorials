/*
    Method 2: Lock-Free Queue

    To avoid repeatedly locking the queue when a producer
    or consumer accesses the queue, we can use a lock-free 
    implementation that utilizes the following atomic operations:

    load(), exchange(), and compare_and_exchange()

    Still, we would need a conditional variable to let consumers 
    wait when the queue is empty. Currently, we are letting 
    producer fill the queue first before unleashing the consumers. 

    g++ -std=c++14 method-2.cpp -o method-2; ./method-2
    
    Estimated time: 2020 ms
    Actual time: 738 ms, num_consumers: 3
*/

#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <atomic>

struct Workload {
    int id;
    int time_needed;
};

template <typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() : head(nullptr), tail(nullptr) {}

    void push(const T& value) {
        Node* newNode = new Node(value);
        Node* prevTail = tail.exchange(newNode);
        if (prevTail != nullptr) {
            prevTail->next = newNode;
        }
        else {
            head = newNode;
        }
    }

    bool pop(T& value) {
        Node* oldHead = head.load();
        while (oldHead != nullptr) {
            if (head.compare_exchange_weak(oldHead, oldHead->next)) {
                value = oldHead->data;
                delete oldHead;

                if (head == nullptr) {
                    tail = nullptr;
                }

                return true;
            }
        }

        return false;
    }

};

LockFreeQueue<Workload> global_queue;
const int NUM_WORKLOADS = 10;
const int NUM_CONSUMERS = 3;
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
        estimate_time += workloads[i].time_needed;
        global_queue.push(workloads[i]);
        // std::cout << "Producer pushed workload with id " << workloads[i].id << " into the queue." << std::endl;
    }
}

void consumer(int consumer_id) {
    Workload workload;
    while (global_queue.pop(workload)) {
        // std::cout << "Consumer " << consumer_id << " started workload with id " << workload.id << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(workload.time_needed));
        // std::cout << "Consumer " << consumer_id << " finished workload with id " << workload.id << std::endl;
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_threads[NUM_CONSUMERS];

    auto start_time = std::chrono::high_resolution_clock::now(); // Record start time

    producer_thread.join(); // assumes producer pushed everything into queue before consumer begins 

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_threads[i] = std::thread(consumer, i + 1);
    }

    // producer_thread.join(); 

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_threads[i].join();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Record end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    int total_time = duration.count();


    std::cout << "Method 2: Lock-Free Queue" << std::endl;
    std::cout << "Estimated time: " << estimate_time << " ms" << std::endl;
    std::cout << "Actual time: " << total_time  << " ms, num_consumers: " << NUM_CONSUMERS << "\n";


    return 0;
}
