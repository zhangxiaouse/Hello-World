#include "file_handler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../printer.h"

// Select directory operation headers based on platform
#ifdef _WIN32
#include <io.h>
#include <direct.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace utils {
namespace file {

std::string FileHandler::readFile(const std::string& filePath) {
    if (!fileExists(filePath)) {
        utils::printMessage("Error: File does not exist - " + filePath);
        return "";
    }
    
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}

bool FileHandler::writeFile(const std::string& filePath, const std::string& content) {
    try {
        std::ofstream file(filePath);
        file << content;
        file.close();
        return true;
    } catch (const std::exception& e) {
        utils::printMessage("Error: Failed to write to file - " + std::string(e.what()));
        return false;
    }
}

bool FileHandler::fileExists(const std::string& filePath) {
    // Use standard library to check file existence
    std::ifstream file(filePath);
    return file.good();
}

std::vector<std::string> FileHandler::listFiles(const std::string& dirPath) {
    std::vector<std::string> fileList;
    
#ifdef _WIN32
    // Windows platform implementation
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile((dirPath + "\\*").c_str(), &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        utils::printMessage("Error: Directory does not exist - " + dirPath);
        return fileList;
    }
    
    do {
        std::string fileName = findData.cFileName;
        if (fileName != "." && fileName != "..") {
            fileList.push_back(fileName);
        }
    } while (FindNextFile(hFind, &findData));
    
    FindClose(hFind);
#else
    // Unix/Linux/MacOS platform implementation
    DIR* dir = opendir(dirPath.c_str());
    if (dir == nullptr) {
        utils::printMessage("Error: Directory does not exist - " + dirPath);
        return fileList;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;
        if (fileName != "." && fileName != "..") {
            fileList.push_back(fileName);
        }
    }
    
    closedir(dir);
#endif
    
    return fileList;
}

} // namespace file
} // namespace utils 