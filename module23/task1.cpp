//
// Created by Александр Широков on 29.11.2022.
//
#include <iostream>

#define MONDAY "MONDAY"
#define THUESDAY "THUESDAY"
#define WEDNESDAY "WEDNESDAY"
#define THURSDAY "THURSDAY"
#define FRIDAY "FRIDAY"
#define SATURDAY "SATURDAY"
#define SUNDAY "SUNDAY"

int main() {
    std::cout << "Input the day of week by number and you can see the name of the day" << std::endl;
    std::cout << "Input num of day of week: ";
    int day;
    std::cin >> day;
    if(1==day) std::cout<<MONDAY;
    else if(2==day) std::cout<<THUESDAY;
    else if(3==day) std::cout<<WEDNESDAY;
    else if(4==day) std::cout<<THURSDAY;
    else if(5==day) std::cout<<FRIDAY;
    else if(6==day) std::cout<<SATURDAY;
    else if(7==day) std::cout<<SUNDAY;
    else std::cout << "There is no such day";
    return 0;
}