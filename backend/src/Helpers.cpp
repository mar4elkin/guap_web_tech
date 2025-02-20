#include "Helpers.h"
#include "str_to_md5.c"

char* Helpers::str_to_md5_wrapper(std::string str)
{
    return str_to_md5(str.c_str());
}

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

void Helpers::create_upload_sub_dir(EUploadDir UploadDir, std::filesystem::path _path)
{
    switch (UploadDir)
    {
    case EUploadDir::Base:
        std::filesystem::create_directory(upload_base_dir() / _path);
        break;
    case EUploadDir::Game:
        std::filesystem::create_directory(upload_games_base_dir() / _path);
        break;
    case EUploadDir::User:
        std::filesystem::create_directory(upload_users_dir() / _path);
        break;
    default:
        return;
    }
}

void Helpers::create_upload_base_dirs()
{
    std::filesystem::create_directory(upload_base_dir());
    std::filesystem::create_directory(upload_games_base_dir());
    std::filesystem::create_directory(upload_users_dir());
}
