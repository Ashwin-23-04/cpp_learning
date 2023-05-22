#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

# define PORT 8085

void sendMsg(int clientSocket){
    // while(true){
        std::cout << ">" ;
        std::string msg ;
        std::getline(std::cin >> std::ws, msg);

        const char *message = (char *)&msg;
        send(clientSocket, message, strlen(message), 0);
    // }
}

int main(){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    while (true){
        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);

        std::cout << buffer << std::endl;
        std::thread t1(sendMsg, clientSocket);
        t1.detach();

    }
    close(clientSocket);

    return 0;
}