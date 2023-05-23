#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

#define PORT 8081

struct Data{
    std::string id;
    int clientSocket;
    std::string name;
    bool waiting = false;
    Data(std::string idNumber,int cS, std::string cName) : id(idNumber), clientSocket(cS), name(cName) {}
};

std::vector<Data> clientSockets;
unsigned int id = 0;

void startConversation(int clientSocket);

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if(bind(s, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        std::cout << "[-] Error on binding"<< std::endl;
    }else {
        std::cout << "[+] Binded Successfully"<< std::endl;
    }
    std::cout << "[+] Listening..."<< std::endl;
    listen(s, 3);
    while (true){
        int clientSocket;
        struct sockaddr_in clientAddress;
        socklen_t clientAddrlen = sizeof(clientAddress);
        clientSocket = accept(s, (struct sockaddr *)&clientSocket, &clientAddrlen);
        if(clientSocket < 0 ){
            std::cout << "[-] Error on accepting client" << std::endl;
        }else{
            std::cout << "[+] Client Accepted " << std::endl;
            std::thread startConv(startConversation, clientSocket);
            startConv.detach();
        }
    }
}

void startConversation(int clientSocket){
    const char *qName = "What is your name?";
    char name[50] = {0};
    send(clientSocket, qName, strlen(qName), 0);
    read(clientSocket, name, 1024);
    std::cout << "Client named " << name << " joined!" << std::endl;
    id += 1;
    std::string userID = std::to_string(id);
    send(clientSocket, &userID, userID.length(), 0);
    clientSockets.push_back(Data(userID, clientSocket, name));

    const char *displayOptions = "1. Connect with user\t2.Exit";
    char selectedOption[10] = {0};
    send(clientSocket, displayOptions, strlen(displayOptions), 0);
    read(clientSocket, selectedOption, 10);
    std::cout << std::stoi(selectedOption) << std::endl;

    if(std::stoi(selectedOption) == 1){
        bool valid = false;
        const char *toConnectOption = "Enter userID to connect";
        char selectedUserID[1024] = {0};
        send(clientSocket, toConnectOption, strlen(toConnectOption), 0);
        read(clientSocket, selectedUserID, 1024);
        std::cout << "User ID: " << selectedUserID << std::endl;
        for(Data data: clientSockets){
            if(std::stoi(data.id) == std::stoi(selectedUserID)){
                valid = true;
                std::cout << "Data" << data.id << std::endl;
                break;
            }else{
                valid = false;
            }
        }
        if(valid){
            char *validReply = "Valid";
            send(clientSocket, validReply, strlen(validReply), 0);
        }else{
            char *validReply = "Invalid";
            send(clientSocket, validReply, strlen(validReply), 0);
        }
    }else if(std::stoi(selectedOption) == 2){
        close(clientSocket);
    }

}