#include <dirent.h>
#include <unistd.h>
#include <iostream>
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
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string key;
  float memTotal, memFree;
  string line;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;

      if (key == "MemTotal:") {
        linestream >> memTotal;
      } else if (key == "MemFree:") {
        linestream >> memFree;
        break;
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime;
  string line;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }

  return uptime;
}

// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  size_t skipValues = 13;
  size_t readValues = 4;
  string value;
  long activeJiffies = 0;
  string line;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (skipValues--) {
      linestream >> value;
    }

    // std::cout << "active jiffies " << std::endl;
    while (readValues--) {
      linestream >> value;
      // std::cout << value << " ";
      activeJiffies += std::stol(value);
    }
    // std::cout << "Total activeJiffies " << activeJiffies << std::endl;
  }
  return activeJiffies;
}

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<uint> LinuxParser::CpuUtilization() {
  string key;
  vector<uint> utils;
  utils.resize(CPUStatesCount);
  string line;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;

      if (key == "cpu") {
        for (size_t i = 0; i < CPUStatesCount; ++i) {
          linestream >> utils[i];
        }
        return utils;
      }
    }
  }
  return utils;
}

template <typename TT>
TT LinuxParser::ReadValueFromFile(const std::string& keyToFind,
                                  const std::string& filename) {
  string key;
  TT value;
  string line;

  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;

      if (key == keyToFind) {
        linestream >> value;
        return value;
      }
    }
  }
  return value;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  return ReadValueFromFile<int>("processes",
                                std::string(kProcDirectory + kStatFilename));
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  return ReadValueFromFile<int>("procs_running",
                                std::string(kProcDirectory + kStatFilename));
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  // else {
  //   line = kProcDirectory + std::to_string(pid) +
  //                          kCmdlineFilename;
  // }

  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  uint ram_MB =
      0.001 * ReadValueFromFile<uint>(
                  "VmSize:", std::string(kProcDirectory + std::to_string(pid) +
                                         kStatusFilename));

  return std::to_string(ram_MB);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  return ReadValueFromFile<string>(
      "Uid:",
      std::string(kProcDirectory + std::to_string(pid) + kStatusFilename));
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uidToFind = Uid(pid);

  string line;
  string username, tmpX;
  string uid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> tmpX >> uid) {
        if (uid == uidToFind) {
          return username;
        }
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  size_t skipValues = 21;
  string starttime;
  string line;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (skipValues--) {
      linestream >> starttime;
    }

    linestream >> starttime;
  }

  //  The total elapsed time in seconds since the process started:
  // seconds = system_uptime_sec - (starttime / Hertz)
  // std::cout << "sys up time " << UpTime() << " start time " <<
  // std::stol(starttime) << " sys ticks/sec " << sysconf(_SC_CLK_TCK) <<
  // std::endl;
  return UpTime() - (std::stol(starttime) / sysconf(_SC_CLK_TCK));
}