#include <iomanip>
#include <sstream>
#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
  int min, hr, sec;
  hr = seconds / 3600;
  seconds = seconds % 3600;
  min = seconds / 60;
  sec = seconds % 60;

  std::ostringstream output;
  output << std::setw(2) << std::setfill('0') << hr << ":"
         << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2)
         << std::setfill('0') << sec << std::endl;
  return output.str();
}