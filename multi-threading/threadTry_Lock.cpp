/*
std::try_lock() tries to lock all the lockable objects passed in it in a given order one by one.
--> If it fails to lock any one , it will release all the other ones it locked before
*/

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

int x=0, y=0;
int count = 5;
int fcount = 5;
std::mutex m1, m2;

void incFuction(int &variableName, std::mutex &m){
    for(int i = 0; i < fcount; i++){
        m.lock();
        variableName = 1;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void containerFunction(){
    int sum = 0;
    while (count > 0)
    {
        int tryLock = std::try_lock(m1, m2);
        if (tryLock != -1){
            if(x !=0 && y != 0){
                count--;
                std::cout << "count : " << count << std::endl;
                sum = sum + x + y;
                x = 0;
                y = 0;
                std::cout << "Sum : " << sum << std::endl;
            }
            m1.unlock();
            m2.unlock();
        }
    }
}

int main(){
    std::thread t1(incFuction, std::ref(x), std::ref(m1));
    std::thread t2(incFuction, std::ref(y), std::ref(m2));
    std::thread t3(containerFunction);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}