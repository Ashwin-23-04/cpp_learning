#include<iostream>

class Strategy{
    public:
        virtual void compute(){}
};

class Operation : public Strategy{
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
        Strategy *strategy;
    public:
        Calc(Strategy *strategy){
            this->strategy = strategy;
        }
        void compute(){
            this->strategy->compute();
        }
};

int main(){
    Operation *op = new PlusOperation(6, 7);
    Calc calc1 = Calc(op);
    calc1.compute();
    op = nullptr;
    op = new MinusOperation(4,3);
    Calc calc2 = Calc(op);
    calc2.compute();
    return 0;
}