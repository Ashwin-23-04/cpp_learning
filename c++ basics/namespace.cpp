#include<iostream>

namespace first{
    int x = 1;
}
namespace second{
    int x = 2;
}

int main(){
    using std::string;
    

    string name = "Ashwin";
    std::cout << "Hello " << name << std::endl;
    using namespace std;
    int x = 0;

    cout << x << endl;
    cout << first::x << endl;
    cout << second::x << endl;
    
    return 0;
}