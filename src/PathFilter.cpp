#include "../includes/PathFilter.h"
#include <algorithm>

#pragma unmanaged

static const std::string doubleStarPrefix("**/");

static const std::string ensureTrailingSeparator(const std::string &path) {
  return path.back() == '/' ? path : path + '/';
}

static const std::string removeLeadingSeparator(const std::string &path) {
  unsigned int i = 0;
  while (path[i++] == '/') {}
  return i > 1 ? path.substr(i - 1) : path;
}

PathFilter::PathFilter(const std::string &root) : mRoot(ensureTrailingSeparator(root)) {}

PathFilter::~PathFilter() {}

void PathFilter::addIgnoreFilter(const std::string &filter) {
  // `**/path/parts[/]`
  if (std::equal(doubleStarPrefix.begin(), doubleStarPrefix.end(), filter.begin())) {
    mFilters.push_back(ensureTrailingSeparator(filter.substr(doubleStarPrefix.length())));
  }
  // `[/]absolute/path[/]`
  else {
    mRootFilters.push_back(mRoot + removeLeadingSeparator(filter));
  }
}

bool PathFilter::ignorePath(const std::string &path) {
  const std::string path2(ensureTrailingSeparator(path));
  for (std::string filter : mRootFilters) {
    if (path2.length() >= filter.length() && std::equal(filter.begin(), filter.end(), path2.begin())) {
        return true;
    }
  }
  for (std::string filter : mFilters) {
    if (path2.find(filter)) {
      return true;
    }
  }
  return false;
}
