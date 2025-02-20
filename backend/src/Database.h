#pragma once

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include <optional>
#include <vector>

using namespace bsoncxx::builder::stream;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;

struct User {
    bsoncxx::oid id;
    std::string username;
    std::string password;
    std::string profile_image;
    double money;
    std::vector<bsoncxx::oid> games;
};

struct Game {
    bsoncxx::oid id;
    double price;
    std::string title;
    std::string short_description;
    std::vector<std::string> long_description;
    std::string preview_img;
    std::vector<std::string> banner_imgs;
};

enum class EPurchaseStatus {
    SUCCESS,
    NOT_ENOUGH_MONEY,
    USER_NOT_FOUND,
    GAME_NOT_FOUND,
    ERROR
};

class Database {

private:
    mongocxx::instance instance;
    mongocxx::client client;
    mongocxx::database db;
public:
    Database(const std::string& uri, const std::string& db_name): client{mongocxx::uri{uri}}, db{client[db_name]} 
    {
        createIndexes();
    }

    void createIndexes();

    std::optional<bsoncxx::oid> createUser(const User& user);
    std::optional<User> getUserById(const bsoncxx::oid& user_id);

    std::optional<bsoncxx::oid> createGame(const Game& game);
    std::optional<Game> getGameById(const bsoncxx::oid& game_id);
    EPurchaseStatus purchaseGame(const bsoncxx::oid& user_id, const bsoncxx::oid& game_id);
};