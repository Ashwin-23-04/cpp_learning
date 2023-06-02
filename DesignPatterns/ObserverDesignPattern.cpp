#include<iostream>

class Observer{
    public:
        virtual void update(float temperature, float pressure, float humidity) = 0;
};

class Object{
    public:
        virtual void registerObserver(Observer *observer) = 0;
        virtual void removeObserver(Observer *observer) = 0;
        virtual void notifyObservers() = 0;
};

class WeatherData : Object {
    private:
        std::vector<Observer *> observers;
        float temperature = 0.0f;
        float pressure = 0.0f;
        float humidity = 0.0f;
    public:
        void registerObserver(Observer *observer){
            observers.push_back(observer);
        }
        void removeObserver(Observer *observer){
            auto iterator = std::find(observers.begin(), observers.end(), observer);
            if(iterator != observers.end()){
                observers.erase(iterator);
            }
        }
        void notifyObservers(){
            for(Observer* observer : observers){
                observer->update(temperature, pressure, humidity);
            }
        }
        void setState(float temperature, float pressure, float humidity){
            this->temperature = temperature;
            this->pressure = pressure;
            this->humidity = humidity;
            notifyObservers();
        }
};

class Client : public Observer{
    private:
        std::string name;
    public:
        Client(std::string name){
            this->name = name;
        }
        void update(float temperature, float pressure , float humidity){
            std::cout << "Name : " << name << "\tTemperature : " << temperature << "\tPressure : " << pressure << "\tHumidity : " << humidity << std::endl;
        }
};


int main(){
    WeatherData weatherdata;
    Client c1("Ashwin");
    Client c2("Max");
    Client c3("Jacky");
    weatherdata.registerObserver(&c1);
    weatherdata.registerObserver(&c2);
    weatherdata.registerObserver(&c3);

    weatherdata.setState(45, 3.9, 12);

    weatherdata.removeObserver(&c1);

    weatherdata.setState(46,4,15);

    return 0;
}