#include<iostream>

class Circle;
class Rectangle;

class Visitor{
    public:
        virtual void visit(Rectangle *rectangle) = 0;
        virtual void visit(Circle *circle) = 0;
};

class Shape{
    public:
        virtual void accept(Visitor *visitor) = 0;
};

class Rectangle : public Shape{
    private:
        double width;
        double height;
        
    public:
        Rectangle(double width, double height){
            this->width = width;
            this->height = height;
        }
        void accept(Visitor *visitor){
            visitor->visit(this);
        }
        double getWidth(){
            return width;
        }
        double getHeight(){
            return height;
        }
};

class Circle : public Shape{
    private:
        double radius;
    public:
        Circle(double radius){
            this->radius = radius;
        }
        void accept(Visitor *visitor){
            visitor->visit(this);
        }
        double getRadius(){
            return radius;
        }
};

class ShapeVisitor: public Visitor{
    public:
        void visit(Rectangle *rectangle){
            std::cout << "Area of Rectangle is " << rectangle->getWidth() * rectangle->getHeight()  << std::endl;
        } 
        void visit(Circle *circle){
            std::cout << "Area of Circle is " << 3.1415 * circle->getRadius() * circle->getRadius()  << std::endl;
        } 
};

int main(){
    // Shape *shape = new Rectangle(2,3);
    Shape *shape = new Circle(2);
    Visitor *eVisitor = new ShapeVisitor();
    shape->accept(eVisitor);
    return 0;
}