#pragma once

#include <random>
#include <string>
#include <cstring>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <filesystem>

enum class EUploadDir { Base, Game, User };

class Helpers {
    public:
        static char* str_to_md5_wrapper(std::string str);
        static std::string uuid();
        static std::string timestamp_uuid(std::string file_ext="");
        static void create_upload_sub_dir(EUploadDir UploadDir, std::filesystem::path _path);
        static void create_upload_base_dirs();
        static std::string path_to_url(uint16_t port, std::filesystem::path full_path);

        // 4:59 AM
        static inline std::filesystem::path upload_base_dir() { 
            return std::filesystem::path(std::filesystem::canonical("/proc/self/exe").parent_path() / "upload");
        };
        static inline std::filesystem::path upload_users_dir() {
             return std::filesystem::path(std::filesystem::path(upload_base_dir()) / "user");
        };
        static inline std::filesystem::path upload_games_base_dir() { 
            return std::filesystem::path(std::filesystem::path(upload_base_dir()) / "games");
        };
    };