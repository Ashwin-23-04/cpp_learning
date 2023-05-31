#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8081

void startingConversation(int soc);
void handleCommunication(int soc, std::string name);

int main(){
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(soc, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    startingConversation(soc);
    close(soc);
    return 0;
}

void startingConversation(int soc){
    char qName[1024] = {0};
    std::string name;
    read(soc, qName, 1024);
    std::cout << "[server] " << qName << "\n> ";
    memset(qName, 0, sizeof(qName));
    std::getline(std::cin >> std::ws, name);
    send(soc, &name, name.length(), 0);
    char myId[1024] = {0};
    read(soc, myId, sizeof(myId));
    std::cout << "Your ID is " << myId << std::endl;
    std::string dummy = "received id";
    send(soc, &dummy, dummy.length(), 0);
    char displayOptions[1024] = {0};
    read(soc, displayOptions, sizeof(displayOptions));
    std::string selectedOption;
    while(true){
        std::cout << "\n[server] " << displayOptions << "\n> ";
        std::getline(std::cin >> std::ws, selectedOption);
        try{
            if(std::stoi(selectedOption) >= 0){
                send(soc, &selectedOption, selectedOption.length(), 0);
                char validateReply[100] = {0};
                read(soc, validateReply, sizeof(validateReply));
                if(strcmp(validateReply, "Valid") == 0){
                    break;
                }else{
                    std::cout << "[-] Invalid Option" << std::endl;
                }
                memset(validateReply, 0, sizeof(validateReply));
            }
        }catch(...){
            std::cout << "[-] Invalid Option " << std::endl;
        }
    }

    if(std::stoi(selectedOption) == 3){
        std::cout << "Exiting..." << std::endl ;
        // close(soc);
    }else if(std::stoi(selectedOption) == 1){
        while(true){
            char toConnectOption[1024] = {0};
            read(soc, toConnectOption, sizeof(toConnectOption));
            std::string selectOption;
            while(true){
                std::cout << "[server] " << toConnectOption << "\n> ";
                std::getline(std::cin >> std::ws, selectOption);
                send(soc, &selectOption, selectOption.length(), 0);
                char validateReply[100] = {0};
                read(soc, validateReply, sizeof(validateReply));
                // std::string check = "Valid";
                if(strcmp(validateReply, "Valid") == 0){
                    std::cout << "[+] Authentication message send" << std::endl;
                    break;
                }else{
                    std::cout << "There is no such ID" << std::endl;
                }
            }
            memset(toConnectOption, 0, sizeof(toConnectOption));
            std::string auth ;
            read(soc, &auth, sizeof(auth));
            if(std::stoi(auth) == 1){
                std::cout << "[+] Accepted your request." << std::endl;
                char *buffer;
                while (true) {

                    std::cout << "> ";
                    std::string msg;
                    std::getline(std::cin >> std::ws, msg);
                    std::string message = msg + "   [<] " + name;
                    size_t dataLength = htonl(message.size());
                    send(soc, &dataLength, sizeof(size_t), 0);
                    send(soc, message.c_str(), message.size(), 0);

                    recv(soc, &dataLength, sizeof(size_t), 0);
                    dataLength = ntohl(dataLength );
                    buffer = new char[ dataLength ];

                    recv(soc,&(buffer[0]),dataLength,0);
                    std::string receivedString;
                    receivedString.assign(buffer,dataLength);
                    buffer = nullptr;

                    std::cout << receivedString << std::endl;
                    
                }
                break;
            }else if(std::stoi(auth) == 2){
                std::cout << "[-] Rejected your request." << std::endl;
            }
            auth = "";
        }
        

    }else if(std::stoi(selectedOption) == 2){
        handleCommunication(soc, name);
    }

}

void handleCommunication(int soc, std::string name){
    while(true){
        std::cout << "handle communication" << std::endl;
        char displayOptions[1024] = {0};
        std::string selectedOption;
        read(soc, displayOptions, sizeof(displayOptions));
        while(true){
            std::cout << "\n[server] " << displayOptions << "\n> ";
            std::getline(std::cin >> std::ws, selectedOption);
            try{
                if((std::stoi(selectedOption) == 1) || (std::stoi(selectedOption) == 2)){
                    send(soc, &selectedOption, selectedOption.length(), 0);
                    break;
                }
                else{
                        std::cout << "[-] Invalid Option" << std::endl;
                    }
            }catch(...){
                std::cout << "[-] Invalid Option " << std::endl;
            }
        }
        memset(displayOptions, 0, sizeof(displayOptions));
        if(std::stoi(selectedOption) == 1){
            char *buffer;
            while (true) {
                size_t dataLength;
                recv(soc, &dataLength, sizeof(size_t), 0);
                dataLength = ntohl(dataLength );
                buffer = new char[ dataLength ];

                recv(soc,&(buffer[0]),dataLength,0);
                std::string receivedString;
                receivedString.assign(buffer,dataLength);
                buffer = nullptr;

                std::cout << receivedString << std::endl;

                std::cout << "> ";
                std::string msg;
                std::getline(std::cin >> std::ws, msg);
                std::string message = msg + "   [<] " + name;
                dataLength = htonl(message.size());
                send(soc, &dataLength, sizeof(size_t), 0);
                send(soc, message.c_str(), message.size(), 0);

            }
        }
    }
}

