#include <iostream>
#include <thread>
#include <future>

bool sensorFuc() {
    std::cout << "sensor thread" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string str;
    bool dataReceived = false;
    std::cout << "Enter anything : ";
    std::getline(std::cin , str);
    if (!str.empty()){
        dataReceived = true;
    }else{
        dataReceived = false;
    }
    
    return dataReceived;
}

int main() {
    std::cout << "Main thread" << std::this_thread::get_id() << std::endl;
    std::future<bool> futureSensorValue = std::async(std::launch::async, sensorFuc);
    // std::future<bool> futureSensorValue = std::async(std::launch::deferred, sensorFuc);
    bool dataReceived = futureSensorValue.get();
    std::cout << "Sensor data received: " << dataReceived << std::endl;

    return 0;
}
