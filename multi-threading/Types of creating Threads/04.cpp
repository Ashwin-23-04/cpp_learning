// non - static member function

#include<iostream>
#include<thread>

template<typename T>
class SomeClass{
    public:
    T someFunc(T something1, T something2){
        std::cout << something1 + something2 << std::endl;
    }
};

int main(){
    SomeClass<int> someClassInt;
    SomeClass<std::string> someClassString;

    std::thread thread1(&SomeClass<int>::someFunc,&someClassInt,1,2);
    std::thread thread2(&SomeClass<std::string>::someFunc,&someClassString, "Hello", " World ");
    
    thread1.join();
    thread2.join();


    return 0;
}