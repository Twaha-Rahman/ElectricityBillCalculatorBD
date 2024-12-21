#include <cstdio>
#include <cstring>
#include <ios>
#include <iostream>
#include <limits>

#include "safeInput.h"

namespace SafeInput {
using std::string;

void clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// [lb, ub] = [lowerBound, upperBound] = inclusive range
int getNumberBetween(int lb, int ub, const char *retryStr) {
  int x;
  std::cin >> x;

  while ((x < lb) || (x > ub)) {
    clearInputBuffer();
    std::cout << retryStr;
    fflush(stdout);

    std::cin >> x;
  }

  return x;
}

// zero is not a positive or negative integer
int getPositiveNumber(const char *retryStr) {
  int x;
  std::cin >> x;

  while (x <= 0) {
    clearInputBuffer();
    std::cout << retryStr;
    fflush(stdout);

    std::cin >> x;
  }

  return x;
}

// allows the sentinel -1 value
int getPositiveNumberAllowingSentinel(const char *retryStr) {
  int x;
  std::cin >> x;

  while ((x <= 0) && (x != -1)) {
    clearInputBuffer();
    std::cout << retryStr;
    fflush(stdout);

    std::cin >> x;
  }

  return x;
}

bool isAlphanumeric(string buffer) {
  for (int i = 0; buffer[i] != '\0'; i++) {
    bool isLowercase = (buffer[i] >= 'a') && (buffer[i] <= 'z');
    bool isUppercase = (buffer[i] >= 'A') && (buffer[i] <= 'Z');
    bool isNumber = (buffer[i] >= '0') && (buffer[i] <= '9');

    if (!isUppercase && !isLowercase && !isNumber) {
      return false;
    }
  }

  return true;
}

string getValidFilename(const char *retryStr) {
  // char *buffer = new char[1024];
  std::string buffer;
  std::cin >> buffer;
  // std::cin.get(buffer, 1024);

  while (!isAlphanumeric(buffer)) {
    std::cout << retryStr;
    clearInputBuffer();
    // std::cin >> std::setw(1024) >> localBuff;
    // std::cin.get(buffer, 1024);
    std::cin >> buffer;
  }

  return buffer;
}

} // namespace SafeInput
