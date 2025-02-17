#pragma once

#include <pqxx/pqxx>
#include <optional>
#include <vector>
#include <string>
#include <algorithm>

struct User {
    int id;
    std::string username;
    std::string password;
    std::string profile_image;
    int money;
    std::vector<int> games;
};

struct Game {
    int id;
    int price;
    std::string title;
    std::string shortDescription;
    std::string longDescription;
    std::string preview_img;
    std::vector<std::string> banner_imgs;
};

class Database {

private:
    pqxx::connection conn;

    void createTables();

public:
    Database(const std::string& conn_str = "postgresql://user:pass@localhost/gamedb")
        : conn(conn_str) {
        createTables();
    }

    // users
    std::optional<User> createUser(const User& user);
    std::optional<User> getUserById(int userId);
    std::optional<User> addGameToUser(int userId, int gameId);
    std::optional<User> updateUser(const User& user);
    std::optional<std::vector<Game>> getUserGames(int userId);

    // games
    std::optional<Game> createGame(const Game& game);
    std::optional<Game> getGameByTitle(const std::string& title);
    std::optional<Game> getGameById(int gameId);
    std::optional<Game> updateGame(const Game& game);

};