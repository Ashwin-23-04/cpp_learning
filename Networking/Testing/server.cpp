#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>

# define PORT 8085

struct Data{
    int id;
    int clientSocket;
    std::string name;
    Data(int identification,int cS, std::string cName) : id(identification), clientSocket(cS), name(cName) {}
};

// std::condition_variable cv;
std::mutex m;
std::vector<Data> clientSockets;
int id = 0;


void start(int clientSocket);
void connectOptions(int clientSocket, int userID);
void handleAccept(int clientSocket);
void connectClient(int clientSocket, int currentID, int connectWithUserID);
void waitingForClient(int clientSocket, int userID);

void handleClient(int clientSocket); // not in use





int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        std::cout << "[-] Error on binding"<< std::endl;
    }else{
        std::cout << "[+] Binded " << std::endl;
    }
    std::cout << "[+] Listening " << std::endl;
    listen(serverSocket, 3); 
    while (true){
        int clientSocket;
        struct sockaddr_in clientAddress;
        socklen_t addrlen = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &addrlen);
        std::cout << "Client Socket : " << clientSocket << std::endl;
        if (clientSocket < 0){
            std::cout << "[-] Error on accept" << std::endl;
        }else{
            std::cout << "[+] Accepted " << std::endl;
        }
        std::thread t1(start, clientSocket);
        t1.detach();
    }
    close(serverSocket);
    return 0;
}

void start(int clientSocket){
    const char *welcomeMsg = "What is your name? -> ";
        send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

        char nameOfClient[1024] = {0};
        read(clientSocket, nameOfClient, 1024);
        id++;
        std::string appendedMsg = "Your id is " + std::to_string(id);
        send(clientSocket, &appendedMsg, appendedMsg.length(), 0);
        int userID = id;
        clientSockets.push_back(Data(userID, clientSocket, nameOfClient));

        std::cout << "[+] Client Named: " << nameOfClient << " joined" << std::endl;
        while (true){
            const char *optionMsg = "\n1. Connect with user\n2.Wait to Connect";
            send(clientSocket, optionMsg, strlen(optionMsg), 0);
            std::string optionClient;
            read(clientSocket, &optionClient, 1024);
            if ((std::stoi(optionClient) == 1)){
                connectOptions(clientSocket, userID);
            }else if (std::stoi(optionClient) == 2) {
                std::cout << "waiting..." << std::endl;
                std::thread t1(waitingForClient, clientSocket, userID);
                t1.join();
            }else{
                std::cout << "Invalid" << std::stoi(optionClient) << id << std::endl;
            }
        }
}

void connectOptions(int clientSocket, int userID){
    const char *optionMsg = "\nEnter user ID to connect ";
    send(clientSocket, optionMsg, strlen(optionMsg), 0);
    std::string innerOptions;
    read(clientSocket, &innerOptions, 1024);

    if (std::stoi(innerOptions) <= id && std::stoi(innerOptions) > 0){
        std::cout << "correct" << std::endl;
        std::thread t1(connectClient, clientSocket, userID, std::stoi(innerOptions));
        t1.join();
    }else if (std::stoi(innerOptions) == userID){
        std::string msg = "Thats your ID";
        send(clientSocket, &msg , msg.length(), 0);
    }
    else{
        std::cout << "Invalid user id" << std::stoi(innerOptions) << id << std::endl;
    }
}

// void handleAccept(int clientSocket){
//     char buffer[1024] = {0} ;
//     while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
//         send(clientSocket, buffer, strlen(buffer), 0);
//         memset(buffer, 0, sizeof(buffer)); 
//     }
//     close(clientSocket);
// }



// void handleAccept(int clientSocket) {
//     char buffer[1024] = {0};
//     int bytesRead;
    
//     while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
//         std::cout << "Received: " << buffer << std::endl;
//         send(clientSocket, buffer, bytesRead, 0);
//         memset(buffer, 0, sizeof(buffer));
//     }
//     if (bytesRead == 0) {
//         std::cout << "Client disconnected" << std::endl;
//     } else if (bytesRead == -1) {
//         std::cerr << "Error in receiving data" << std::endl;
//     }
//     close(clientSocket);
// }

void handleClient(int clientSocket) {
    char buffer[1024] = {0} ;
    while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        for (int i = 0; i < clientSockets.size(); ++i) {
            if (clientSockets[i].clientSocket != clientSocket) {
                const char* strToAddFirst = "   [<] \n";
                const char* strToAddSecond = clientSockets[i].name.c_str();
                std::strcat(buffer, strToAddFirst);
                std::strcat(buffer, strToAddSecond);
                send(clientSockets[i].clientSocket, buffer, strlen(buffer), 0);
            }
        }
        memset(buffer, 0, sizeof(buffer)); 
    }
    clientSockets.erase(
    std::remove_if(clientSockets.begin(), clientSockets.end(), [&](Data const & data) {
        return data.clientSocket == clientSocket;
    }),
    clientSockets.end());
    close(clientSocket);   
}

