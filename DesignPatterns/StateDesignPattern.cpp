#include<iostream>

class State;
class Context{
    private: 
        State *state;
    public:
        Context(){
            state = nullptr;
        }
        void setState(State *state){
            this->state = state;
        }
        State* getState(){
            return state;
        }
};

class State{
    public:
        virtual void doAction(Context context){}
};

class StartState: public State{
    public:
        void doAction(Context context){
            std::cout << "Player is in Start State" << std::endl;
            context.setState(this);
        }
};

class StopState : public State{
    public:
        void doAction(Context context){
            std::cout << "Player is in Stop State" << std::endl;
            context.setState(this);
        }
};

int main(){
    Context *context = new Context();
    StartState *startState = new StartState();
    startState->doAction(*context);

    StopState *stopState = new StopState();
    stopState->doAction(*context);
    return 0;
}