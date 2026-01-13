#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm> // for std::transform
#include <cctype> // for std::tolower

namespace RoutePlanner {
    // Takes string by value, returns lowercased copy
    inline std::string toLower(std::string data) {
        std::transform(data.begin(), data.end(), data.begin(),
                    [](unsigned char c){ return std::tolower(c); });
        return data;
    }
}


#endif