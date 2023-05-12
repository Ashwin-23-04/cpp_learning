# include<iostream>


void func(double *pArr, int size){

    for (int i = 0; i < size ; i++){
        std::cout << *(pArr + i) << std::endl ;
    }
}

void twoD(int *pArr, int rowSize , int columnSize){
    for (int i = 0 ; i < rowSize ; i ++){
        for (int j=0; j< columnSize ; j++){
            std::cout << i << " , " << j << " : " << *(pArr++) << std::endl;
        }
    }
}

int main(){
    double arr[5] = {1,2,3,4,5};

    int my_array[2][3] = {{1, 2, 3}, {4, 5, 6}};


    // std::cout << *(*(my_array+0) + 1) << std::endl;


    // std::cout << sizeof(arr) << std::endl;
    // std::cout << sizeof(double) << std::endl;

    // int size = sizeof(arr) / sizeof(double);

    // func(arr, size);

    int (*pMy_array)[3] = my_array;
    // int *p = *my_array;


    

    // std::cout << sizeof(my_array) << std::endl;
    // std::cout << sizeof(my_array[0]) << std::endl;

    // std::cout << sizeof(my_array[0]) << std::endl;
    // std::cout << sizeof(my_array[0][0]) << std::endl;

    int rowSize = sizeof(my_array) / sizeof(my_array[0]);
    int columnSize = sizeof(my_array[0]) / sizeof(my_array[0][0]) ;

    // std::cout << rowSize << std::endl;
    // std::cout << columnSize << std::endl;

    // for (int i = 0 ; i < rowSize ; i ++){
    //     for (int j=0; j< columnSize ; j++){
    //         std::cout << i << " , " << j << " : " << &my_array[i][j] << std::endl;
    //     }
    // }

    // twoD(*my_array, rowSize, columnSize);
    return 0;
}