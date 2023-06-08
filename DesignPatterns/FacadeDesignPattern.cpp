#include<iostream>

class AC{
    public:
    void on(){
        std::cout << "AC is on" << std::endl;
    }
    void off(){
        std::cout << "AC is off" << std::endl;
    }
};

class TV{
    public:
    void on(){
        std::cout << "TV is on" << std::endl;
    }
    void off(){
        std::cout << "TV is off" << std::endl;
    }
};

class Facade{
    private:
        AC ac;
        TV tv;
    public:
        void goForWork(){
            ac.off();
            tv.off();
        }
        void comeHome(){
            ac.on();
            tv.on();
        }
};

int main(){
    Facade f;
    f.comeHome();
    f.goForWork();
    return 0;
}