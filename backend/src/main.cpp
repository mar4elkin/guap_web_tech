#include "crow.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <cstring>
#include "Helpers.h"
#include "FormDataProcessor.h"
#include <bsoncxx/oid.hpp>
#include "Database.h"

int main() 
{
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://127.0.0.1:27017/"}};
    auto db = conn["guap_db"];

    Helpers::create_upload_base_dirs();
    crow::SimpleApp app;

    CROW_ROUTE(app, "/user/singin")
    .methods(crow::HTTPMethod::Post)([&, db](const crow::request& req) {
        auto body = crow::json::load(req.body);
        crow::json::wvalue res_object;

        //bsoncxx::oid body_id{std::string(body["_id"])};
        auto body_username = std::string(body["username"]);
        auto body_password = std::string(
            Helpers::str_to_md5_wrapper(
                std::string(body["password"])
            )
        );

        MongoManager manager_db(db);
        auto db_user = manager_db.getUserByUsername(body_username);

        if (!Database::is_empty<Database::User>::check(db_user)) {
            if (MongoManager::compare_creds(db_user.username, body_username) == MongoManager::compare_creds(db_user.password, body_password)) {
                res_object["_id"] = db_user.id.to_string();
                res_object["username"] = db_user.username;
                res_object["password"] = db_user.password;
                res_object["profile_image"] = db_user.profile_image;
                res_object["status"] = "ok";
                return crow::response(res_object);
            } else {
                crow::json::wvalue res_object_err;
                res_object_err["status"] = "error";
                return crow::response(res_object_err);
            }
        } else {
            crow::json::wvalue res_object_err;
            res_object_err["status"] = "error";
            return crow::response(res_object_err);
        }
    });

    CROW_ROUTE(app, "/user/singup")
    .methods(crow::HTTPMethod::Post)([&, db](const crow::request& req) {
        crow::multipart::message_view form_data(req);
        crow::json::wvalue res_object;

        FormDataProcessor processor = FormDataProcessor(form_data, res_object);
        processor.username("username");
        processor.password("password");
        processor.image("profile_image", Helpers::upload_users_dir());

        Database::User new_user{
            {},
            res_object["username"].dump(),
            res_object["password"].dump(),
            res_object["profile_image"].dump(),
            15000.0,
            {}
        };
        
        MongoManager manager_db(db);
        auto user_id = manager_db.createUser(new_user);

        if (user_id.has_value()) {
            res_object["_id"] = user_id->to_string();
            res_object["status"] = "ok";
            return crow::response(res_object);
        } else {
            crow::json::wvalue res_object_err;
            res_object_err["status"] = "error";
            return crow::response(res_object_err);
        }
    });

    // very unsafe, not for prod
    CROW_ROUTE(app, "/static/<string>/<string>")
    ([](std::string maindir, std::string filename) {
        std::filesystem::path path = Helpers::upload_base_dir() / maindir / (filename + ".jpg");

        std::ifstream file(path, std::ios::binary);

        if (!file) {
            return crow::response(404, "File not found");
        }

        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::string file_content(buffer.begin(), buffer.end());

        crow::response res;
        res.code = 200;
        res.set_header("Content-Type", "image/jpeg");
        res.body = std::move(file_content); 
        res.set_header("Content-Length", std::to_string(res.body.size()));

        return res;
    });

    CROW_ROUTE(app, "/games")([&, db]() {
        crow::json::wvalue response;
        
        MongoManager manager_db(db);
        auto db_games = manager_db.getGames();

        std::vector<crow::json::wvalue> games_list;
        for (const Database::Game& db_game : db_games) {
            crow::json::wvalue game;
            game["price"] = db_game.price;
            game["text"]["title"] = db_game.title;
            game["text"]["shortDescription"] = db_game.short_description;
            game["img"]["previewImg"] = db_game.preview_img;
            game["img"]["bannerImgs"] = db_game.banner_imgs;
            
            games_list.push_back(std::move(game));
        }
        
        response["games"] = std::move(games_list);

        return crow::response(response);
    });

    CROW_ROUTE(app, "/game/<str>")([&, db](std::string index) {
        crow::json::wvalue response;
        
        bsoncxx::oid _id {index};
        MongoManager manager_db(db);
        auto db_game = manager_db.getGameById(_id);

        response["_id"] = index;
        response["price"] = db_game.price;
        response["text"]["title"] = db_game.title;
        response["text"]["shortDescription"] = db_game.short_description;
        response["img"]["previewImg"] = db_game.preview_img;
        response["img"]["bannerImgs"] = db_game.banner_imgs;

        return crow::response(response);
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

        auto description_items_raw = body["text"]["longDescription"];
        std::vector<std::string> description_items;

        // auto items = body["text"]["longDescription"];

        // if (items.t() == crow::json::type::List) {
        //     for (const auto& item : items) {
        //         CROW_LOG_INFO << item;
        //     }
        // }

        if (description_items_raw.t() == crow::json::type::List) {
            for (const auto& item : description_items_raw) {
                description_items.push_back(std::string(item));
            }
        }

        Database::Game new_game{
            {},
            std::stod(std::string(response["price"].dump())),
            response["text"]["title"].dump(),
            response["text"]["shortDescription"].dump(),
            description_items,
            "",
            {}
        };

        MongoManager manager_db(db);
        auto game_id = manager_db.createGame(new_game);

        if (game_id.has_value()) {
            response["status"] = "ok";
            response["_id"] = game_id->to_string();
            return crow::response(response);
        } else {
            crow::json::wvalue response_err;
            response_err["status"] = "error";
            return crow::response(response_err);
        }
    });

    CROW_ROUTE(app, "/game/<str>/images")
    .methods(crow::HTTPMethod::Post)([&, db](const crow::request& req, std::string index) {
        crow::multipart::message_view form_data(req);
        crow::json::wvalue response;
        crow::json::wvalue response_error;

        FormDataProcessor processor = FormDataProcessor(form_data, response);
        processor.image("preview_img", Helpers::upload_games_base_dir());
        processor.banner_images("banner_img_", Helpers::upload_games_base_dir());
        
        CROW_LOG_INFO << response["preview_img"].dump();

        std::vector<std::string> banner_imgs;
        for (auto k: processor.banner_images_keys("banner_img_")) {
            banner_imgs.push_back(response[k].dump());
            CROW_LOG_INFO << response[k].dump();
        }

        Database::Game update_game{
            {}, 
            0, 
            "", 
            "", 
            {}, 
            std::string(response["preview_img"].dump()), 
            banner_imgs
        };

        bsoncxx::oid _id {index};
        MongoManager manager_db(db);
        auto updated_game = manager_db.updateGameById(_id, update_game);

        if (!Database::is_empty<Database::Game>::check(updated_game)) {
            response["status"] = "ok";
            return crow::response(response);
        } else {
            response_error["status"] = "error";
            return crow::response(response_error);
        }
        return crow::response(response_error);
    });

    app.port(1488).multithreaded().run();
}