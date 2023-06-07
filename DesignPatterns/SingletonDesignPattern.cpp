#include<iostream>

class DataBase{
    private:
        static DataBase db;
        DataBase(){}
        int arr[4];
    public:
        static DataBase& getInstance(){
            return db;
        }
        void makeArray(int x, int y, int z){
            arr[0] = x;
            arr[1] = y;
            arr[2] = z;
        }
        void lastElement(int x){
            arr[3] = x;
        }
        void show(){
            for(int x : arr){
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
};

void arrayys(){
    int arr[4] = {1,2,3,4};

}

int main(){
    DataBase& db = DataBase::getInstance();
    db.makeArray(4,5,6);
    db.show();
    arrayys();
    DataBase& db2 = DataBase::getInstance();
    db2.lastElement(7);
    db2.show();

    return 0;
}