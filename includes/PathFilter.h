#ifndef FILTER_H
#define FILTER_H

#include <regex>
#include <string>
#include <vector>

class PathFilter {
    private:
        std::vector<std::regex> mIgnorePathRegexVector;

    public:
        PathFilter();
        ~PathFilter();

        /** add a regex to the internal list of ignore filters */
        void addIgnoreRegex(const std::regex &re);
        /** return true if path should be ignored, false otherwise */
        bool ignorePath(const std::string &path);
};

#endif
