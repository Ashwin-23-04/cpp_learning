#include<iostream>
#include<thread>
#include<mutex>

std::mutex m;
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
    // m.lock();
    // if(db == nullptr){
    //     std::cout << "New Instance Created" << std::endl;
    //     db = new DataBase();
    // }
    // m.unlock();
    // return db;

    if(db == nullptr){
        m.lock();
        if(db == nullptr){
            std::cout << "New Instance Created" << std::endl;
            db = new DataBase();
        }
        m.unlock();
    }
    return db;    
}

void callInstance(){
    DataBase* db = DataBase::getInstance();
}

int main(){
    // DataBase* db = DataBase::getInstance();
    // db->makeArray(4,5,6);
    // db->show();
    // DataBase* db2 = DataBase::getInstance();
    // db2->lastElement(7);
    // db2->show();
    std::thread t1(callInstance);
    std::thread t2(callInstance);

    t1.join();
    t2.join();

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