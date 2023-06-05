#include<iostream>

class Game{
    private:
        virtual void initialize() = 0;
        virtual void startPlay() = 0;
        virtual void endPlay() = 0;
    public:
        void play(){
            initialize();
            startPlay();
            endPlay();
        }
};

class Cricket: public Game{
    public:
        void initialize(){
            std::cout << "Cricket match initialized" << std::endl ;
        }
        void startPlay(){
            std::cout << "Cricket match started" << std::endl;
        }
        void endPlay(){
            std::cout << "Cricket match ended" << std::endl;
        }
};

class FootBall: public Game{
    public:
        void initialize(){
            std::cout << "FootBall match initialized" << std::endl ;
        }
        void startPlay(){
            std::cout << "FootBall match started" << std::endl;
        }
        void endPlay(){
            std::cout << "FootBall match ended" << std::endl;
        }
};

int main(){
    Game *cricket = new Cricket();
    cricket->play();
    Game *football = new FootBall();
    football->play();
    return 0;
}