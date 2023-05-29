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
    // bool waiting = false;
    Data(std::string idNumber,int cS, std::string cName) : id(idNumber), clientSocket(cS), name(cName) {}
};

std::vector<Data> clientSockets;
unsigned int id = 0;

void startConversation(int clientSocket);
void handleCommunication(int clientSocket, int clientToSpeak, std::string name);

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
    close(s);
}

void startConversation(int clientSocket){
    try{
        const char *qName = "What is your name?";
        char name[50] = {0};
        send(clientSocket, qName, strlen(qName), 0);
        read(clientSocket, name, 1024);
        std::cout << "Client named " << name << " joined!" << std::endl;
        id += 1;
        std::string userID = std::to_string(id);
        send(clientSocket, &userID, userID.length(), 0);
        std::string dummy;
        read(clientSocket, &dummy, sizeof(dummy));
        clientSockets.push_back(Data(userID, clientSocket, name));

        const char *displayOptions = "1. Connect with user 2. Wait to connect 3.Exit";

        send(clientSocket, displayOptions, strlen(displayOptions), 0);
        char selectedOption[10] = {0};
        while(true){
            read(clientSocket, selectedOption, sizeof(selectedOption));
            if((std::stoi(selectedOption) == 1) || (std::stoi(selectedOption) == 2) || (std::stoi(selectedOption) == 3)){
                const char *validReply = "Valid";
                send(clientSocket, validReply, strlen(validReply), 0);
                break;
            }else{
                const char *validReply = "Invalid";
                send(clientSocket, validReply, strlen(validReply), 0);
            }
        }
        std::cout << std::stoi(selectedOption) << std::endl;

        if(std::stoi(selectedOption) == 3){
            clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(),[&](Data const &data){
                return data.clientSocket == clientSocket;
            }),clientSockets.end());
            close(clientSocket);
        }else if(std::stoi(selectedOption) == 1){
            while(true){
                int clientToSpeak;
                bool valid = false;
                const char *toConnectOption = "Enter userID to connect";
                char selectedUserID[1024] = {0};
                send(clientSocket, toConnectOption, strlen(toConnectOption), 0);
                while(true){
                    read(clientSocket, selectedUserID, sizeof(selectedUserID));
                    std::cout << "User ID: " << selectedUserID << std::endl;
                    for(Data data: clientSockets){
                        if(data.id == selectedUserID && selectedUserID != userID){
                            valid = true;
                            clientToSpeak = data.clientSocket;
                            break;
                        }else{
                            valid = false;
                        }
                    }
                    if(valid){
                        const char *validReply = "Valid";
                        send(clientSocket, validReply, strlen(validReply), 0);
                        break;
                    }else{
                        const char *validReply = "Invalid";
                        send(clientSocket, validReply, strlen(validReply), 0);
                    }
                }
                handleCommunication(clientSocket, clientToSpeak, name);
            }
        }
    }catch(...){
        clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(),[&](Data const &data){
            return data.clientSocket == clientSocket;
        }),clientSockets.end());
        close(clientSocket);
    }
}

void handleCommunication(int clientSocket, int clientToSpeak, std::string name){
    std::cout << "Client socket :" << clientSocket << "\tClient to speak : " << clientToSpeak << std::endl;
    std::string display = "1. Accept 2.Reject from " + name;
    const char *displayOptions = display.c_str();

    char selectedOption[10] = {0};
    send(clientToSpeak, displayOptions, display.size(), 0);
    read(clientToSpeak, selectedOption, sizeof(selectedOption));
    std::cout << std::stoi(selectedOption) << std::endl;
    send(clientSocket, selectedOption, strlen(selectedOption), 0);
    if(std::stoi(selectedOption) == 1){
        char buffer[1024] = {0};
        while (true) {
            if (read(clientSocket, buffer, sizeof(buffer)) <= 0) {
                break;
            }
            send(clientToSpeak, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
            if (read(clientToSpeak, buffer, sizeof(buffer)) <= 0) {
                break;
            }
            send(clientSocket, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
        }
    }

}