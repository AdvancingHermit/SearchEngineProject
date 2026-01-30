#include "../../core/interfaces.h"
#include <fstream>

static std::string extractFileSection(std::string filename, long long start, long long end) {
  std::string contents;
  std::ifstream file;
  file.open (filename);
  if (!file.good()) {
    printf("Error reading file");
    return contents;
  }
  if (!file.is_open()) {
    printf("No file is open");
    return contents;
  }
  if (!file) return {};

  file.seekg(start);
  long long n = end - start;
  std::string out;
  out.resize(n);
  file.read(&out[0], n);
  return out;
};