#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor();
  float Utilization();
  
 private:
  unsigned int prevIdle_, prevNonIdle_;
};

#endif