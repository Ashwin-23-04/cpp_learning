/*
    Notes:
        1. Either join or detach should be called on thread object , otherwise during thread object's destructor it will terminate your program will be terminate
        2. Don't double join or double detach a thread it will result in program termination.
        3. Always use joinable() function to check a thread can be join or detach.

*/

#include<iostream>
#include<thread>

void printHello()
{
    std::cout << "Hello!" << std::endl;
}

int main(){
    std::thread firstThread(printHello);

    if(firstThread.joinable()){
        firstThread.join(); // wait for thread to complete
        // firstThread.detach(); // make thread as background process [after that no access to thread]
    }
    return 0;
}