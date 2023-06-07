#include<iostream>

class User;
class ChatMediator;

class Mediator{
    public:
        virtual void sendMsg(std::string message, User *user){}
        virtual void addUser(User *user){}
};

class User{
    protected:
        Mediator *mediator;
        std::string name;
    public:
        User(Mediator *mediator, std::string name){
            this->mediator = mediator;
            this->name = name;
        }
        virtual void send(std::string message){}
        virtual void receive(std::string message){}
};

class ChatMediator : public Mediator{
    private:
        std::vector<User*> users;
    public:
        void addUser(User *user){
            this->users.push_back(user);
        }
        void sendMsg(std::string message, User *user){
            for (User *u: users){
                if(u != user){
                    u->receive(message);
                }
            }
        }

};

class Client : public User{
    public:
        Client(ChatMediator *mediator, std::string name) : User(mediator, name){}
        void send(std::string message){
            std::cout << "user : " << this->name << " is sending message ..." << std::endl;
            this->mediator->sendMsg(message, this);
        }
        void receive(std::string message){
            std::cout << "user : " << this->name << " is receiving message >" << message << std::endl;
        }
};


int main(){
    ChatMediator *chatMediator = new ChatMediator();
    User *max = new Client(chatMediator, "Max");
    User *ashwin = new Client(chatMediator, "Ashwin");
    User *jacky = new Client(chatMediator, "Jacky");

    chatMediator->addUser(max);
    chatMediator->addUser(ashwin);
    chatMediator->addUser(jacky);

    max->send("hello all");
    return 0;
}