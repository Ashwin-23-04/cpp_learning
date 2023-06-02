#include<iostream>

class Color{
    public:
        virtual void fillColor(){}
};

class RedColor : public Color{
    public:
        void fillColor(){
            std::cout << "Red Color" << std::endl;
        }
};

class BlueColor : public Color{
    public:
        void fillColor(){
            std::cout << "Blue Color" << std::endl;
        }
};

class GreenColor : public Color{
    public:
        void fillColor(){
            std::cout << "Green Color" << std::endl;
        }
};

class Shape{
    private:
        Color *color;
    public:
        Shape(Color *color){
            this->color = color;
        }
        virtual void draw(){
            color->fillColor();
        }
};

class Circle : public Shape{
    public:
        Circle(Color *color) : Shape(color){}
        void draw(){
            std::cout << "Circle is drawn with ";
            Shape::draw();
        }
};

class Rectangle : public Shape{
    public:
        Rectangle(Color *color) : Shape(color){}
        void draw(){
            std::cout << "Rectangle is drawn with ";
            Shape::draw();
        }
};

int main(){
    Shape *redCircle = new Circle(new RedColor);
    redCircle->draw();
    Shape *greenRectangle = new Rectangle(new GreenColor);
    greenRectangle->draw();
    Shape *blueCircle = new Circle(new BlueColor);
    blueCircle->draw();
    return 0;
}