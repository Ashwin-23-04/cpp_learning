#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8081

void startingConversation(int soc);
void handleCommunication(int soc, std::string name);
// void waiting(int soc);

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
    std::getline(std::cin >> std::ws, name);
    send(soc, &name, name.length(), 0);
    char myId[1024] = {0};
    read(soc, myId, 1024);
    std::cout << "Your ID is " << myId << std::endl;
    std::string dummy = "received id";
    send(soc, &dummy, dummy.length(), 0);
    char displayOptions[1024] = {0};
    read(soc, displayOptions, 1024);
    std::string selectedOption;
    while(true){
        std::cout << "\n[server] " << displayOptions << "\n> ";
        std::getline(std::cin >> std::ws, selectedOption);
        try{
            if(std::stoi(selectedOption) >= 0){
                send(soc, &selectedOption, selectedOption.length(), 0);
                char validateReply[100] = {0};
                read(soc, validateReply, 100);
                if(strcmp(validateReply, "Valid") == 0){
                    break;
                }else{
                    std::cout << "[-] Invalid Option" << std::endl;
                }
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
            read(soc, toConnectOption, 1024);
            std::string selectOption;
            while(true){
                std::cout << "[server] " << toConnectOption << "\n> ";
                std::getline(std::cin >> std::ws, selectOption);
                send(soc, &selectOption, selectOption.length(), 0);
                char validateReply[100] = {0};
                read(soc, validateReply, 100);
                // std::string check = "Valid";
                if(strcmp(validateReply, "Valid") == 0){
                    std::cout << "[+] Authentication message send" << std::endl;
                    break;
                }else{
                    std::cout << "There is no such ID" << std::endl;
                }
            }
            std::string auth ;
            read(soc, &auth, 1024);
            if(std::stoi(auth) == 1){
                char buffer[1024] = {0};
                while (true) {
                    std::cout << "> " ;
                    std::string msg ;
                    std::getline(std::cin >> std::ws, msg);
                    char *message = (char *)&msg;

                    const char* strToAddFirst = "   [<] ";
                    const char* strToAddSecond = name.c_str();
                    std::strcat(message, strToAddFirst);
                    std::strcat(message, strToAddSecond);


                    send(soc, message, strlen(message), 0);
                    if (read(soc, buffer, sizeof(buffer)) <= 0) {
                        break;
                    }
                    std::cout << buffer << std::endl;
                    memset(buffer, 0, sizeof(buffer));
                }
                break;
            }else if(std::stoi(auth) == 2){
                std::cout << "[-] Rejected your request." << std::endl;
            }
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
        read(soc, displayOptions, 1024);
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
        if(std::stoi(selectedOption) == 1){
            char buffer[1024] = {0};
            while (true) {
                if (read(soc, buffer, sizeof(buffer)) <= 0) {
                    break;
                }
                // send(soc, buffer, strlen(buffer), 0);
                std::cout << buffer << std::endl;
                memset(buffer, 0, sizeof(buffer));

                std::cout << "> " ;
                std::string msg ;
                std::getline(std::cin >> std::ws, msg);
                char *message = (char *)&msg;

                const char* strToAddFirst = "   [<] ";
                const char* strToAddSecond = name.c_str();
                std::strcat(message, strToAddFirst);
                std::strcat(message, strToAddSecond);



                send(soc, message, strlen(message), 0);
            }
        }
    }
}