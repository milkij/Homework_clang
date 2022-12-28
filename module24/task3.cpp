#include "iostream"
#include "iomanip"
#include "ctime"

void delay(int ms)
{
    int c = clock() + ms;
    while (clock() < c);
}

int main(){
#if 1
    std::time_t t = std::time(nullptr);
    t=0;
    std::tm* local = std::localtime(&t);
    std::cout<<"Input min and sec in format MM:SS: ";
    std::cin >> std::get_time(local,"%M:%S");
    std::time_t start_time = mktime(local);

    while (true) {
        if(start_time==t) {
            std::cout<<"DING! DING! DING";
            break;
        }
        std::tm localtime= *std::localtime(&start_time);
        std::cout<<std::put_time(&localtime,"%M:%S")<<std::endl;
        start_time--;
        delay(1000000);
        system("clear");
    }

#endif

}
