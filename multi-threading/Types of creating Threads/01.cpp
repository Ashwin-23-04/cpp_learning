// Using Function Pointer

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

/*
Note:
    If we create multiple thread at the same time it doesn't guarentee which one will start first
*/