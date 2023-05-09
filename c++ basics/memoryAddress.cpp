#include<iostream>

typedef std::string text_t;

void swap(text_t &x, text_t &y);

int main() {
    text_t x = "30";
    text_t y = "40";

    std::cout << "Before swapping: \nx: " << x << "\ny: " << y << std::endl;

    swap(x,y);

    std::cout << "After swapping: \nx: " << x << "\ny: " << y << std::endl;

    return 0;
}

void swap(text_t &x, text_t &y){
    text_t temp ;
    temp = x ;
    x = y;
    y = temp;
}