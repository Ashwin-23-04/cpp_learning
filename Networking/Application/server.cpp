#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>

std::timed_mutex m;
char buffer[1024] = {0} ;

void handleClient(int clientSocket, std::vector<int>& clientSockets) {
    while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        std::unique_lock<std::timed_mutex> lock(m, std::chrono::seconds(5));
        for (int i = 0; i < clientSockets.size(); ++i) {
            if (clientSockets[i] != clientSocket) {
                send(clientSockets[i], buffer, strlen(buffer), 0);
            }
        }
        memset(buffer, 0, sizeof(buffer)); 
    }
    auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
    if (it != clientSockets.end()) {
        clientSockets.erase(it);
    }
    close(clientSocket);
}


int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        std::cout << "[-] Error on binding"<< std::endl;
    }else{
        std::cout << "[+] Binded " << std::endl;
    }
    std::cout << "[+] Listening " << std::endl;
    listen(serverSocket, 3); 
    std::vector<int> clientSockets;
    while (true){
        int clientSocket;
        struct sockaddr_in clientAddress;
        socklen_t addrlen = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &addrlen);
        if (clientSocket < 0){
            std::cout << "[-] Error on accept" << std::endl;
        }else{
            std::cout << "[+] Accepted " << std::endl;
            clientSockets.push_back(clientSocket);
        }
        const char *welcomeMsg = "What is your name?";
        send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

        char nameOfClient[1024] = {0};
        read(clientSocket, nameOfClient, 1024);

        std::cout << "[+] Client Named: " << nameOfClient << " joined" << std::endl;
        std::thread t1(handleClient, clientSocket, std::ref(clientSockets));
        t1.detach();
    }
    close(serverSocket);
    return 0;
}