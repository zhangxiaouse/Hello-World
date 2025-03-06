#include "text_processor.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <regex>

namespace utils {
namespace text {

std::string TextProcessor::toUpperCase(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), 
                   ::toupper);
    return result;
}

std::string TextProcessor::toLowerCase(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), 
                   ::tolower);
    return result;
}

std::vector<std::string> TextProcessor::split(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    
    while ((end = text.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + delimiter.length();
    }
    
    // Add the last part
    if (start < text.length()) {
        tokens.push_back(text.substr(start));
    }
    
    return tokens;
}

std::string TextProcessor::replace(const std::string& text, const std::string& search, const std::string& replace) {
    std::string result = text;
    size_t pos = 0;
    
    while ((pos = result.find(search, pos)) != std::string::npos) {
        result.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    
    return result;
}

std::map<std::string, int> TextProcessor::wordFrequency(const std::string& text) {
    std::map<std::string, int> frequency;
    std::regex wordRegex("\\w+");
    
    // Use regex to split words
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::string word = toLowerCase((*i).str());
        frequency[word]++;
    }
    
    return frequency;
}

} // namespace text
} // namespace utils 