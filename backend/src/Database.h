#pragma once

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include <iostream>
#include <optional>
#include <vector>

using namespace bsoncxx::builder::stream;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;

namespace Database {
    template <typename T>
    struct is_empty {
        static bool check(const T& obj) {
            return obj == T{};
        }
    };

    struct User {
        bsoncxx::oid id;
        std::string username;
        std::string password;
        std::string profile_image;
        double money;
        std::vector<bsoncxx::oid> games;

        bool operator==(const User& other) const {
            return id == other.id &&
                username == other.username &&
                password == other.password &&
                profile_image == other.profile_image &&
                money == other.money &&
                games == other.games;
        }
    };

    struct Game {
        bsoncxx::oid id;
        double price;
        std::string title;
        std::string short_description;
        std::vector<std::string> long_description;
        std::string preview_img;
        std::vector<std::string> banner_imgs;

        bool operator==(const Game& other) const {
            return id == other.id &&
                   price == other.price &&
                   title == other.title &&
                   short_description == other.short_description &&
                   long_description == other.long_description &&
                   preview_img == other.preview_img &&
                   banner_imgs == other.banner_imgs;
        }
    };

    enum class EPurchaseStatus {
        SUCCESS,
        NOT_ENOUGH_MONEY,
        USER_NOT_FOUND,
        GAME_NOT_FOUND,
        ERROR
    };
}

class MongoManager {

private:
    mongocxx::database _db;

    std::string cleanInput(const std::string& input);

public:
    MongoManager(mongocxx::database database_instance);
    void createIndexes();

    std::optional<bsoncxx::oid> createUser(const Database::User& user);
    Database::User getUserById(const bsoncxx::oid& user_id);
    Database::User getUserByUsername(const std::string& username);

    std::optional<bsoncxx::oid> createGame(const Database::Game& game);
    Database::Game getGameById(const bsoncxx::oid& game_id);
    std::vector<Database::Game> getGames();
    Database::Game updateGameById(const bsoncxx::oid& game_id, const Database::Game &game);
    Database::EPurchaseStatus purchaseGame(const bsoncxx::oid& user_id, const bsoncxx::oid& game_id);

    static bool compare_creds(std::string a, std::string b);
};