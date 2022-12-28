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
    int min,sec;
    printf("Input min and sec: ");
    std::cin>>min>>sec;
    std::time_t finish_time = std::time(nullptr)+(std::time_t)(min*60+sec)-1;
    while(true){
        std::time_t temp_time =std::time(nullptr);
        std::cout<<min<<':'<<sec<<std::endl;
        if(sec-1==-1) {
            sec=60;
            min--;
        }
        sec--;
        delay(1000000);
        if(temp_time==finish_time) {
            std::cout<<"DING! DING! DING";
            break;
        }
    }

#endif
}
