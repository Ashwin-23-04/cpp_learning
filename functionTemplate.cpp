#include<iostream>

// Function template is nothying but the generics

template<typename T, typename U>  

U findMax(T x, U y){   /// Alternatively, you can upgrade your compiler to a C++14-compatible version that allows auto as a return type.
    return (x > y) ? x : y;
}

int main(){
    std::cout << findMax(1, 2.3) << std::endl;
    return 0;
}