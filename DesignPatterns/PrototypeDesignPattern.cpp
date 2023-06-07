#include <iostream>
#include<memory>

class Car{
    protected:
        std::string model;
        std::string color;
    public:
        Car(std::string model, std::string color){
            this->model = model;
            this->color = color;
        }
        virtual void setColor(std::string color) = 0;
        virtual std::string getColor() = 0;
        virtual std::unique_ptr<Car> clone() = 0;
        virtual ~Car(){}
};

class RaceCar : public Car{
    private:
        std::string speed;
    public:
        RaceCar(std::string model, std::string color, std::string speed) : Car(model, color){
            this->speed = speed;
        }
        void setColor(std::string color){
            this->color = color;
        } 
        std::string getColor(){
            return this->color;
        }
        std::unique_ptr<Car> clone(){
            return std::make_unique<RaceCar>(*this);
        }
};

int main(){
    auto raceCarPrototype = std::make_unique<RaceCar>("Model","color","250 mph");

    auto car1 = raceCarPrototype->clone();
    car1->setColor("RED");

    std::cout << "Race car 1 has color : " << car1->getColor() << std::endl;
    return 0;
}