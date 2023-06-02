#include <iostream>

class Employee{
    private:
        std::string name;
        std::string department;
        double salary;
        std::vector<Employee*> subordinates;
    public:
        Employee(std::string name, std::string department, double salary){
            this->name = name;
            this->department = department;
            this->salary = salary;
        }

        void addSubordinates(Employee *emp){
            subordinates.push_back(emp);
        }

        void removeSubordinates(Employee *emp){
            for(auto sub = subordinates.begin(); sub != subordinates.end(); sub++){
                if(*sub == emp){
                    subordinates.erase(sub);
                    break;
                }
            }
        }

        std::vector<Employee*> getSubordinates(){
            return subordinates;
        }

        std::string printInfo(){
            return "\n\nEmployee: \nName: " + name + "\nDepartment: " + department + "\nSalary: " + std::to_string(salary) ;
        }
};  


int main(){
    Employee emp1 = Employee("Max", "CEO" , 100000.00);
    Employee emp2 = Employee("Jacky", "Head Marketing" , 50000.00);
    Employee emp3 = Employee("Spicky", "Marketing" , 50000.00);
    Employee emp4 = Employee("Abishek", "sales" , 25000.00);
    Employee emp5 = Employee("Kevin", "sales" , 25000.00);

    emp1.addSubordinates(&emp2);
    emp1.addSubordinates(&emp3);

    emp2.addSubordinates(&emp4);
    emp3.addSubordinates(&emp5);

    for (Employee *i : emp1.getSubordinates()){
        std::cout << i->printInfo() << std::endl;
    }

    // emp1.removeSubordinates(&emp3);

    // for (Employee *i : emp1.getSubordinates()){
    //     std::cout << i->printInfo() << std::endl;
    // }
    return 0;
}