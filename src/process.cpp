#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid(){ 
    return pid_ ;
}

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return LinuxParser::Cpu(pid_) ;
}

// DONE: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_) ; 
 }

// DONE: Return this process's memory utilization
string Process::Ram() { 
    return ram_;
 }

// DONE: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(pid_) ;
}

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_) ;
 }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a )const { 
    long  ram1 = 0 ; 
    long  ram2 = 0 ;
    if ((this->ram_).size() >0 ) { ram1 = std::stol(this->ram_); } //check to avoid empty string throwing exceptions 
    if ((a.ram_).size() >0 ){ ram2 = std::stol(a.ram_);}
    return (ram1 < ram2 ) ; 

 }

//Update ram variable 
void Process::UpdateMemory(){
    ram_ = LinuxParser::Ram(pid_) ; 
}

//This Function sorts the vector in ascending order
void Process::ProcessSort(std::vector<Process> *v) {
    std::sort(v->begin() , v->end() ) ; 
}