#include <iostream>
#include <algorithm> 
#include "ncurses_display.h"
#include "system.h"

#include "format.h"

int main() {
  System system;
  NCursesDisplay::Display(system);

  // TEST
  //using namespace std;

  // // System and Processor
  // std::cout << "CPU: " << system.Cpu().Utilization() * 100 << std::endl;
  // std::cout << "Mem: " << system.MemoryUtilization() * 100 << std::endl;
  // std::cout << "Total Processes: " << system.TotalProcesses() << std::endl;
  // cout << "Running Processes: " << to_string(system.RunningProcesses()) << endl;
  // cout << "Up Time: " <<  Format::ElapsedTime(system.UpTime()) << endl;


  // // Processes
  // cout << endl << endl;
  // std::vector<Process>& processes = system.Processes();
  // cout << "Processes found: " << processes.size() << endl << endl;
  // int processCount = std::min(10, int(processes.size()));
  // for (size_t i = 0; i< processCount; ++i){
  //   cout << "PID: " << processes[i].Pid() << endl;
  //   cout << "CPU %: "<< processes[i].CpuUtilization() * 100 << endl;
  //   cout << "User : "<< processes[i].User() << endl;
  //   cout << "Ram : "<< processes[i].Ram() << endl;
  //   cout << "Time : "<< processes[i].UpTime() << endl;
  //   cout << "Command : "<< processes[i].Command() << endl;
  //   cout << endl << endl;
  //}
  

}