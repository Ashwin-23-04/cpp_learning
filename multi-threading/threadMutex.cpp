#include<iostream>
#include<mutex>
#include<thread>

int x = 0;
std::mutex m;

void inc(){
    m.lock();
    std::cout << std::this_thread::get_id() << std::endl;
    x++; // this is a critical section 
    m.unlock();
}

int main() {
    std::thread t1(inc);
    std::thread t2(inc);

    t1.join();
    t2.join();

    std::cout << "Result : " << x;
    return 0;
}