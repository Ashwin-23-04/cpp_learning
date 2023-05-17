#include <iostream>
#include<thread>
#include<chrono>
#include<mutex>

int count = 0;
std::timed_mutex m;

void someFuc(std::string threadName){
    if(m.try_lock_for(std::chrono::seconds(3))){ // 1
        count++;
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 2
        std::cout << threadName << " has entered." << std::endl;
        m.unlock();
    }else{
        std::cout << threadName << " has not entered." << std::endl;
    }
}

// void someFuc(std::string threadName){
    // auto now = std::chrono::steady_clock::now();
    // if(m.try_lock_until( now + std::chrono::seconds(1))){
//         count++;
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//         std::cout << threadName << " has entered." << std::endl;
//         m.unlock();
//     }else{
//         std::cout << threadName << " has not entered." << std::endl;
//     }
// }

int main(){
    std::thread t1 (someFuc, "thread 1");
    std::thread t2 (someFuc, "thread 2");

    t1.join();
    t2.join();
    std::cout << "Count Value : " << count ;
    return 0;
}