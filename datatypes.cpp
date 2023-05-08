#include<iostream>

int main(){
    // Integer (whole number)
    int firstNumber = 3;
    int secondNumber = 0;
    int sumOfFirstAndSecondNumber = firstNumber + secondNumber ;
    int marks = int(99.9);

    std::cout << "Interger Example: \n\t" << marks << std::endl;

    // boolean (true or false)
    bool like = true; // 1
    bool dislike = false; // 0

    std::cout << "Boolean Example: \n\t" << dislike << std::endl;

    // double 
    double pi = 3.14;

    std::cout << "Double Example: \n\t" << pi << std::endl;

    // character 
    char symbol = '@';

    std::cout << "Character Example :\n\t" << symbol << std::endl;

    // string
    std::string  name = "Ashwin";

    std::cout <<"String Example :\n\t" << name << std::endl;

    return 0;
}