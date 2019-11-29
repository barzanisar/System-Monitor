#include <unistd.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
    : pid_(pid),
      user_(LinuxParser::User(pid)),
      cmd_(LinuxParser::Command(pid)),
      cpuUtilization_(0.0) {
  //UpdateCpuUtilization();
}

// Return this process's ID
int Process::Pid() const { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
  return cpuUtilization_;
}

// Return this process's CPU utilization
void Process::UpdateCpuUtilization() {
  cpuUtilization_ =
      (float(LinuxParser::ActiveJiffies(Pid())) / sysconf(_SC_CLK_TCK)) /
      float(UpTime());
}

// Return the command that generated this process
string Process::Command() const { return cmd_; }

// Return this process's memory utilization
string Process::Ram() const { return LinuxParser::Ram(Pid()); }

// Return the user (name) that generated this process
string Process::User() const { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(Pid()); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return (CpuUtilization() > a.CpuUtilization());
}