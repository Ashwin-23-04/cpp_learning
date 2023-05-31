// The factory design pattern is used when we have a superclass with multiple sub-classes 
// and based on input, we need to return one of the sub-class.

#include<iostream>

class Shape{
    public:
        virtual std::string getName() = 0; 
};

class Triangle : public Shape {
    public:
    std::string getName(){
        return "Triangle";
    }
};

class Rectangle : public Shape {
    public:
    std::string getName(){
        return "Rectangle";
    }
};

class Circle : public Shape {
    public:
    std::string getName(){
        return "Circle";
    }
};

enum Shapes {
    TRIANGLE, RECTANGLE, CIRCLE
};

class Factory {
    public:
    Shape* create(Shapes s){
        switch (s)
        {
        case TRIANGLE:
            return new Triangle();
        case RECTANGLE:
            return new Rectangle();
        case CIRCLE:
            return new Circle();
        }
    }
};

int main(){
    Factory factory;
    Shape* shape = factory.create(CIRCLE);
    std::cout << shape->getName() << std::endl; 
    return 0;
}