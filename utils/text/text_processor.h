#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>
#include <vector>
#include <map>

namespace utils {
namespace text {

/**
 * Text processor class providing various text operation functionalities
 */
class TextProcessor {
public:
    /**
     * Convert text to uppercase
     * @param text Input text
     * @return Converted text
     */
    static std::string toUpperCase(const std::string& text);
    
    /**
     * Convert text to lowercase
     * @param text Input text
     * @return Converted text
     */
    static std::string toLowerCase(const std::string& text);
    
    /**
     * Split text
     * @param text Text to split
     * @param delimiter Delimiter
     * @return Array of split text segments
     */
    static std::vector<std::string> split(const std::string& text, const std::string& delimiter);
    
    /**
     * Replace specified content in text
     * @param text Original text
     * @param search Content to search for
     * @param replace Content to replace with
     * @return Text after replacement
     */
    static std::string replace(const std::string& text, const std::string& search, const std::string& replace);
    
    /**
     * Count word frequency in text
     * @param text Input text
     * @return Mapping of words and their frequencies
     */
    static std::map<std::string, int> wordFrequency(const std::string& text);
};

} // namespace text
} // namespace utils

#endif // TEXT_PROCESSOR_H 