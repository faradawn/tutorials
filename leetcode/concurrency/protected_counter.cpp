#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int counter = 0;
mutex mtx;

void incr(int n){
    mtx.lock();
    for(int i = 0; i < n; i++){
        counter ++;
    }
    mtx.unlock();
}

int main(){
    thread threads[5];
    for(int i = 0; i < 5; i++){
        threads[i] = thread(incr, 1000);
    }
    for(int i = 0; i < 5; i++){
        threads[i].join();
    }
    // put this after join threads 
    cout<<"counter is "<< counter<<endl;
}