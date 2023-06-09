#include <iostream>

class Mouse;
class Keyboard;
class Monitor;

class ComputerPartVisitor {
    public:
        virtual void visit(Mouse* mouse) = 0;
        virtual void visit(Keyboard* keyboard) = 0;
        virtual void visit(Monitor* monitor) = 0;
};

class ComputerPart {
    public:
        virtual void accept(ComputerPartVisitor* computerPartVisitor) = 0;
};

class Mouse : public ComputerPart {
    public:
        void accept(ComputerPartVisitor* computerPartVisitor){
            computerPartVisitor->visit(this);
        }
};

class Keyboard : public ComputerPart {
    public:
        void accept(ComputerPartVisitor* computerPartVisitor){
            computerPartVisitor->visit(this);
        }
};

class Monitor : public ComputerPart {
    public:
        void accept(ComputerPartVisitor* computerPartVisitor){
            computerPartVisitor->visit(this);
        }
};

class Computer : public ComputerPart {
    private:
        std::vector<ComputerPart*> parts;
    public:
        Computer() {
            parts.push_back(new Mouse());
            parts.push_back(new Keyboard());
            parts.push_back(new Monitor());
        }
        void accept(ComputerPartVisitor* computerPartVisitor){
            for (ComputerPart *part : parts) {
                part->accept(computerPartVisitor);
            }
        }
};

class ComputerPartDisplayVisitor : public ComputerPartVisitor {
    public:
        void visit(Mouse* mouse) {
            std::cout << "Displaying Mouse" << std::endl;
        }

        void visit(Keyboard* keyboard) {
            std::cout << "Displaying Keyboard" << std::endl;
        }

        void visit(Monitor* monitor) {
            std::cout << "Displaying Monitor" << std::endl;
        }
};

int main() {
    ComputerPart* computer = new Computer();
    ComputerPartVisitor* computerPartDisplay = new ComputerPartDisplayVisitor();
    computer->accept(computerPartDisplay);
    return 0;
}