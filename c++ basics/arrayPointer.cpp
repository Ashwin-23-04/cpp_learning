#include<iostream>

int main(){
    float arr[3];
    float *pArr;

    std::cout << "Printing address using arr" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "arr[" << i << "] :\t" << &arr[i] << std::endl;
    }

    pArr = arr;

    std::cout << "Printing address using pointer" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "pointer + " << i << " :\t" << pArr + i << std::endl;
    }
    

    return 0;
}