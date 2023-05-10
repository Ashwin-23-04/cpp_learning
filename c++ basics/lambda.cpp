#include<iostream>

int main(){

    int numberOne = 1;
    auto someFunc = [&numberOne](int a , int b) -> double{ // return type default is Integer
        return (numberOne + a) / b;
    };

    double result = someFunc(2,3);
    std::cout << "Result :\t" << result;

    return 0;
}