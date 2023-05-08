#include<iostream>

enum Day {
    sunday = 0,
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6
};

int main() {

    Day today = saturday;

    switch (today)
    {
    case sunday:
        std::cout << "It's Sunday!" << std::endl;
        break;

    case monday:
        std::cout << "It's Monday!" << std::endl;
        break;
    
    case tuesday:
        std::cout << "It's Tuesday!" << std::endl;
        break;

    case wednesday:
        std::cout << "It's Wednesday!" << std::endl;
        break;

    case thursday:
        std::cout << "It's Thursday!" << std::endl;
        break;

    case friday:
        std::cout << "It's Friday!" << std::endl;
        break;

    case saturday:
        std::cout << "It's Saturday!" << std::endl;
        break;
    
    default:
        break;
    }

    return 0;
}