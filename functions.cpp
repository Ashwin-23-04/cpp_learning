#include<iostream>

void welcomeMsg(std::string name);
std::string returningFunc(){
    std::string anything;
    std::cout << "Enter Any thing : " ;
    std::getline(std::cin,anything);
    return anything;
}

void welcomeMsg(){
    std::cout << "Welcome !!";
}

int main(){
    std::string name = "Ashwin";
    std::string anythingMsg ;
    welcomeMsg(name);
    anythingMsg = returningFunc();
    std::cout << "This is anything message --> " << anythingMsg << std::endl;
    welcomeMsg();
    return 0;
}

void welcomeMsg(std::string name){
    std::cout << "Hello, " << name << std::endl;
}