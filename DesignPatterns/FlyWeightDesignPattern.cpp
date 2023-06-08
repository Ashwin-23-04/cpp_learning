#include<iostream>
#include<map>

enum Type{
    DEVELOPER = 0,
    TESTER = 1
};

class Employee{
    public:
        virtual void assignSkill(std::string skill) {}
        virtual void task(){}
};

class Developer: public Employee{
    private:
        std::string jobTitle;
        std::string skill;
    public:
        Developer(){
            this->jobTitle = "Fix the issue";
        }
        void assignSkill(std::string skill) {
            this->skill = skill;
        }
        void task(){
            std::cout << "Developer with a skill " << skill << " has job title " << jobTitle << std::endl;
        }
};

class Tester: public Employee{
    private:
        std::string jobTitle;
        std::string skill;
    public:
        Tester(){
            this->jobTitle = "Test the issue";
        }
        void assignSkill(std::string skill){
            this->skill = skill;
        }
        void task(){
            std::cout << "Tester with a skill " << skill << " has job title " << jobTitle << std::endl;
        }
};

class EmployeeFactory{
    private:
        std::map<Type, Employee*> empMap;
    public:
        EmployeeFactory(){
            empMap[DEVELOPER] = nullptr;
            empMap[TESTER] = nullptr;
        }
        Employee* getEmployee(Type type){
            Employee *emp = nullptr;
            std::map<Type, Employee*>::iterator iter = empMap.find(type);
            
            if(iter->second != nullptr){
                emp = iter->second;
            }else{
                switch (type)
                {
                case DEVELOPER:
                    emp = new Developer();
                    break;
                
                case TESTER:
                    emp = new Tester();
                    break;
                }

                empMap[type] = emp;
            }
            return emp;
        }
};

int main(){
    EmployeeFactory *empFactory = new EmployeeFactory();
    
    Employee *e1 = empFactory->getEmployee(DEVELOPER);
    Employee *e2 = empFactory->getEmployee(TESTER);
    Employee *e3 = empFactory->getEmployee(DEVELOPER);
    Employee *e4 = empFactory->getEmployee(TESTER);

    e1->assignSkill("JAVA");
    e2->assignSkill("C");
    e1->task();
    e2->task();

    e3->assignSkill("PYTHON");
    e4->assignSkill("C++");
    e3->task();
    e4->task();
    return 0;
}