void hA(int clientSocket, std::string connectWithUserId){
    char buffer[1024] = {0} ;
    while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        for (int i = 0; i < clientSockets.size(); ++i) {
            if (clientSockets[i].id == std::stoi(connectWithUserId)) {
                const char* strToAddFirst = "   [<] \n";
                const char* strToAddSecond = clientSockets[i].name.c_str();
                std::strcat(buffer, strToAddFirst);
                std::strcat(buffer, strToAddSecond);
                send(clientSockets[i].clientSocket, buffer, strlen(buffer), 0);
            }
        }
        memset(buffer, 0, sizeof(buffer)); 
    }
    clientSockets.erase(
    std::remove_if(clientSockets.begin(), clientSockets.end(), [&](Data const & data) {
        return data.clientSocket == clientSocket;
    }),
    clientSockets.end());
    close(clientSocket);   
}

void handleAccept2(int clientSocket, std::string connectWithUserId){

    // char buffer[1024] = {0} ;
    // std::string msg = "Hello bro from " + std::to_string(clientSocket);
    // send(clientSocket, &msg, msg.length(), 0);
    // recv(clientSocket, buffer, sizeof(buffer), 0);
    // std::cout << buffer << std::endl;
    // close(clientSocket);

    char buffer[1024] = {0} ;
    while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        for (int i = 0; i < clientSockets.size(); ++i) {
            if (clientSockets[i].id == std::stoi(connectWithUserId)) {
                const char* strToAddFirst = "   [<] \n";
                const char* strToAddSecond = clientSockets[i].name.c_str();
                std::strcat(buffer, strToAddFirst);
                std::strcat(buffer, strToAddSecond);
                send(clientSockets[i].clientSocket, buffer, strlen(buffer), 0);
            }
        }
        memset(buffer, 0, sizeof(buffer)); 
    }
    clientSockets.erase(
    std::remove_if(clientSockets.begin(), clientSockets.end(), [&](Data const & data) {
        return data.clientSocket == clientSocket;
    }),
    clientSockets.end());
    close(clientSocket);
}

void connectClient(int clientSocket, int currentID, int connectWithUserID){
    std::string appendedMsg = "\n1. Accept\n2.Reject\n";
    std::string userOption;
    std::string id = std::to_string(currentID);
    std::string msgReceived ;
    for(int i = 0; i < clientSockets.size(); i++){
        if (clientSockets[i].id == connectWithUserID){
            send(clientSockets[i].clientSocket, &appendedMsg, appendedMsg.length(), 0);
            std::cout << "authontication send" << std::endl;  
            read(clientSocket, &msgReceived,1024 );
            send(clientSockets[i].clientSocket, &id, id.length(), 0);
            read(clientSocket, &userOption, 1024);
            if (std::stoi(userOption) == 1){
                // std::thread acceptThread(hA, clientSocket, std::to_string(connectWithUserID));
                // acceptThread.join();
                std::cout << "Accepted from connecting side"<< std::endl ;
            }else if (std::stoi(userOption) == 1){
                std::string rejMsg = "Rejected your request" ; 
                send(clientSocket, &rejMsg, rejMsg.length(), 0);
            }else{
                std::cout << "Invalid" << std::endl;
            }
        }
    }
}

void waitingForClient(int clientSocket, int userID){
    std::string authontication;
    std::string optionClient;
    std::string connectWithUserId;
    std::string msgReceived = "msg received";
    read(clientSocket, &authontication, 1024);
    std::cout << "authontication received" << std::endl; 
    send(clientSocket, &msgReceived, msgReceived.length(), 0 );
    read(clientSocket, &connectWithUserId, 1024);
    if(connectWithUserId.empty()){
        std::cout << "Empty in user id";
    }else{
        std::cout << connectWithUserId << std::endl;
    }
    for (int i = 0; i<clientSockets.size(); i++){
        if(clientSockets[i].id ==  std::stoi(connectWithUserId)){
            read(clientSocket, &optionClient, 1024);
            send(clientSockets[i].clientSocket, &optionClient, optionClient.length(), 0);
        }
    }
    if (std::stoi(optionClient) == 1){
        // read(clientSocket, &connectWithUserId, 1024);
        // std::thread acceptThread(handleAccept2, clientSocket, connectWithUserId);
        // acceptThread.join();
        std::cout << "Accepted from waiting side"<< std::endl ;
    }else{
        connectOptions(clientSocket, userID);
    }
}

/*
- id transfer between above 2 func. [+]
- change handle function for both to handle and store id of each other.
- see difference between send(), recv(), write() , read()
*/