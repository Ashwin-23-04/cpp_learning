#include<iostream>

class Animal;
class Shape;

class Visitor{
    public:
        virtual void visit(Animal *animal) = 0;
        virtual void visit(Shape *shape) = 0;
};

class Element{
    public:
        virtual void accept(Visitor *visitor) = 0;
};

class Animal : public Element{
    public:
        void accept(Visitor *visitor){
            visitor->visit(this);
        }
};

class Shape : public Element{
    public:
        void accept(Visitor *visitor){
            visitor->visit(this);
        }
};

class ElementVisitor: public Visitor{
    public:
        void visit(Animal *animal){
            std::cout << "Animal" << std::endl;
        } 
        void visit(Shape *shape){
            std::cout << "Shape" << std::endl;
        } 
};

int main(){
    Element *element = new Animal();
    Visitor *eVisitor = new ElementVisitor();
    element->accept(eVisitor);
    return 0;
}