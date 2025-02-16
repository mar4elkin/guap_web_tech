#include "helpers.h"

std::string Helpers::uuid()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);
    const char hex_chars[] = "0123456789abcdef";

    std::ostringstream oss;
    for (int i = 0; i < 16; ++i) {
        oss << hex_chars[dis(gen)];
    }
    return oss.str();
}

std::string Helpers::timestamp_uuid(std::string file_ext)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H_%M_%S_%d_%m_%Y") << "_" << uuid() << file_ext;

    return oss.str();
}
