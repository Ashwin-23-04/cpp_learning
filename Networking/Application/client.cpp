#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

#define PORT 8081

void sendMsg(int s);

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(s, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    while(true){
        try {
            char messageFromServer[1024] = {0} ;
            read(s, messageFromServer, 1024);
            std::cout << messageFromServer << std::endl;
            std::thread t1(sendMsg, s);
            t1.detach();
        }catch(...){
            std::cout << "Exiting.." << std::endl;
            break;
        }
    }
    close(s);
    return 0;
}

void sendMsg(int s){
    std::cout << "> " ;
    std::string msg ;
    std::getline(std::cin >> std::ws, msg);
    const char *message = (char *)&msg;
    send(s, message, strlen(message), 0);
}