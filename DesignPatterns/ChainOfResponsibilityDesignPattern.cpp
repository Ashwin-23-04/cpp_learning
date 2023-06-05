#include<iostream>

class Numbers{
    private:
        int num1;
        int num2;
        std::string result;
    public:
        Numbers (int n1, int n2, std::string cW) : num1(n1), num2(n2), result(cW) {}
        int getNum1(){return num1;}
        int getNum2(){return num2;}
        std::string getCalcWanted(){return result;}
};

class Chain{
    public:
        virtual void setNextChain(Chain *nextChain){}
        virtual void calculate(Numbers request){}
};

class AddNumbers : public Chain {
    private:
        Chain *nextInChain;
    public:
        void setNextChain(Chain *nextChain){
            nextInChain = nextChain;
            
        }
        void calculate(Numbers request){
            if(request.getCalcWanted() == "Add"){
                std::cout << request.getNum1() << " + " << request.getNum2() << " = " << request.getNum1() + request.getNum2() << std::endl;            
            }else{
                nextInChain->calculate(request);
            }
        }
};

class SubtractNumbers : public Chain {
    private:
        Chain *nextInChain;
    public:
        void setNextChain(Chain *nextChain){
            nextInChain = nextChain;
        }
        void calculate(Numbers request){
            if(request.getCalcWanted() == "Sub"){
                std::cout << request.getNum1() << " - " << request.getNum2() << " = " << request.getNum1() - request.getNum2() << std::endl;
            }else{
                nextInChain->calculate(request);
            }
        }
};

class MultNumbers : public Chain {
    private:
        Chain *nextInChain;
    public:
        void setNextChain(Chain *nextChain){
            nextInChain = nextChain;
        }
        void calculate(Numbers request){
            if(request.getCalcWanted() == "Mult"){
                std::cout << request.getNum1() << " * " << request.getNum2() << " = " << request.getNum1() * request.getNum2() << std::endl;
            }else{
                nextInChain->calculate(request);
            }
        }
};

class DivideNumbers : public Chain {
    private:
        Chain *nextInChain;
    public:
        void setNextChain(Chain *nextChain){
            nextInChain = nextChain;
        }
        void calculate(Numbers request){
            if(request.getCalcWanted() == "Div"){
                std::cout << request.getNum1() << " / " << request.getNum2() << " = " << request.getNum1() / request.getNum2() << std::endl;
            }else{
                std::cout << "Only works for Add, Sub, Mult and Div" << std::endl;
            }
        }
};

int main(){
    Chain *calc1 = new AddNumbers;
    Chain *calc2 = new SubtractNumbers;
    Chain *calc3 = new MultNumbers;
    Chain *calc4 = new DivideNumbers;

    calc1->setNextChain(calc2);
    calc2->setNextChain(calc3);
    calc3->setNextChain(calc4);

    Numbers request = Numbers(4,2,"Sub");
    calc1->calculate(request); 

    return 0;
}