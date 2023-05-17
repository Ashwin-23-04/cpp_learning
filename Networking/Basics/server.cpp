#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
// #include<cstring>

int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //Protocol value for Internet Protocol(IP), which is 0
    
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY - automatically be filled with current host's IP address
    serverAddress.sin_port = htons(8080); // short integer value to network byte order

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
        std::cout << "[-] Error on binding"<< std::endl;
    }else{
        std::cout << "[+] Binded " << std::endl;
    }
    std::cout << "[+] Listening " << std::endl;
    while (true){
        listen(serverSocket, 1); 

        
        int clientSocket;
        struct sockaddr_in clientAddress;
        socklen_t addrlen = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &addrlen);
        if (clientSocket < 0){
            std::cout << "[-] Error on accept" << std::endl;
        }else{
            std::cout << "[+] Accepted " << std::endl;
        }

        const char *message = "Hello , world!";
        send(clientSocket, message, strlen(message), 0);

        char buffer[1024] = {0};
        read(clientSocket, buffer, 1024);

        std::cout << "[+] Client message: " << buffer << std::endl;
    }
    close(serverSocket);
    return 0;
}