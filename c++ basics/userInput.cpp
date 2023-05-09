#include <iostream>

int main(){
    std::string name;
    int age;

    std::cout << "Enter your full name : ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "\nEnter your age : ";
    std::cin >> age;

    std::cout << "Hello " << name << ". Your age is " << age << std::endl;
    return 0;
}