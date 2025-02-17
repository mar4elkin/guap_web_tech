#pragma once

#include "helpers.h"
#include "crow.h"
#include <thread>
#include <string>
#include <functional>
#include <filesystem>
#include "str_to_md5.h"

class FormDataProcessor {
public:
    explicit FormDataProcessor(crow::multipart::message_view& view, crow::json::wvalue& object)
    : _view(view), _object(object) {}

    void username(std::string field_name);
    void password(std::string field_name);
    void image(std::string field_name, std::filesystem::path image_base_path);
    void banner_images(std::string prefix, std::filesystem::path image_base_path);

private:
    crow::json::wvalue& _object;
    const crow::multipart::message_view& _view;
};