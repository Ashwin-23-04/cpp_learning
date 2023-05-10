// Using staic member Function

#include<iostream>
#include<thread>

template<typename T>
class SomeClass{
    public:
    static T someFunc(T something1, T something2){
        std::cout << something1 + something2 << std::endl;
    }
};

int main(){
    std::thread thread1(&SomeClass<int>::someFunc,1,2);
    std::thread thread2(&SomeClass<std::string>::someFunc, "Hello", " World ");
    
    thread1.join();
    thread2.join();
    return 0;
}