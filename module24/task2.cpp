#include "iostream"
#include "ctime"
#include "iomanip"
#include "map"
#include "thread"

bool isDateEquel (std::time_t dobTime,std::string n, std::string condition)
{
    std::time_t t = std::time(nullptr);
    std::tm currentTime = *std::localtime(&t);
    std::tm dobT = *std::localtime(&dobTime);
    if((currentTime.tm_mon==dobT.tm_mon && currentTime.tm_mday==dobT.tm_mday)
       && condition=="E")
    {
        std::cout << std::put_time(&dobT,"%Y/%m/%d") << " - " << n << std::endl;
        return true;
    }
    else if((currentTime.tm_mon<=dobT.tm_mon && currentTime.tm_yday<dobT.tm_yday
            )
            && condition=="nE")
    {
        std::cout << std::put_time(&dobT,"%Y/%m/%d") << " - " << n << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    std::multimap<std::time_t, std::string> dobCalendar;
    std::multimap<std::time_t, std::string> dobCalendarWithoutYY;
    while (true)
    {
        std::time_t t = 0;
        std::tm localTime = *std::localtime(&t);
        std::string name;
        std::cout<<"Input Name: ";
        std::cin>>name;
        //exit condition
        if(name=="exit") break;
        std::cout<<"Input DOB: ";
        std::cin >> std::get_time(&localTime,"%Y/%m/%d");
        //insert in multymap dobCalendar;
        dobCalendar.insert(std::make_pair(mktime(&localTime),name));
    }
    //loop in dobCalendar;
    std::cout<<"Cur DOB:"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bool isNotCurDob = false;
    for (std::multimap<std::time_t,std::string>::iterator it = dobCalendar.begin();
         it!=dobCalendar.end();++it)
    {
        if(isDateEquel(it->first,it->second,"E")) {
            isNotCurDob=true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };

    }
    if(!isNotCurDob){
        std::cout<<"-------//-------"<<std::endl;
    }
    std::cout<<"Next DOB:"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    isNotCurDob = false;
    for (std::multimap<std::time_t,std::string>::iterator it = dobCalendar.begin();
         it!=dobCalendar.end();++it)
    {
        if(isDateEquel(it->first,it->second,"nE")) {
            isNotCurDob=true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };
    }
    if(!isNotCurDob){
        std::cout<<"-------//-------"<<std::endl;
    }
}