#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    //update current pids
    vector <int> current_pids = LinuxParser::Pids();
    //clear prev processes
    processes_.clear(); 
    int pid_size = current_pids.size(); 
    //instanciate new processes
    for (int i = 0 ; i < pid_size; i ++ ){
        Process temp_process(current_pids[i]) ;
        processes_.push_back(temp_process) ;
    }
    Process::ProcessSort(&processes_) ; //Sort ascending order according to memory utilization
    reverse(processes_.begin(), processes_.end()); // reverse to get descending order
    return processes_; 
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel() ; 
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization() ; }

// DONE: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem() ;
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses() ;
 }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses() ; 
 }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
 }