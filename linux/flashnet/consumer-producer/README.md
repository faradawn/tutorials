# Three Consumer-Producer Models 

### Model 1: Simple Queue

A single producer pushes 10 workloads to a queue from the back, 
and 3 consumers take turns to clear the queue from the front. 

The consumers wait when the queue is empty, and exit when 
the producer is done.
```
g++ -std=c++14 method-1.cpp -o method-1; ./method-1

Estimated time: 2020 ms
Actual time: 745 ms, num_consumers: 3
```

### Method 2: Lock-Free Queue

To avoid repeatedly locking the queue when a producer
or consumer accesses the queue, we can use a lock-free 
implementation that utilizes the following atomic operations:

load(), exchange(), and compare_and_exchange()

Still, we would need a conditional variable to let consumers 
wait when the queue is empty. Currently, we are letting 
producer fill the queue first before unleashing the consumers. 
```
g++ -std=c++14 method-2.cpp -o method-2; ./method-2

Estimated time: 2020 ms
Actual time: 738 ms, num_consumers: 3
```


### Method 3: Workload Stealing

The producer round-robinly assigns workload to each of the consumers, 
each of which has a local queue. When a consumer's queue is empty, 
it will try to steal workloads from other queues. 

This method performs better in a distributed setting, where the 
global queue is far from each node. Yet, on a single machine, this 
method is slower than the previous two.

```
g++ -std=c++14 method-3.cpp -o method-3; ./method-3

Estimated time: 2020 ms
Actual time: 816 ms, num_consumers: 3
```