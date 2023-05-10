// Using Functors

#include<iostream>
#include<thread>

template<typename T>
class SomeClass{
    public:
    T operator()(T something1, T something2){
        std::cout << something1 + something2 << std::endl;
    }
};

int main(){
    SomeClass<int> someClassInt;
    SomeClass<std::string> someClassString;

    std::thread thread1(someClassInt,1,2);
    std::thread thread2(someClassString, "Hello", " World ");
    
    thread1.join();
    thread2.join();
    return 0;
}