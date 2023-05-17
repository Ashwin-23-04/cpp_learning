#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

std::condition_variable cv;
std::mutex m;
int balance = 0;

void addMoney(int amount){
    std::lock_guard<std::mutex> lock(m);
    balance += amount;
    std::cout << "Added Money" << std::endl;
    cv.notify_one();
}

void withdraw(int amount){
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock , []{return balance!=0 ? true : false;});
    if (balance >= amount){
        balance -= amount;
        std::cout << "withdraw success" << std::endl;
    }else{
        std::cout << "Balance is less than " << amount << std::endl;
    }
}


int main(){
    std::thread t1(withdraw, 600);
    std::thread t2(addMoney, 500);
    t1.join();
    t2.join();
    return 0;
}


// int main(){
//     char buffer[1024] = {0};
//     std::cout << strlen(buffer) << std::endl;
//     strcpy(buffer, "hello bro");
//     std::cout << strlen(buffer) << std::endl;
//     // memset(buffer, 0, sizeof(buffer));
//     // std::cout << strlen(buffer) << std::endl;
//     std::cout << buffer << std::endl;
//     return 0;
// }