#include "processor.h"
#include <vector>

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float CPU_Percentage = 0.0 ; 
    std::vector <long int > cpu_times =  LinuxParser::CpuUtilization();
    long int PrevIdle,Idle,PrevNonIdle,NonIdle,PrevTotal,Total,totald,idled ;
    //check for first call (cpu_times_prev uninitialized yet)
    if (this->cpu_times_prev.size() != 10 ){ 
        cpu_times_prev = cpu_times; 
        return 0.0; 
    }else{

    
        PrevIdle = cpu_times_prev[kIdle] + cpu_times_prev[kIOwait] ;
        Idle = cpu_times[kIdle] + cpu_times[kIOwait] ;

        PrevNonIdle = cpu_times_prev[kUser] + cpu_times_prev[kNice] + cpu_times_prev[kSystem]
                 + cpu_times_prev[kIRQ] + cpu_times_prev[kSoftIRQ] + cpu_times_prev[kSteal];
        NonIdle =  cpu_times[kUser] + cpu_times[kNice] + cpu_times[kSystem]
                 + cpu_times[kIRQ] +  cpu_times[kSoftIRQ] + cpu_times[kSteal];

        PrevTotal = PrevIdle + PrevNonIdle;
        Total = Idle + NonIdle;

        // differentiate: actual value minus the previous one for more precision
        totald = Total - PrevTotal;
        idled = Idle - PrevIdle;

        CPU_Percentage = (float)(totald - idled)/totald;
        cpu_times_prev = cpu_times; 
        return CPU_Percentage ;
    }

 }

 