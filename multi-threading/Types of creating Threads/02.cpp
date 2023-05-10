// Using lambda function

#include<iostream>
#include<thread>

template<typename T>
auto someFunc = [](T something1, T something2){
    std::cout << something1 + something2 << std::endl;
};

int main(){
    std::thread thread1(someFunc<int>,1,2);
    std::thread thread2(someFunc<std::string>, "Hello", " World ");
    
    thread1.join();
    thread2.join();
    return 0;
}