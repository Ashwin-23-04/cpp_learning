#include<iostream>

class Human {
    public:
        std::string name;
        std::string occupation;
        int age;

        void eat(){
            std::cout << "This person is eating" << std::endl;
        }
        void drink(){
            std::cout << "This person is drinking water" << std::endl;
        }
        void sleep(){
            std::cout << "This person is sleeping" << std::endl;
        }
};

void printData(Human &person);

int main(){
    Human person1;
    Human person2;

    person1.name = "Ashwin";
    person1.age = 21;
    person1.occupation = "Programmer";

    person2.name = "Max";
    person2.age = 2;
    person2.occupation = "Guard";

    printData(person1);
    printData(person2);
  
    person1.eat();
    person1.drink();
    person1.sleep();

    return 0;
}

void printData(Human &person){
    std::cout << person.name << "\t" << person.age << "\t" << person.occupation << std::endl;
}