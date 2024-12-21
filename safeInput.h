#if !defined(SAFEINPUT_H)
#define SAFEINPUT_H

#include <string>

namespace SafeInput {
void clearInputBuffer();
int getNumberBetween(int lb, int ub, const char *retryStr);
int getPositiveNumber(const char *retryStr);
int getPositiveNumberAllowingSentinel(const char *retryStr);
std::string getValidFilename(const char *retryStr);
} // namespace SafeInput

#endif
