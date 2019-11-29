#include "processor.h"
#include "linux_parser.h"

#include <iostream>

Processor::Processor(): prevIdle_(0), prevNonIdle_(0){}

// Return the aggregate CPU utilization
float Processor::Utilization() {
  using namespace LinuxParser;
  std::vector<uint> utils = CpuUtilization();

  float idle = utils[CPUStates::kIdle_] + utils[CPUStates::kIOwait_];

  float nonIdle = utils[CPUStates::kUser_] + utils[CPUStates::kNice_] +
                 utils[CPUStates::kSystem_] + utils[CPUStates::kIRQ_] +
                 utils[CPUStates::kSoftIRQ_] + utils[CPUStates::kSteal_];

  float totalDiff = idle + nonIdle - (prevIdle_ + prevNonIdle_);
  float idleDiff = idle - prevIdle_;

  prevIdle_ = idle;
  prevNonIdle_ = nonIdle;

  return (totalDiff - idleDiff) / totalDiff;
}