#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <vector>

/* CPUStates */
#define kUser  0 
#define kNice  1 
#define kSystem 2
#define kIdle 3
#define kIOwait 4
#define kIRQ 5
#define kSoftIRQ 6
#define kSteal 7
#define kGuest 8
#define kGuestNice 9


class Processor {
 public:
  float Utilization();  

  
 private:
    std::vector <long int> cpu_times_prev;

};

#endif