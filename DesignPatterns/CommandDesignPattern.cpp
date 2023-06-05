#include<iostream>
#include<stack>

class Command{
    public:
        virtual void execute(){}
        virtual void unExecute(){}
};

class AddToCart : public Command{
    public:
        void execute(){
            std::cout << "Adding Cart Command executed" << std::endl;
        }
        void unExecute(){
            std::cout << "Adding Cart Command unexecuted" << std::endl;
        }
};

class CreateOrder : public Command{
    public:
        void execute(){
            std::cout << "Creating Order Command executed" << std::endl;
        }
        void unExecute(){
            std::cout << "Creating Order Command unexecuted" << std::endl;
        }
};

class Invoker{
    private :
        Command *cmd;
    public:
        Invoker(Command *cmd){
            this->cmd = cmd;
        }
        void executeCmd(){
            cmd->execute();
        }
        void unExecuteCmd(){
            cmd->unExecute();
        }
};

int main(){
    std::stack<Command*> commandHistory;
    Command *addToCart = new AddToCart();
    Command *createOrder = new CreateOrder();
    Invoker invoker =  Invoker(addToCart);
    invoker.executeCmd();
    invoker =  Invoker(createOrder);
    invoker.executeCmd();
    invoker.unExecuteCmd();
    return 0;
}