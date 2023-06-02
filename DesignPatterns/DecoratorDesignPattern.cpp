#include<iostream>

class Shape{
    public:
        virtual void draw(){}
};

class Circle : public Shape{
    public:
        void draw(){
            std::cout << "drawing circle" << std::endl;
        }
};

class Square : public Shape{
    public:
        void draw(){
            std::cout << "drawing square" << std::endl;
        }
};

class ShapeDecorator : public Shape{
    private :
        Shape *shapeToDecorate;
    public:
        ShapeDecorator(Shape *shapeToDecorate){
            this->shapeToDecorate = shapeToDecorate;
        }
        virtual void draw(){
            shapeToDecorate->draw();
        }
};

class BlueBorderShapeDecorator : public ShapeDecorator{
    private:
        void addBlueBorder(){
            std::cout << "Blue border Added" << std::endl;
        }
    public:
        BlueBorderShapeDecorator(Shape *shapeToDecorate) : ShapeDecorator(shapeToDecorate) {
            
        } 
        void draw(){
            ShapeDecorator::draw();
            addBlueBorder();
        }
};

int main(){
    Shape *circle = new Circle;
    BlueBorderShapeDecorator *blueCircle = new BlueBorderShapeDecorator(circle);
    BlueBorderShapeDecorator *blueSquare = new BlueBorderShapeDecorator(new Square);
    circle->draw();
    blueCircle->draw();
    blueSquare->draw();
    return 0;
}