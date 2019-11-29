#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System()
    : cpu_(Processor()),
      os_(LinuxParser::OperatingSystem()),
      kernel_(LinuxParser::Kernel()) {
  InitProcesses();
}

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // TODO: reinitialize processes to show new processes 
  // InitProcesses();
  for (auto& process : processes_){
      process.UpdateCpuUtilization();
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Return the operating system name
std::string System::OperatingSystem() { return os_; }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }

void System::InitProcesses() {
  std::vector<int> pids = LinuxParser::Pids();
  processes_.clear();
  processes_.reserve(pids.size());

  for (auto pid: pids) {
    processes_.emplace_back(pid); // implicit construction of processes with pid
  }
}
