#include<iostream>
#include<fstream>

int main(){
    std::fstream file;
    file.open("log.txt", std::ios::app);
    file<<". My name is Ashwin";
    file.close();
    std::string s;
    file.open("log.txt", std::ios::in);
    while(file>>s){
        std::cout<<s << " ";
    }
    file.close();
    return 0 ;
}