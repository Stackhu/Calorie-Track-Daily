#include "Utils.h"
#include <fstream>
#include <sstream>
#include <cctype>

namespace Utils {
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(trim(token));
        }
        return tokens;
    }

    std::string trim(const std::string& str) {
        size_t start = 0;
        size_t end = str.size();
        while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) ++start;
        while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) --end;
        return str.substr(start, end - start);
    }

    bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
}
