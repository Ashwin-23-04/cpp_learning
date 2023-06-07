#include<iostream>

class Television{
    private:
        bool onOffState;
    public:
        void switchOff(){
            std::cout << "Television is switched off" << std::endl;
            this->onOffState = false;
        }
        void switchOn(){
            std::cout << "Television is switched on" << std::endl;
            this->onOffState = true;
        }
        bool isSwitchedOn(){
            if(onOffState){
                return true;
            }else{
                return false;
            }
            
        }
};

class RemoteController{
    private :
        Television *tv;
    public:
        void pressPowerButton(){
            if(tv->isSwitchedOn()){
                tv->switchOff();
            }else{
                tv->switchOn();
            }
        }
};

int main(){
    RemoteController remote;
    remote.pressPowerButton();
    remote.pressPowerButton();
    remote.pressPowerButton();
    return 0;
}