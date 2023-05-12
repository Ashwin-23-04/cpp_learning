#include<iostream>
#include<mutex>
#include<thread>

std::recursive_mutex m1;
int buffer = 0 ;

// with recursion fuction

void recFuc(std::string threadName ,int loopFor){
    if(loopFor < 0)
        return;
    m1.lock();
    std::cout << threadName << " #" << buffer++ << std::endl;
    recFuc(threadName, --loopFor);
    m1.unlock();
}

// int main(){
//     std::thread t1(recFuc, "Thread 1", 10);
//     std::thread t2(recFuc, "Thread 2", 10);
//     t1.join();
//     t2.join();
//     return 0;
// }

// with loop

int main(){
    for (int i = 0; i < 5 ; i++){
        m1.lock();
        std::cout << "Locked " << i << std::endl;
    }
    for (int i = 0; i < 5 ; i++){
        m1.unlock();
        std::cout << "Unlocked " << i << std::endl;
    }
    return 0;
}