#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid ) : pid_(pid) {
      UpdateMemory() ; 
  }
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  
  void UpdateMemory();                       //assign memory utilization to ram_
  static bool Compare (Process a , Process b ) ; 
  static void ProcessSort(std::vector<Process> *v) ; 
  
 private:
 int pid_ = 0;
 std::string  ram_;
};

#endif