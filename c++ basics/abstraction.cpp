#include<iostream>

class Shape {
public:
    virtual double calculateArea() = 0;
};

class Circle : public Shape {
public:
    Circle(double r){
        radius = r;
    }
    double calculateArea() override { 
        return 3.14 * radius * radius; 
    }
private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double calculateArea() override { 
        return width * height; 
    }
private:
    double width;
    double height;
};


int main() {
    Shape* shapes[2];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(3, 4);

    for (int i = 0; i < 2; i++) {
        std::cout << "Area of shape " << i << " is " << shapes[i]->calculateArea() << std::endl;
        delete shapes[i];
    }

    return 0;
}
