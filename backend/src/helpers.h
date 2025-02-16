#pragma once

#include <random>
#include <string>
#include <cstring>
#include <chrono>
#include <sstream>
#include <iomanip>

class Helpers {
    public:
        static std::string uuid();
        static std::string timestamp_uuid(std::string file_ext="");
    };