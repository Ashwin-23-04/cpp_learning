#include<iostream>

class DataBase{
    private:
        static DataBase *db;
        DataBase(){}
        int arr[4];
    public:
        static DataBase* getInstance();
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

DataBase *DataBase::db = nullptr;
DataBase *DataBase::getInstance(){
    if(db == nullptr){
        db = new DataBase();
        return db;
    }else{
        return db;
    }
}

int main(){
    DataBase* db = DataBase::getInstance();
    db->makeArray(4,5,6);
    db->show();
    DataBase* db2 = DataBase::getInstance();
    db2->lastElement(7);
    db2->show();

    return 0;
}


// #include<iostream>

// class DataBase{
//     private:
//         DataBase(){}
//         int arr[4];
//     public:
//         static DataBase& getInstance(){
//             static DataBase db;
//             return db;
//         }
//         void makeArray(int x, int y, int z){
//             arr[0] = x;
//             arr[1] = y;
//             arr[2] = z;
//         }
//         void lastElement(int x){
//             arr[3] = x;
//         }
//         void show(){
//             for(int x : arr){
//                 std::cout << x << " ";
//             }
//             std::cout << std::endl;
//         }
// };

// int main(){
//     DataBase& db = DataBase::getInstance();
//     db.makeArray(4,5,6);
//     db.show();
//     DataBase& db2 = DataBase::getInstance();
//     db2.lastElement(7);
//     db2.show();

//     return 0;
// }