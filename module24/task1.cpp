#include "iostream"
#include "ctime"
#include "vector"
#define MAINPROGRAM 1

struct tasker
{
    std::string name_of_task;
    std::time_t time_of_begin;
    std::time_t time_of_end;
    float wasted_time=0;
    bool is_curent;
};
void println(std::string text) {
    std::cout<<text<<std::endl;
}
bool finish_task(std::vector<tasker>& task) {
    if(task.size()==0) return false;
    task.back().time_of_end=std::time(nullptr);
    task.back().wasted_time=(float)(task.back().time_of_end-task.back().time_of_begin)/3600;
    task.back().is_curent= false;
    return true;
}

int main(){
    std::vector<tasker> dashboard;
    tasker current_task;
    std::string command;
    bool true_command= true;


#if MAINPROGRAM
    while(true) {
        println("Input command(begin,end,status,exit):");
        std::cin>>command;
        if(command=="begin") {
            finish_task(dashboard);
            println("Input name of task");
            std::cin >> current_task.name_of_task;
            current_task.time_of_begin = std::time(nullptr);
            current_task.is_curent=true;
            dashboard.push_back(current_task);
        }
        else if(command=="end" && dashboard.size()!=0) {
            finish_task(dashboard);
        }
        else if(command=="status") {
            bool is_exists_finished_tasks=false;
            if(dashboard.size()!=0) {
                println("Finished tasks:");
                for (int i=0; i<dashboard.size(); i++) {
                    if(dashboard[i].is_curent==false){
                        is_exists_finished_tasks=true;
                        std::cout << i+1 << ". " << dashboard[i].name_of_task
                                  << " waisted time: " << dashboard[i].wasted_time << "h."
                                  << std::endl;
                    }
                    if(!is_exists_finished_tasks) println("--------");
                }
                if(dashboard.back().is_curent==true) {
                    println("Current task:");
                    std::cout <<  dashboard.back().name_of_task << std::endl;
                } else println("Current task:/n-----------");
            }
        }
        else if(command=="exit") {
            return 0;
        } else println("Incorrect command! Try again");
    }
#endif
}