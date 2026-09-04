#pragma once
#include <string>

namespace installer {

// Result of an install attempt: success flag + a human-readable message
struct Result {
    bool success;
    std::string message;
};

// Takes a path to either a .zip file or a folder containing a Python project,
// and installs it as a desktop application (menu entry).
Result install_from_path(const std::string& input_path);

} // namespace installer
