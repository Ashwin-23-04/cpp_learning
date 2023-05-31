#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

#define PORT 8081

void startingConversation(int soc);

std::string receiveMsg(int soc){
    char *buffer = nullptr;
    size_t dataLength;
    std::string receivedString;
    recv(soc, &dataLength, sizeof(size_t), 0);
    dataLength = ntohl(dataLength);
    buffer = new char[ dataLength ];

    recv(soc,&(buffer[0]),dataLength,0);
    receivedString.assign(buffer,dataLength);
    
    return receivedString;
}

void availableUsers(int soc){
    while(true){
        std::string availableClients = receiveMsg(soc);
        if(availableClients.compare("NO USER AVAILABLE [Auto Refresh in 5s]") == 0){
            std::cout << availableClients << std::endl;
            continue;
        }else{
            std::cout << availableClients << std::endl;
            break;
        }
    }
}

void sendMsg(int soc, std::string name){
    while(true){
        std::string input;
        std::getline(std::cin >> std::ws, input);
        if(input == "0" ){}
        else if(input == "q" || input == "Q"){}
        else{
            input += " [" + name + "]";
        }
        size_t dataLength;
        dataLength = htonl(input.size());
        send(soc, &dataLength, sizeof(size_t), 0);
        send(soc, input.c_str(), input.size(), 0);
        if(input == "q" || input == "Q"){break;}
    }

    // if(input.compare("0 [" + name + "]") == 0){
    //     std::string availableClients = receiveMsg(soc);
    //     std::cout << availableClients << std::endl;
    // }
    
}

void receiveThread(int soc){
    while(true){
        char *buffer = nullptr;
        size_t dataLength;
        std::string receivedString;
        recv(soc, &dataLength, sizeof(size_t), 0);
        dataLength = ntohl(dataLength);
        buffer = new char[ dataLength ];

        recv(soc,&(buffer[0]),dataLength,0);
        receivedString.assign(buffer,dataLength);

        std::cout << receivedString << std::endl;
        buffer = nullptr;
    }
}

int main(){
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(soc, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    startingConversation(soc);
    close(soc);
    return 0;
}



void startingConversation(int soc){
    try{
        std::string qName = receiveMsg(soc);
        std::cout << "[SERVER] " << qName << "\n>";
        std::string name;
        std::getline(std::cin >> std::ws, name);
        size_t dataLength;
        dataLength = htonl(name.size());
        send(soc, &dataLength, sizeof(size_t), 0);
        send(soc, name.c_str(), name.size(), 0);
        availableUsers(soc);
        std::string info = receiveMsg(soc);
        std::cout << info << std::endl ;
        std::thread t2(receiveThread, soc);
        t2.detach();
        std::thread t1(sendMsg, soc, name);
        t1.join();   
    }catch(...){
        close(soc);
    }
}