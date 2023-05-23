#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8081

void startingConversation(int soc);

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
    char qName[1024] = {0};
    std::string name;
    read(soc, qName, 1024);
    std::cout << "[server] " << qName << "\n> ";
    std::getline(std::cin >> std::ws, name);
    send(soc, &name, name.length(), 0);
    char myId[1024] = {0};
    read(soc, myId, 1024);
    std::cout << "Your ID is " << myId << std::endl;
    char displayOptions[1024] = {0};
    read(soc, displayOptions, 1024);
    std::string selectedOption;
    while(true){
        std::cout << "[server] " << displayOptions << "\n> ";
        std::getline(std::cin >> std::ws, selectedOption);
        try{
            if(std::stoi(selectedOption) == 1 || std::stoi(selectedOption) == 2){
                send(soc, &selectedOption, selectedOption.length(), 0);
                break;
            }else{
                std::cout << "[-] Invalid Option" << std::endl;
            }
        }catch(...){
            std::cout << "[-] Enter 1 or 2 " << std::endl;
        }
    }

    if(std::stoi(selectedOption) == 2){
        std::cout << "Exiting..." << std::endl ;
        // close(soc);
    }
    if(std::stoi(selectedOption) == 1){
        char toConnectOption[1024] = {0};
        read(soc, toConnectOption, 1024);
        std::string selectedOption;
        std::cout << "[server] " << toConnectOption << "\n> ";
        std::getline(std::cin >> std::ws, selectedOption);
        send(soc, &selectedOption, selectedOption.length(), 0);
        char validateReply[100] = {0};
        read(soc, validateReply, 100);
        std::cout << "Reply " << validateReply << std::endl;
    }
    
}