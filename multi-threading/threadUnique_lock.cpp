#include<iostream>
#include<mutex>
#include<thread>

std::mutex m1;

/*
void recFuc(std::string threadName ,int loopFor){
    std::unique_lock<std::mutex> lock(m1); // work on scope basis
    for (int i=0; i < loopFor ; i++){
        std::cout << threadName << " #" << i << std::endl;
    }
}
*/

void recFuc(std::string threadName ,int loopFor){
    std::unique_lock<std::mutex> lock(m1, std::defer_lock); // lock explicitily and don't need to unlock it
    std::cout << threadName << " entered loop" << std::endl;
    lock.lock();
    for (int i=0; i < loopFor ; i++){
        std::cout << threadName << " #" << i << std::endl;
    }
}


int main(){
    std::thread t1(recFuc, "Thread 1", 10);
    std::thread t2(recFuc, "Thread 2", 10);
    t1.join();
    t2.join();
    return 0;
}