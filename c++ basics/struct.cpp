#include<iostream>

struct Student {
    std::string name ;
    double gpa;
    bool enrolled = true; // default memeber initializer
};

void printStudentData(Student &student);

int main(){
    Student student1;
    Student student2;
    Student student3;

    student1.name = "Ashwin";
    student1.gpa = 3.2;

    student2.name = "Max";
    student2.gpa = 1.2;

    student3.name = "Spicky";
    student3.gpa = 2.2;
    student3.enrolled = false;
    
    printStudentData(student1);
    printStudentData(student2);
    printStudentData(student3);

    return 0;
}

// Passing stuct as an argument

void printStudentData(Student &student){
    std::cout << student.name << "\t" << student.gpa << "\t" << student.enrolled << std::endl;
}