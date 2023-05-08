#include<iostream>

class Student {
    public:
        std::string name;
        int age;
        double gpa;

    Student(std::string name, int age, double gpa){
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }
};

void printData(Student &student);

int main(){
    Student s1 = Student("Ashwin", 21, 4.1);
    printData(s1);
    return 0;
}

void printData(Student &student){
    std::cout << student.name << "\t" << student.age << "\t" << student.gpa << std::endl;
}