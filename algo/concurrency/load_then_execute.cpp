#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
int processed = 0;

void data_loader(){
    mtx.lock();
    cout<<"loading data"<<endl;
    this_thread::sleep_for(chrono::microseconds(1000));
    processed = 1;
    cout<<"data processed"<<endl;
    mtx.unlock();
    cv.notify_all();
}

void master(){
    unique_lock<mutex> lck(mtx);
    cout<< "start waiting"<<endl;
    while(processed == 0){
        cv.wait(lck);
    }    
    cout<< "done process" << endl;
}

int main(){
    thread t2 = thread(master);
    thread t1 = thread(data_loader);
    t1.join();
    t2.join();
}