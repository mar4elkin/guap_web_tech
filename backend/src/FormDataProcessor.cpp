#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "FormDataProcessor.h"

void FormDataProcessor::username(std::string field_name)
{
    auto it = _view.part_map.find(field_name);
    if (it != _view.part_map.end()) {
        _object[field_name] = std::string(it->second.body);
    }
}

void FormDataProcessor::password(std::string field_name)
{
    auto it = _view.part_map.find(field_name);
    if (it != _view.part_map.end()) {

        std::string password = std::string(it->second.body);
        char* hash = Helpers::str_to_md5_wrapper(password.c_str());
        _object[field_name] = hash;
        free(hash);
    }
}

void FormDataProcessor::image(std::string field_name, std::filesystem::path image_base_path)
{
    auto it = _view.part_map.find(field_name);
    if (it != _view.part_map.end()) {

        auto headers_it = it->second.headers.find("Content-Disposition");
        if (headers_it == it->second.headers.end())
        {
            //return crow::response(400);
            return;
        }

        auto params_it = headers_it->second.params.find("filename");
        if (params_it == headers_it->second.params.end())
        {
            //return crow::response(400);
            return;
        }

        const auto image_path = image_base_path / Helpers::timestamp_uuid(".jpg");
        std::ofstream out_file(image_path);

        _object[field_name] = Helpers::path_to_url(1488, std::string(image_path));

        out_file << it->second.body;
        out_file.close();

        std::thread([image_path]() {
            int width, height, channels;
            unsigned char* img = stbi_load(image_path.c_str(), &width, &height, &channels, 4);

            // if (!img) {
            //     CROW_LOG_ERROR << "Failed to load image: " << image_path;
            // }
            
            stbi_write_jpg(image_path.c_str(), width, height, 4, img, 75);
            stbi_image_free(img);

            //CROW_LOG_INFO << "Image processed: " << image_path;
        }).detach();
    }
}

void FormDataProcessor::banner_images(std::string prefix, std::filesystem::path image_base_path)
{
    for (const auto& part : _view.part_map) {
        const auto& _field_name = std::string(part.first); 
        if (_field_name.starts_with(prefix)) {
            image(_field_name, image_base_path);
        }
    }
}

std::vector<std::string> FormDataProcessor::banner_images_keys(std::string prefix)
{
    std::vector<std::string> keys;
    for (const auto& part : _view.part_map) {
        const auto& _field_name = std::string(part.first); 
        if (_field_name.starts_with(prefix)) {
            keys.push_back(std::string(_field_name));
        }
    }
    return keys;
}
