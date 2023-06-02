#include<iostream>

class Shape{
    public:
        virtual void draw(){}
};

class Circle : public Shape{
    public:
        void draw(){
            std::cout << "Drawing Circle" << std::endl;
        }
};

class Rectangle : public Shape{
    public:
        void draw(){
            std::cout << "Drawing Rectangle" << std::endl;
        }
};

class Triangle : public Shape{
    public:
        void draw(){
            std::cout << "Drawing Triangle" << std::endl;
        }
};

class ShapeMaker{
    private:
        Shape *circle;
        Shape *rectangle;
        Shape *triangle;
    public:
        ShapeMaker(){
            circle = new Circle;
            rectangle = new Rectangle;
            triangle = new Triangle;
        }
        void drawCircle(){
            circle->draw();
        }
        void drawRectangle(){
            rectangle->draw();
        }
        void drawTriangle(){
            triangle->draw();
        }
};

int main(){
    ShapeMaker shapeMaker;
    shapeMaker.drawCircle();
    shapeMaker.drawRectangle();
    shapeMaker.drawTriangle();
    return 0;
}