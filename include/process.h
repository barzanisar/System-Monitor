#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 public:
  Process(int pid);
  int Pid() const;                               
  std::string User() const;                      
  std::string Command() const;                   
  float CpuUtilization() const;                  
  std::string Ram() const;                       
  long int UpTime() const;                       
  bool operator<(Process const& a) const;  

  void UpdateCpuUtilization();

 private:
  int pid_;
  std::string user_;
  std::string cmd_;
  float cpuUtilization_;

};

#endif