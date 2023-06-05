#include<iostream>

class Memento{
    private:
        std::string state;
    public:
        Memento(std::string state){
            this->state = state;
        } 
        std::string getState(){
            return state;
        }
};

class Originator{
    private :
        std::string state;
    public:
        void setState(std::string state){
            this->state = state;
        }
        std::string getState(){
            return state;
        }
        Memento* saveStateToMemento(){
            return new Memento(state);
        }
        void getStateFromMemento(Memento *memento){
            state = memento->getState();
        }
};

class CareTaker{
    private:
        std::vector<Memento*> mementos;
    public:
        void add(Memento *memento){
            mementos.push_back(memento);
        }
        Memento* get(int index){
            return mementos.at(index);
        }
};

int main(){

    Originator *originator = new Originator();
    CareTaker *careTaker = new CareTaker();

    originator->setState("state 1");
    originator->setState("state 2");
    careTaker->add(originator->saveStateToMemento());

    originator->setState("state 3");
    careTaker->add(originator->saveStateToMemento());

    originator->setState("state 4");
    std::cout << "Current State : " << originator->getState() << std::endl;

    originator->getStateFromMemento(careTaker->get(0));
    std::cout << "First Saved State : " << originator->getState() << std::endl;

    originator->getStateFromMemento(careTaker->get(1));
    std::cout << "First Saved State : " << originator->getState() << std::endl;

    return 0;
}