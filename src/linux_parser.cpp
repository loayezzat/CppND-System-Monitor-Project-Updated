#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os,version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float percent = 0.0 ;
  long value , memtotal = 1 , memfree = 1  ;//avoid dividing by zero 
  string line , key ; 
  std::ifstream stream (kProcDirectory+kMeminfoFilename) ; 
  if (stream.is_open()){
    while (std::getline(stream , line )){
      std::istringstream linestream(line) ;
      linestream >> key >> value ; 
      if (key =="MemTotal:"){
        memtotal = value ; 
      } 
      else if (key =="MemFree:"){
        memfree = value ;
        break ;
      }
    }
  }
  percent = (float)(memtotal-memfree)/(memtotal) ; 
  //std::cout << "Total:" <<memtotal <<" Free:" <<memfree  << " percent:" << percent << std::endl ;
  return percent ; 
 }

// DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  double up_time=0, idle_time=0;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time >> idle_time ;
  }
  return up_time;
 }

//return vector of long ints instead of strings for sake of efficiency 
std::vector<long int> LinuxParser::CpuUtilization(){
  std::vector <long int> cpu_times(10, 0);
  std::string line , key; 
  std::ifstream filestream (kProcDirectory + kStatFilename) ;
  if (filestream.is_open()){
      while (std::getline(filestream , line)){
        std::istringstream linestream(line) ; 
        linestream >> key ;
        if (key == "cpu") {
          for (int i=0; i< 10 ; i++){
            linestream >> cpu_times.at(i) ; 
          }
          return cpu_times; 
        }
      }
  }
  return cpu_times;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream stream (kProcDirectory + kStatFilename) ;
  std::string line , name ;
  int value = 0 ;
  if (stream.is_open()){
    while (std::getline(stream , line ) ){
      std::istringstream linestream(line);
      while (linestream >> name >> value) {
        if (name == "processes") { 
          return value;
        }
      }
    }

  }
  return value ; 
 }

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream stream (kProcDirectory + kStatFilename) ;
  std::string line , name ;
  int value = 0 ;
  if (stream.is_open()){
    while (std::getline(stream , line ) ){
      std::istringstream linestream(line);
      while (linestream >> name >> value) {
        if (name == "procs_running") {
          return value;
        }
      }
    }

  }
  return value ; 
 }

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  std::string pid_s = std::to_string(pid) ; 
  std::string line ;
  std::ifstream filestream(kProcDirectory +pid_s+ kCmdlineFilename) ;
  if (filestream.is_open()){
    getline(filestream ,line );
      return line ; 
  }
  return line ;
 }

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
    std::string key , line , ram_s  ; 
    long int ram =0 ;
    std::string pid_s = std::to_string(pid) ; 
    std::ifstream filestream(kProcDirectory+pid_s+kStatusFilename) ; 
    if (filestream.is_open()){
      while (std::getline(filestream, line)){
        std::istringstream linestream(line) ; 
        if(linestream >> key >> ram ) {
          /*despite VmSize is highlighted in the course material 
          the right Key to use is VmData which is corresponding to real size 
          while VmSize is corresponding to virtual memory size */
          if (key == "VmData:"){
          ram_s = std::to_string(ram/1024) ; 
          return ram_s ; 
          }
        }
      }

    }
    ram_s = std::to_string(0) ; 
    return ram_s ;
 }

// DONE: Read and return the user-ID (UID) associated with a process(PID)
string LinuxParser::Uid(int pid) { 
    std::string key , line , uid_s  ; 
    int uid ;
    std::string pid_s = std::to_string(pid) ; 
    std::ifstream filestream(kProcDirectory+pid_s+kStatusFilename) ; 
    if (filestream.is_open()){
      while (std::getline(filestream, line)){
        std::istringstream linestream(line) ; 
        linestream >> key >> uid ; 
        if (key == "Uid:"){
          uid_s = std::to_string(uid) ; 
          return uid_s ; 
        }
      }
    }
    return uid_s ;
 }

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) { 

  int uid = std::stoi(LinuxParser::Uid(pid)); //get the uid of a given process 
  std::string line , user , x ;
  int uid_f ; //uid from file 
  std::ifstream filestream (kPasswordPath) ;
  if (filestream.is_open()){
    while (std::getline(filestream , line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line) ; 
      linestream >> user >> x >> uid_f ; //need only first string 
      if (uid_f == uid){
        return user ; 
      }
    }
  } 
  return user;
  
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
    std::string pid_s = std::to_string(pid) ; 
    std::ifstream filestream(kProcDirectory+pid_s+kStatFilename) ; 
    std::string line , value  ; 
    long start_time =0 , up_time =0 ;
    int i = 1 ; 
    if (filestream.is_open()){
      while (filestream >> value )
      {
        if (i == 22 ) { 
            start_time = std::stol(value) ; 
            //up_time (process up time) = system uptime - process start time 
            up_time = UpTime() - start_time/sysconf(_SC_CLK_TCK) ; 
            return up_time ; 
        }
        i++ ; 
      }
    }
  
    return up_time ;
}

//Read data and return cpu utlization for a given process
float LinuxParser::Cpu(int pid){
    std::string pid_s = std::to_string(pid) ; 
    std::ifstream filestream(kProcDirectory+pid_s+kStatFilename) ; 
    std::string line , value  ; 
    long up_time{0} , u_time{0} , s_time{0} , cu_time{0} , cs_time{0} ,start_time{0} 
    , total_time{0} ; 
    float cpu_usage = 0.0 ; 
    int i = 1 ; 
    if (filestream.is_open()){
      while (filestream >> value )
      {
        switch (i)
        {
        case 14 :
          u_time = std::stol(value) ; break;
        case 15 :
          s_time = std::stol(value) ; break;
        case 16 :
          cu_time = std::stol(value) ; break;
        case 17 :
          cs_time = std::stol(value) ; break;
        case 22 :
          start_time = std::stol(value) ; break;
        }
        i++ ; 
      }
          
      up_time = UpTime() - start_time/sysconf(_SC_CLK_TCK) ;//up_time (process up time) = system uptime - process start time 
      total_time = u_time+ s_time+ cu_time+ cs_time ; //in this approach we included the time from children processes
      total_time = total_time /sysconf(_SC_CLK_TCK) ; //(seconds)
      cpu_usage = (float)total_time / up_time ; 
    }

    return cpu_usage ;

    

}