#include "../includes/PathFilter.h"

#pragma unmanaged

PathFilter::PathFilter() {}
PathFilter::~PathFilter() {}

void PathFilter::addIgnoreRegex(const std::regex &re) {
  mIgnorePathRegexVector.push_back(re);
}

bool PathFilter::ignorePath(const std::string &path) {
  std::smatch match;
  for (std::regex re : mIgnorePathRegexVector) {
    if (std::regex_match(path, match, re)) {
      return true;
    }
  }
  return false;
}
