#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>


struct Data{
    int clientSocket;
    std::string name;

    Data(int cS, std::string cName) : clientSocket(cS), name(cName) {}
};

// std::condition_variable cv;
std::timed_mutex m;
char buffer[1024] = {0} ;
std::vector<Data> clientSockets;



// void receiveMsg(int clientSocket, std::vector<int> &clientSockets){
//     while (true){
//         std::unique_lock<std::timed_mutex> lock(m, std::chrono::seconds(3));
//         memset(buffer, 0, sizeof(buffer));
//         int bytesRead = read(clientSocket, buffer, sizeof(buffer));
//         if (strlen(buffer) != 0){
//             // std::cout << buffer << std::endl;
//             for (int i = 0; i < clientSockets.size(); ++i) {
//                 if (clientSockets[i] != clientSocket) {
//                     send(clientSockets[i], buffer, bytesRead, 0);
//                 }
//             }
//             memset(buffer, 0, sizeof(buffer));
//         }
//     }
// }
    
void handleClient(int clientSocket) {
    while ((recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        std::unique_lock<std::timed_mutex> lock(m, std::chrono::seconds(5));
        for (int i = 0; i < clientSockets.size(); ++i) {
            if (clientSockets[i].clientSocket != clientSocket) {
                const char* strToAddFirst = "   [<] ";
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


int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8082);

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
        if (clientSocket < 0){
            std::cout << "[-] Error on accept" << std::endl;
        }else{
            std::cout << "[+] Accepted " << std::endl;
        }
        const char *welcomeMsg = "What is your name? -> ";
        send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

        char nameOfClient[1024] = {0};
        read(clientSocket, nameOfClient, 1024);

        std::cout << "[+] Client Named: " << nameOfClient << " joined" << std::endl;
        clientSockets.push_back(Data(clientSocket, nameOfClient));
        std::thread t1(handleClient, clientSocket);
        t1.detach();
    }
    close(serverSocket);
    return 0;
}