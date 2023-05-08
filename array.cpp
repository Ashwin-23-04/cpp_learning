#include<iostream>

int addArr(int arr[],int size){
    int total = 0;

    for (int i =0 ; i < size; i++){
        total += arr[i];
    }
    return total;
}

void sortArr(int arr[], int size){
    int temp;

    for(int i=0; i<size-1; i++){
        for(int j=0; j<size - i - 1; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){

    int arr[] = {10,1,4,7,2,3,5,9,6,8};
    int size = sizeof(arr) / sizeof(int);

    std::cout << addArr(arr, size)<< std::endl;

    sortArr(arr, size);

    for (int j : arr){
        std::cout<< j << " ";
    }
    return 0;
}