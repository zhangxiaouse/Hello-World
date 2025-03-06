#include <iostream>
#include <string>
#include "utils/printer.h"
#include "utils/file/file_handler.h"
#include "utils/text/text_processor.h"

// Demonstrate printing functionality
void demonstratePrinting() {
    utils::printMessage("=== Printing Module Demo ===");
    utils::printMessage("This is a simple message");
}

// Demonstrate text processing functionality
void demonstrateTextProcessing() {
    utils::printMessage("\n=== Text Processing Module Demo ===");
    
    // Test case conversion
    std::string testText = "Hello World Example";
    utils::printMessage("Original text: " + testText);
    utils::printMessage("Convert to uppercase: " + utils::text::TextProcessor::toUpperCase(testText));
    utils::printMessage("Convert to lowercase: " + utils::text::TextProcessor::toLowerCase(testText));
    
    // Test text splitting
    utils::printMessage("\nSplit text (by space):");
    std::vector<std::string> words = utils::text::TextProcessor::split(testText, " ");
    for (const auto& word : words) {
        utils::printMessage(" - " + word);
    }
    
    // Test text replacement
    utils::printMessage("\nReplace 'World' with 'C++':");
    std::string replaced = utils::text::TextProcessor::replace(testText, "World", "C++");
    utils::printMessage(replaced);
    
    // Test word frequency counting
    std::string longText = "This is a test. This test is to demonstrate word frequency. Is this working?";
    utils::printMessage("\nWord frequency count:");
    utils::printMessage("Text: " + longText);
    
    auto frequency = utils::text::TextProcessor::wordFrequency(longText);
    for (const auto& pair : frequency) {
        utils::printMessage(" - '" + pair.first + "': " + std::to_string(pair.second) + " times");
    }
}

// Demonstrate file operation functionality
void demonstrateFileOperations() {
    utils::printMessage("\n=== File Operations Module Demo ===");
    
    // Create test file
    std::string testFilePath = "test_file.txt";
    std::string content = "This is a test file.\nUsed to demonstrate file operation functionality.\nContains multiple lines of text.";
    
    utils::printMessage("Creating test file: " + testFilePath);
    bool writeResult = utils::file::FileHandler::writeFile(testFilePath, content);
    
    if (writeResult) {
        utils::printMessage("File created successfully!");
        
        // Read file content
        utils::printMessage("\nReading file content:");
        std::string readContent = utils::file::FileHandler::readFile(testFilePath);
        utils::printMessage(readContent);
        
        // List current directory files
        utils::printMessage("\nCurrent directory file list:");
        auto files = utils::file::FileHandler::listFiles(".");
        for (const auto& file : files) {
            utils::printMessage(" - " + file);
        }
    } else {
        utils::printMessage("Failed to create file!");
    }
}

int main() {
    utils::printMessage("Hello World - C++ Code Modularization and File Organization Example");
    utils::printMessage("=======================================\n");
    
    // Demonstrate each module functionality
    demonstratePrinting();
    demonstrateTextProcessing();
    demonstrateFileOperations();
    
    return 0;
} 