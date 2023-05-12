#include<iostream>
#include<thread>

void printHello(){
    std::cout << "Hello!" << std::endl;
}

int main() {
    std::thread t1(printHello);
    std::thread t2 = std::move(t1);
    
    t2.join();
    return 0;
}