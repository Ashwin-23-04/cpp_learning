#include<iostream>

int main(){
    int *pointer = nullptr;
    pointer = new int;

    *pointer = 11;

    std::cout << "Before deleteing Pointer value : " << *pointer << std::endl;

    delete pointer;

    std::cout << "After deleteing Pointer value : " << *pointer << std::endl;

    // In arrays

    int size ;
    std::cout << "Enter size of an array : " ;
    std::cin >> size;

    int *pointerForArr = new int[size];

    for(int i = 0 ; i < size ; i++){
        std::cout << "Enter value for #" << i + 1 << " : " ;
        std::cin >> *(pointerForArr + i);
    }

    for (int i = 0; i < size ; i++){
        std::cout << "Value in #" << i+1 << " : " << *(pointerForArr + i) << std::endl;
    }

    std::cout << "pointer value" << *pointerForArr << std::endl;

    delete[] pointerForArr;

    std::cout << "pointer value" << *pointerForArr << std::endl;

    return 0;
}