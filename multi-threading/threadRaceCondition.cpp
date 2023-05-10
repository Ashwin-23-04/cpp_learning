/*
Race Condition is a situation where two or more threads try to modify a same data
*/

#include<iostream>
#include<thread>

int x = 0;

void inc(){
    x++;
}

int main() {
    std::thread t1(inc);
    std::thread t2(inc);

    t1.join();
    t2.join();

    std::cout << "Result : " << x; // expected output is 2 but sometimes we get 1 --> this results in raceCondition.
    return 0;
}

// This can be avoid using mutex