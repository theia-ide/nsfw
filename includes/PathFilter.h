#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>

class PathFilter {
    private:
        std::vector<std::string> mRootFilters;
        std::vector<std::string> mFilters;
        std::string mRoot;

    public:
        PathFilter(const std::string &root);
        ~PathFilter();

        /** register a path filter */
        void addIgnoreFilter(const std::string &filter);
        /** return true if path should be ignored, false otherwise */
        bool ignorePath(const std::string &path);
};

#endif
