#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "crow.h"
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <thread>
#include <cstring>

#include "md5_imp.c"
#include "helpers.h"

int main() 
{
    Helpers::create_upload_base_dirs();
    crow::SimpleApp app;

    //CROW_ROUTE(app, "/user/singin")

    CROW_ROUTE(app, "/user/singup")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
        crow::multipart::message_view file_message(req);
        crow::json::wvalue response;

        for (const auto& part : file_message.part_map)
        {
            const auto& part_name = part.first;
            const auto& part_value = part.second;
            
            if ("username" == part_name) 
            {
                response["username"] = std::string(part_value.body);
            }

            if ("password" == part_name) 
            {
                auto password = std::string(part_value.body);
                // DO NOT FORGET ABOUT FREE
                auto hash = str_to_md5(password.c_str());
                response["password"] = hash;
                free(hash);
            }

            if ("profile_image" == part_name)
            {
                auto headers_it = part_value.headers.find("Content-Disposition");
                if (headers_it == part_value.headers.end())
                {
                    return crow::response(400);
                }
                auto params_it = headers_it->second.params.find("filename");
                if (params_it == headers_it->second.params.end())
                {
                    return crow::response(400);
                }
                const auto image_path = Helpers::upload_users_dir() / Helpers::timestamp_uuid(".jpg");
                std::ofstream out_file(image_path);

                if (!out_file)
                {
                    CROW_LOG_ERROR << " Write to file failed\n";
                    continue;
                }

                out_file << part_value.body;
                out_file.close();

                std::thread([image_path]() {
                    int width, height, channels;
                    unsigned char* img = stbi_load(image_path.c_str(), &width, &height, &channels, 4);
                    if (!img) {
                        CROW_LOG_ERROR << "Failed to load image: " << image_path;
                        return;
                    }
                    
                    stbi_write_jpg(image_path.c_str(), width, height, 4, img, 75);
                    stbi_image_free(img);
    
                    CROW_LOG_INFO << "Image processed: " << image_path;
                }).detach();
            }
        }
        response["message"] = "Received data successfully!";
        return crow::response(response);
    });

    //CROW_ROUTE(app, "/game/<int>")

    // anyone can add a game, but it doesn't matter much for this project
    CROW_ROUTE(app, "/game")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400);
        }

        // body["price"];
        // body["text"]["title"];
        // body["text"]["shortDescription"];
        // body["text"]["longDescription"];

    });

    // CROW_ROUTE(app, "/game/<int>/images")
    // .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
    //     crow::multipart::message_view file_message(req);
    //     crow::json::wvalue response;

    //     for (const auto& part : file_message.part_map)
    //     {
    //         const auto& part_name = part.first;
    //         const auto& part_value = part.second;

    //         if ("preview_img" == part_name)
    //         {
    //             auto headers_it = part_value.headers.find("Content-Disposition");
    //             if (headers_it == part_value.headers.end())
    //             {
    //                 return crow::response(400);
    //             }
    //             auto params_it = headers_it->second.params.find("filename");
    //             if (params_it == headers_it->second.params.end())
    //             {
    //                 return crow::response(400);
    //             }
    //             const auto image_path = upload_dir_path / Helpers::timestamp_uuid(".jpg");
    //             std::ofstream out_file(image_path);

    //             if (!out_file)
    //             {
    //                 CROW_LOG_ERROR << " Write to file failed\n";
    //                 continue;
    //             }

    //             out_file << part_value.body;
    //             out_file.close();

    //             std::thread([image_path]() {
    //                 int width, height, channels;
    //                 unsigned char* img = stbi_load(image_path.c_str(), &width, &height, &channels, 4);
    //                 if (!img) {
    //                     CROW_LOG_ERROR << "Failed to load image: " << image_path;
    //                     return;
    //                 }
                    
    //                 stbi_write_jpg(image_path.c_str(), width, height, 4, img, 75);
    //                 stbi_image_free(img);
    
    //                 CROW_LOG_INFO << "Image processed: " << image_path;
    //             }).detach();
    //         }
    //     }
    //     response["message"] = "Received data successfully!";
    //     return crow::response(response);
    // });

    CROW_ROUTE(app, "/")([](){
        crow::json::wvalue response;
        response["message"] = "Received data successfully!";
        response["name"] = "name";
        response["age"] = 123;
        return crow::response(response);
    });

    app.port(1488).multithreaded().run();
}