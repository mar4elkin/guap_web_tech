#include "Database.h"

void Database::createTables()
{
    try {
        pqxx::work txn(conn);
        
        txn.exec(
            "CREATE TABLE IF NOT EXISTS Users ("
            "id SERIAL PRIMARY KEY,"
            "username VARCHAR(255) UNIQUE NOT NULL,"
            "password VARCHAR(255) NOT NULL,"
            "profile_image TEXT,"
            "money INTEGER DEFAULT 0);"
            
            "CREATE TABLE IF NOT EXISTS Games ("
            "id SERIAL PRIMARY KEY,"
            "price INTEGER NOT NULL,"
            "title VARCHAR(255) UNIQUE NOT NULL,"
            "short_description TEXT NOT NULL,"
            "long_description TEXT NOT NULL,"
            "preview_img TEXT NOT NULL,"
            "banner_imgs TEXT[] NOT NULL);"
            
            "CREATE TABLE IF NOT EXISTS UserGames ("
            "user_id INTEGER REFERENCES Users(id) ON DELETE CASCADE,"
            "game_id INTEGER REFERENCES Games(id) ON DELETE CASCADE,"
            "PRIMARY KEY (user_id, game_id));"
            
            "CREATE INDEX IF NOT EXISTS idx_user_games ON UserGames(user_id);"
        );
        
        txn.commit();
    } catch (const std::exception& e) {
        throw std::runtime_error("Error creating tables: " + std::string(e.what()));
    }
}

std::optional<User> Database::createUser(const User &user)
{
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "INSERT INTO Users (username, password, profile_image, money) "
            "VALUES ($1, $2, $3, $4) RETURNING *",
            user.username, user.password, user.profile_image, user.money
        );
        txn.commit();

        return User{
            result["id"].as<int>(),
            result["username"].as<std::string>(),
            result["password"].as<std::string>(),
            result["profile_image"].as<std::string>(),
            result["money"].as<int>(),
            {}
        };
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<User> Database::getUserById(int userId)
{
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "SELECT id, username, password, profile_image, money "
            "FROM Users WHERE id = $1",
            userId
        );
        
        if (result.empty()) return std::nullopt;
        
        auto row = result[0];
        return User{
            row["id"].as<int>(),
            row["username"].as<std::string>(),
            row["password"].as<std::string>(),
            row["profile_image"].as<std::string>(),
            row["money"].as<int>()
        };
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<User> Database::addGameToUser(int userId, int gameId)
{
    try {
        pqxx::work txn(conn);
        
        auto game_result = txn.exec_params1(
            "SELECT price FROM Games WHERE id = $1", 
            gameId
        );
        auto user_result = txn.exec_params1(
            "SELECT money FROM Users WHERE id = $1 FOR UPDATE", 
            userId
        );

        int current_balance = user_result["money"].as<int>();
        int game_price = game_result["price"].as<int>();

        if(current_balance < game_price) {
            txn.abort();
            return std::nullopt;
        }

        txn.exec_params1(
            "UPDATE Users SET money = money - $1 WHERE id = $2",
            game_price,
            userId
        );
        
        txn.exec_params1(
            "INSERT INTO UserGames (user_id, game_id) VALUES ($1, $2) "
            "ON CONFLICT DO NOTHING",
            userId, 
            gameId
        );

        txn.commit();
        
        return getUserById(userId);
    } 
    catch (const pqxx::unexpected_rows&) {
        return std::nullopt;
    }
    catch (...) {
        return std::nullopt;
    }
}

std::optional<User> Database::updateUser(const User& user) {
    try {
        pqxx::work txn(conn);
        txn.exec_params1(
            "UPDATE Users SET "
            "username = $1, password = $2, profile_image = $3, money = $4 "
            "WHERE id = $5",
            user.username,
            user.password,
            user.profile_image,
            user.money,
            user.id
        );
        txn.commit();
        return getUserById(user.id);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<std::vector<Game>> Database::getUserGames(int userId) {
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "SELECT g.* FROM Games g "
            "JOIN UserGames ug ON g.id = ug.game_id "
            "WHERE ug.user_id = $1",
            userId
        );

        std::vector<Game> games;
        for (const auto& row : result) {
            Game game;
            game.id = row["id"].as<int>();
            game.price = row["price"].as<int>();
            game.title = row["title"].as<std::string>();
            game.shortDescription = row["short_description"].as<std::string>();
            game.longDescription = row["long_description"].as<std::string>();
            game.preview_img = row["preview_img"].as<std::string>();
            
            auto arr = row["banner_imgs"].as_array();
            for (auto elem : arr) {
                game.banner_imgs.push_back(elem);
            }
            
            games.push_back(game);
        }
        return games;
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<Game> Database::createGame(const Game &game) {
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "INSERT INTO Games (price, title, short_description, "
            "long_description, preview_img, banner_imgs) "
            "VALUES ($1, $2, $3, $4, $5, $6) "
            "RETURNING *",
            game.price,
            game.title,
            game.shortDescription,
            game.longDescription,
            game.preview_img,
            pqxx::array(game.banner_imgs)
        );

        return Game{
            result["id"].as<int>(),
            result["price"].as<int>(),
            result["title"].as<std::string>(),
            result["short_description"].as<std::string>(),
            result["long_description"].as<std::string>(),
            result["preview_img"].as<std::string>(),
            pqxx::to_vector<std::string>(result["banner_imgs"])
        };
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<Game> Database::getGameByTitle(const std::string &title) {
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "SELECT * FROM Games WHERE title = $1",
            title
        );
        
        if (result.empty()) return std::nullopt;
        
        auto row = result[0];
        return Game{
            row["id"].as<int>(),
            row["price"].as<int>(),
            row["title"].as<std::string>(),
            row["short_description"].as<std::string>(),
            row["long_description"].as<std::string>(),
            row["preview_img"].as<std::string>(),
            pqxx::to_vector<std::string>(row["banner_imgs"])
        };
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<Game> Database::getGameById(int gameId) {
    try {
        pqxx::work txn(conn);
        auto result = txn.exec_params1(
            "SELECT * FROM Games WHERE id = $1",
            gameId
        );
        
        if (result.empty()) return std::nullopt;
        
        auto row = result[0];
        return Game{
            row["id"].as<int>(),
            row["price"].as<int>(),
            row["title"].as<std::string>(),
            row["short_description"].as<std::string>(),
            row["long_description"].as<std::string>(),
            row["preview_img"].as<std::string>(),
            pqxx::to_vector<std::string>(row["banner_imgs"])
        };
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<Game> Database::updateGame(const Game &game) {
    try {
        pqxx::work txn(conn);
        txn.exec_params1(
            "UPDATE Games SET "
            "price = $1, title = $2, short_description = $3, "
            "long_description = $4, preview_img = $5, banner_imgs = $6 "
            "WHERE id = $7",
            game.price,
            game.title,
            game.shortDescription,
            game.longDescription,
            game.preview_img,
            pqxx::array(game.banner_imgs),
            game.id
        );
        txn.commit();
        return getGameById(game.id);
    } catch (...) {
        return std::nullopt;
    }
}
