/*
Thread basics
*/

#include<iostream>
#include<thread>

void printHello()
{
    std::cout << "Hello!\tFrom thread : " << std::this_thread::get_id() << std::endl;
}

int main(){
    std::cout << "Total number of threads supported by the cpu" << std::thread::hardware_concurrency() << std::endl ;
    
    // creating a thread
    std::thread firstThread(printHello);
    firstThread.join();
    return 0;
}