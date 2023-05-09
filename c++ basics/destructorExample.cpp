#include<iostream>

class Human{
    public:
        std::string name;
        int age;

    Human(std::string name, int age){
        this-> name = name;
        this->age = age;

        std::cout << "The constructor is invoked for human named " << name << std::endl;
    }

    ~Human(){
        std::cout << "The destructor is invoked for human named " << name << std::endl;
    }


};

int main(){

    Human persor("Ashwin", 21);
    Human person("Max", 2);

    person.age = 3;
    persor.age = 20;

    return 0;
}