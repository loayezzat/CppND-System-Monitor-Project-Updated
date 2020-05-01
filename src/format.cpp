#include <string>

#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds ) { 
    string HH = std::to_string(seconds/3600) ;
    seconds = seconds%3600 ; 
    string MM = std::to_string(seconds/60) ;
    seconds = seconds%60 ;
    string SS = std::to_string(seconds) ;
    if (SS.size() == 1 ) SS = "0" + SS  ; 
    if (HH.size() == 1 ) HH = "0" + HH  ; 
    if (MM.size() == 1 ) MM = "0" + MM  ; 
    return HH +":"+MM+":"+SS ;   
}