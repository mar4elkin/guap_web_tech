#include "crow.h"
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <cstring>
#include "Database.h"
#include "helpers.h"
#include "str_to_md5.h"
#include "FormDataProcessor.h"

int main() 
{
    Helpers::create_upload_base_dirs();
    crow::SimpleApp app;

    CROW_ROUTE(app, "/user/singin")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::json::wvalue res_object;

        body["username"];
        body["password"]; //str_to_md5

        res_object["message"] = "Received data successfully!";
        return crow::response(res_object);
    });

    CROW_ROUTE(app, "/user/singup")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
        crow::multipart::message_view form_data(req);
        crow::json::wvalue res_object;

        FormDataProcessor processor = FormDataProcessor(form_data, res_object);
        processor.username("username");
        processor.password("password");
        processor.image("profile_image", Helpers::upload_users_dir());

        res_object["message"] = "Received data successfully!";
        return crow::response(res_object);
    });

    CROW_ROUTE(app, "/game/<int>")([&](int index) {
        crow::json::wvalue res_object;
        res_object["message"] = "Received data successfully!";
        return crow::response(res_object);
    });

    // anyone can add a game, but it doesn't matter much for this project
    CROW_ROUTE(app, "/game/create")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::json::wvalue response;

        if (!body) {
            return crow::response(400);
        }

        response["price"] = body["price"];
        response["text"]["title"] = body["text"]["title"];
        response["text"]["shortDescription"] = body["text"]["shortDescription"];
        response["text"]["longDescription"] = body["text"]["longDescription"];

        // auto items = body["text"]["longDescription"];

        // if (items.t() == crow::json::type::List) {
        //     for (const auto& item : items) {
        //         CROW_LOG_INFO << item;
        //     }
        // }

        return crow::response(response);
    });

    CROW_ROUTE(app, "/game/<int>/images")
    .methods(crow::HTTPMethod::Post)([&](const crow::request& req, int index) {
        crow::multipart::message_view form_data(req);
        crow::json::wvalue res_object;

        FormDataProcessor processor = FormDataProcessor(form_data, res_object);
        processor.image("preview_img", Helpers::upload_games_base_dir());
        processor.banner_images("banner_img_", Helpers::upload_games_base_dir());

        res_object["message"] = "Received data successfully!";
        return crow::response(res_object);
    });

    CROW_ROUTE(app, "/")([](){
        crow::json::wvalue response;
        response["message"] = "Received data successfully!";
        return crow::response(response);
    });

    app.port(1488).multithreaded().run();
}