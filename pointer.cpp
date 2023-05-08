#include<iostream>

int main(){
    // std::string name = "Ashwin";

    // std::string *pNname = &name;

    // std::cout<< name << std::endl;
    // std::cout<< pNname << std::endl;
    // std::cout<< *pNname << std::endl;


    int *pointer = nullptr;

    int x = 23;

    // pointer = &x;

    if (pointer == nullptr){
        std::cout << "Pointer is not assigned" << std::endl;
        std::cout << *pointer;
    }else {
        std::cout << "Pointer is assigned" << std::endl;
    }

    return 0;
}