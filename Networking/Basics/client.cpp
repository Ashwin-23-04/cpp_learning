#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
// #include<cstring>

int main(){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    while (true){
        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);

        std::cout << "[+] Server message: " << buffer << std::endl;

        const char *message = "Hello, server!";
        send (clientSocket, message, strlen(message), 0);
    }
    close(clientSocket);

    return 0;
}