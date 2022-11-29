//
// Created by Александр Широков on 29.11.2022.
//
#include <iostream>

#define MONDAY 1
#define THUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6
#define SUNDAY 7

int main() {
    std::cout << "Input the day of week by number and you can see the name of the day" << std::endl;
    std::cout << "Input num of day of week: ";
    int day;
    std::cin >> day;
    if(MONDAY==day) std::cout<<"Monday";
    else if(THUESDAY==day) std::cout<<"Thusday";
    else if(WEDNESDAY==day) std::cout<<"Wednesday";
    else if(THURSDAY==day) std::cout<<"Thursday";
    else if(FRIDAY==day) std::cout<<"Friday";
    else if(SATURDAY==day) std::cout<<"Saturday";
    else if(SUNDAY==day) std::cout<<"Sunday";
    else std::cout << "There is no such day";
    return 0;
}