#include <iostream>

class Person {
public:
    std::string name;
    int age;
protected:
    char gender;
};

class Student : public Person {
public:
    int roll_no;
    void setGender(char g) {
        gender = g; // valid as gender is protected in the base class
    }
    void getGender(){
        std::cout << gender ;
    }
};

int main() {
    Person p;
    p.name = "John";
    p.age = 30;
    // p.gender = 'M'; // invalid as gender is protected in the base class
    
    Student s;
    s.name = "Mary";
    s.age = 20;
    s.setGender('F'); // valid as setGender is a public member in the derived class
    s.roll_no = 100;

    std::cout << p.name << "\n" << p.age << "\n" << s.roll_no <<std::endl;
    s.getGender();
    
    return 0;
}
