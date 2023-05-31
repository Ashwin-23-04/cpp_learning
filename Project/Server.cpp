#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
#include <sstream>

#define PORT 8081

struct Data{
    std::string id;
    int clientSocket;
    std::string name;
    Data(std::string idNumber,int cS, std::string cName) : id(idNumber), clientSocket(cS), name(cName) {}
};

std::vector<Data> clientSockets;
unsigned int id = 0;

void startConversation(int clientSocket);
std::string receiveMsg(int clientSocket);
void sendMsg(int clientSocket, std::string receivedString);
std::string getAvailableUser(std::string userID);
bool checkAvailableClients(std::string userID, std::string id);
std::vector<std::string> split(const std::string &str);
void handleClient(int clientSocket, std::string userID);


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
        std::string qName = "What is your name?";
        sendMsg(clientSocket, qName);
        std::string name = receiveMsg(clientSocket);
        std::cout << "Client named " << name << " joined!" << std::endl;
        id += 1;
        std::string userID = std::to_string(id);
        clientSockets.push_back(Data(userID, clientSocket, name));
        std::string availableClients = getAvailableUser(userID);
        sendMsg(clientSocket, availableClients);
        std::string info = "\nEnter either of this format \n\n(a) Id number ~ message \n(b) Id num1, Id num2 ,... ~ message \n(c) 0 to show available user \n(d) q to quit\n";
        sendMsg(clientSocket, info);
        std::thread t1(handleClient, clientSocket, userID);
        t1.join();
        

    }catch(...){
        clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(),[&](Data const &data){
            return data.clientSocket == clientSocket;
        }),clientSockets.end());
        close(clientSocket);
    }
    clientSockets.erase(std::remove_if(clientSockets.begin(), clientSockets.end(),[&](Data const &data){
        return data.clientSocket == clientSocket;
    }),clientSockets.end());
    close(clientSocket);
}

std::vector<std::string> split(const std::string &str, char sep){
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);
    std::string sep2 = "";
    sep2 = sep;
    while (std::getline(ss, token, sep)) {
        if (!token.empty()) {
            if(token.compare(sep2) != 0){
                tokens.push_back(token);
            }
        }
    }
    return tokens;
}

void handleClient(int clientSocket, std::string userID) {
    while(true){
        std::string msg = receiveMsg(clientSocket);
        std::vector<std::string> tokens = split(msg, '~');
        // for(auto i: tokens){
        //     std::cout << i << std::endl;
        // }
        if(tokens.front() == "0"){
            std::string availableClients = getAvailableUser(userID);
            sendMsg(clientSocket, availableClients);
        }else if(tokens.front() == "q" || tokens.front() == "Q"){
            std::string exitMsg = "Exiting...";
            sendMsg(clientSocket, exitMsg);
            break;
        }else{  

            std::vector<std::string> clientsToSend = split(tokens.front(), ',');
            for(auto i: clientsToSend){
                bool available = false;
                available = checkAvailableClients(userID,i);
                if(available){
                    for(Data data: clientSockets){
                        if(data.id == i){
                            sendMsg(data.clientSocket, tokens.back());
                        }
                    }
                }
            }
        }

    }
    clientSockets.erase(
    std::remove_if(clientSockets.begin(), clientSockets.end(), [&](Data const & data) {
        return data.clientSocket == clientSocket;
    }),
    clientSockets.end());
    close(clientSocket);   
}

std::string receiveMsg(int clientSocket){
    char *buffer = nullptr;
    size_t dataLength;
    recv(clientSocket, &dataLength, sizeof(size_t), 0);
    dataLength = ntohl(dataLength);
    buffer = new char[ dataLength ];

    recv(clientSocket,&(buffer[0]),dataLength,0);
    std::string receivedString;
    receivedString.assign(buffer,dataLength);
    return receivedString;
}

void sendMsg(int clientSocket, std::string receivedString){
    size_t dataLength;
    dataLength = htonl(receivedString.size());
    send(clientSocket, &dataLength, sizeof(size_t), 0);
    send(clientSocket, receivedString.c_str(), receivedString.size(), 0);
}

std::string getAvailableUser(std::string userID){
    std::string availableClients;
    bool notAvailable = true;
    for(Data data:clientSockets){
        if(data.id != userID){
            std::string formatedString = "\nId: " + data.id + " Name: " + data.name;
            availableClients.append(formatedString);
            notAvailable = false;
        }
    }
    if(notAvailable){
        return "NO USER AVAILABLE";
    }
    return availableClients;
}
   

bool checkAvailableClients(std::string userID, std::string id){
    bool available = false;
    for(Data data:clientSockets){
        if(data.id != userID && data.id == id){
            available = true;
        }
    }
    return available;
}