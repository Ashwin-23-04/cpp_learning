#include <iostream>
#include <thread>
#include <future>

void sensorFuc(std::promise<bool>& sensorValue) {
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
    
    sensorValue.set_value(dataReceived);
}

int main() {
    std::promise<bool> sensorValue;
    std::future<bool> futureSensorValue = sensorValue.get_future();
    std::thread t1(sensorFuc, std::ref(sensorValue));
    bool dataReceived = futureSensorValue.get();
    std::cout << "Sensor data received: " << dataReceived << std::endl;
    t1.join();

    return 0;
}
