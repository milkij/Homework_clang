#include "iostream"
#include "ctime"
#include "iomanip"
#include "map"

#define PROD 1

void println(std::string text){
    std::cout<<text<<std::endl;
}
void print(std::string text){
    std::cout<<text;
}

int main() {
#if PROD
    std::multimap<std::time_t, std::string> calendar;
    std::string fullname;
    std::time_t t = std::time(nullptr);
    std::tm local = *std::localtime(&t);
    while (true) {
        print("Input fullname: ");
        std::cin>>fullname;
        if(fullname=="end") break;
        print("Input DOB (YYYY/MM/DD): ");
        std::cin >> std::get_time(&local,"%Y/%m/%d");
        std::time_t time_of_dob = mktime(&local);
        calendar.insert(std::make_pair(time_of_dob,fullname));
    }
    std::time_t t2 = std::time(nullptr);
    std::tm current_time = *std::localtime(&t);
    std::string today_DOBs;
    println("---------\nTODAYS DOB:");
    for (std::map<std::time_t,std::string>::iterator it=calendar.begin();it!=calendar.end();++it){
        std::tm loc = *std::localtime(&it->first);
        if(loc.tm_mon==current_time.tm_mon && loc.tm_mday==current_time.tm_mday){
            std::cout<<loc.tm_mon<<"/"<<loc.tm_mday<<" - "+it->second<<" ";
        }

    }
    std::cout<<std::endl;
    println("---------\nNEXT DOB:");
    for (std::map<std::time_t,std::string>::iterator it=calendar.begin();it!=calendar.end();++it){
        std::tm loc = *std::localtime(&it->first);
        if(loc.tm_mon>current_time.tm_mon ||
           (loc.tm_mon=current_time.tm_mon && loc.tm_mday>current_time.tm_mday))
            std::cout<<loc.tm_mon<<"/"<<loc.tm_mday<<" - "+it->second<<" ";
    }
#endif

}
