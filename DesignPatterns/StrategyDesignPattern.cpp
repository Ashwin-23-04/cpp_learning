#include<iostream>

class OperationStrategy{
    public:
        virtual void compute(){}
};

class Operation : public OperationStrategy{
    private:
        int a;
        int b;
    public:
        Operation(int a, int b){
            this->a = a;
            this->b = b;
        }
        int getA(){
            return a;
        }
        int getB(){
            return b;
        }
};

class PlusOperation : public Operation{

    public:
        PlusOperation(int a , int b) : Operation(a, b){}
        void compute(){
            std::cout << Operation::getA() << " + " << Operation::getB() << " = " << Operation::getA() + Operation::getB() << std::endl ;
        }
};

class MinusOperation : public Operation{

    public:
        MinusOperation(int a , int b) : Operation(a, b){}
        void compute(){
            std::cout << Operation::getA() << " - " << Operation::getB() << " = " << Operation::getA() - Operation::getB() << std::endl;
        }
};

class Calc {
    private:
        OperationStrategy *strategy;
    public:
        Calc(OperationStrategy *strategy){
            this->strategy = strategy;
        }
        void compute(){
            this->strategy->compute();
        }
};

int main(){
    PlusOperation plusOperation(6, 7);
    Calc calc1 = Calc(&plusOperation);
    calc1.compute();
    MinusOperation minusOperation(4,3);
    Calc calc2 = Calc(&minusOperation);
    calc2.compute();
    return 0;
}