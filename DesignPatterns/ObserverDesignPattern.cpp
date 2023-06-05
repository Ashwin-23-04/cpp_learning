#include<iostream>

class Observer{
    public:
        virtual void update(float temperature, float pressure, float humidity) = 0;
};

class Publisher{
    public:
        virtual void registerObserver(Observer *observer) = 0;
        virtual void removeObserver(Observer *observer) = 0;
        virtual void notifyObservers() = 0;
};

class WeatherData : Publisher {
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

class Subscriber : public Observer{
    private:
        std::string name;
    public:
        Subscriber(std::string name){
            this->name = name;
        }
        void update(float temperature, float pressure , float humidity){
            std::cout << "Name : " << name << "\tTemperature : " << temperature << "\tPressure : " << pressure << "\tHumidity : " << humidity << std::endl;
        }
};


int main(){
    WeatherData weatherdata;
    Subscriber s1("Ashwin");
    Subscriber s2("Max");
    Subscriber s3("Jacky");
    weatherdata.registerObserver(&s1);
    weatherdata.registerObserver(&s2);
    weatherdata.registerObserver(&s3);

    weatherdata.setState(45, 3.9, 12);

    weatherdata.removeObserver(&s1);
    weatherdata.setState(46,4,15);

    return 0;
}