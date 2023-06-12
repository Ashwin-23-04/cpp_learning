#include<iostream>

class Expression{
    public:
        virtual bool interpreter(std::string context) = 0;
};

class TerminalExpression : public Expression {
    private:
        std::string data;
    public:
        TerminalExpression(std::string data){
            this->data = data;
        }
        bool interpreter(std::string context){
            if (data.compare(context) == 0) {
                return true;
            }
            return false;
        }
};

class OrExpression : public Expression{
    private:
        Expression *exp1;
        Expression *exp2;
    public:
        OrExpression(Expression *exp1, Expression *exp2){
            this->exp1 = exp1;
            this->exp2 = exp2;
        }
        bool interpreter(std::string context){
            return exp1->interpreter(context) || exp2->interpreter(context);
        }
};

int main(){
    std::string cmd;
    bool check;
    while(true){
        std::cout << "> " ;
        std::getline(std::cin >> std::ws , cmd);
        Expression *e = new OrExpression(new TerminalExpression("ls") , new TerminalExpression("list"));
        check = e->interpreter(cmd);
        if(check){
            std::cout << "Listing Directory " << std::endl;
        }else{
            std::cout << "Invalid Command" << std::endl;
        }
    }
    return 0;
}