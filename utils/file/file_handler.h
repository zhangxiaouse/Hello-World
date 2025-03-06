#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>

namespace utils {
namespace file {

    /**
     * File handler class for basic file operations
     */
    class FileHandler {
    public:
        /**
         * Read file content
         * @param filePath Path to the file
         * @return String containing file content
         */
        static std::string readFile(const std::string& filePath);
        
        /**
         * Write content to file
         * @param filePath Path to the file
         * @param content Content to write
         * @return Whether the write operation was successful
         */
        static bool writeFile(const std::string& filePath, const std::string& content);
        
        /**
         * Check if file exists
         * @param filePath Path to the file
         * @return Whether the file exists
         */
        static bool fileExists(const std::string& filePath);
        
        /**
         * Get all filenames in the specified directory
         * @param dirPath Directory path
         * @return List of filenames
         */
        static std::vector<std::string> listFiles(const std::string& dirPath);
    };

} // namespace file
} // namespace utils

#endif // FILE_HANDLER_H 