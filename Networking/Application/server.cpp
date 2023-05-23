#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

#define PORT 8081

struct Data{
    int id;
    int clientSocket;
    std::string name;
    bool waiting = false;
    Data(int idNumber,int cS, std::string cName) : id(idNumber), clientSocket(cS), name(cName) {}
};

std::vector<Data> clientSockets;
unsigned int id = 0;

void serverStartMsg(int clientSocket);
void connectToClient(int clientSocket, int connectWithSocket);
void waitingForClient(int clientSocket);
void handleCommunication(int client1, int client2);

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
    int clientSocket;
    struct sockaddr_in clientAddress;
    socklen_t clientAddrlen = sizeof(clientAddress);
    while (true){
        try {
            clientSocket = accept(s, (struct sockaddr *) &clientAddress, &clientAddrlen);

            if(clientSocket <= 0){
                std::cout << "[-] Error on accepting client" << std::endl;
            }else{
                std::cout << "[+] Client Accepted " << std::endl;
                std::thread startThread(serverStartMsg, clientSocket);
                startThread.detach();
            }
        }catch(...){
            continue;
        }
    }
    close(s);
    return 0;
}

void serverStartMsg(int clientSocket){
    std::string qName = "What is your name?";
    char name[1024] = {0};
    send(clientSocket, &qName, qName.length(), 0);
    read(clientSocket, name, 1024);
    id += 1;
    std::string idOfClient = "Your id is " + std::to_string(id);
    send(clientSocket, &idOfClient, idOfClient.length(), 0);
    int userId = id;
    clientSockets.push_back(Data(userId, clientSocket, name));
    std::cout << "[+] Client Named: " << name << " joined the server!" << std::endl;
    while(true){
        const char *displayOptions = "\n1. Connect with user\n2.Wait to Connect\n3.Exit";
        const char *displayConnectUserOption = "\nEnter user ID to connect ";
        const char *invalidOption = "Invalid";
        bool invalid;
        std::string userIdToConnect = "";
        send(clientSocket, displayOptions, strlen(displayOptions), 0);
        std::string selectedOption = "";
        read(clientSocket, &selectedOption, 1024);

        if(std::stoi(selectedOption) == 1){
            std::cout << clientSocket << " has selected option 1" << std::endl;
            send(clientSocket, displayConnectUserOption, strlen(displayConnectUserOption), 0);
            read(clientSocket, &userIdToConnect, 1024);

            if(std::stoi(userIdToConnect) <= id && std::stoi(userIdToConnect) !=0){          
                for(int i=0; i < clientSockets.size(); i++){
                    if(clientSockets[i].id == std::stoi(userIdToConnect) && clientSockets[i].waiting == true){
                        invalid = false;
                        std::cout << "user ID" << std::to_string(userId) << std::endl;
                        std::string goingToConnectUserID = std::to_string(userId);
                        send(clientSockets[i].clientSocket, &goingToConnectUserID, goingToConnectUserID.length(), 0);
                        std::thread connectThread(connectToClient, clientSocket, clientSockets[i].clientSocket);
                        connectThread.join();
                        break;
                    }else{
                        invalid = true;
                    }
                }
            }else{
                invalid = true;
            }
            if(invalid){
                send(clientSocket, invalidOption, strlen(invalidOption), 1024);
            }
            selectedOption = "";
        }else if(std::stoi(selectedOption) == 2){
            std::cout << clientSocket << " has selected option 2" << std::endl;
            std::thread waitThread(waitingForClient, clientSocket);
            waitThread.join();
            selectedOption = "";
            break;
        }else if(std::stoi(selectedOption) == 3){
            std::cout << clientSocket << " has selected option 3" << std::endl;
            selectedOption = "";
            const char *msg = "Quit";
            send(clientSocket, msg, strlen(msg), 0);
            break;
        }else{
            std::cout << clientSocket << " has selected Invalid Option" << std::endl;
        }
    }
    close(clientSocket);
}

void connectToClient(int clientSocket, int connectWithSocket){
    const char *displayOptions = "\n1. Accept\n2.Reject\n";
    send(connectWithSocket, displayOptions, strlen(displayOptions), 0);
    std::string selectedOption;
    read(connectWithSocket, &selectedOption, 1024);
    if(std::stoi(selectedOption) == 1){
        const char *msg = "Accepted";
        send(clientSocket, msg, strlen(msg), 0);
        for(int i=0; i < clientSockets.size(); i++){
        if(clientSockets[i].clientSocket == connectWithSocket){
            clientSockets[i].waiting = false;
        }
    }
        // std::thread communicationThread(handleCommunication, clientSocket, connectWithSocket);
        // communicationThread.detach();
        handleCommunication(clientSocket, connectWithSocket);
    }else{
        const char *msg = "Rejected";
        send(clientSocket, msg, strlen(msg), 0);
        send(connectWithSocket, msg, strlen(msg), 0);
    }
}

void waitingForClient(int clientSocket){
    const char *waitingMsg = "waiting...";
    for(int i=0; i < clientSockets.size(); i++){
        if(clientSockets[i].clientSocket == clientSocket){
            clientSockets[i].waiting = true;
        }
    }
    std::string wait;
    std::string connectFromSocket;

    std::cout << waitingMsg  << std::endl;
    read(clientSocket, &connectFromSocket, 1024);
    read(std::stoi(connectFromSocket), &wait, 1024);
    
}

void handleCommunication(int client, int clientToSpeak){
    char buffer[1024] = {0};
    while (true) {
        if (read(client, buffer, sizeof(buffer)) <= 0) {
            break;
        }
        send(clientToSpeak, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        if (read(clientToSpeak, buffer, sizeof(buffer)) <= 0) {
            break;
        }
        send(client, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }
}