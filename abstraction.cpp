#include<iostream>

class Shape{
    public:
    virtual void draw() = 0;
};

class Triangle : public Shape{
    public:
    void draw(){
        std::cout << "Drawing triangle.." << std::endl;
    }
};

class Circle : public Shape{
    public :
    void draw(){
        std::cout << "Drawing circle.." << std::endl;
    }
};

int main() {
    Shape *pS;

    Triangle t;
    Circle c;

    t.draw();
    c.draw();

    pS = &c;
    pS -> draw();

    return 0;
}