/*
Types of creating threads 

1. Function Pointer
*/

#include<iostream>
#include<thread>

template<typename T>
void someFunc(T something1, T something2){
    std::cout << something1 + something2;
}

int main(){
    std::thread thread1(someFunc<int>, 5, 6);

    std::thread thread2(someFunc<std::string>, "Hello", " World ");


    thread1.join();
    thread2.join();
    return 0;
}