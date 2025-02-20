#include "Database.h"

std::string MongoManager::cleanInput(const std::string &input)
{
    if (input.size() >= 2 && input.front() == '"' && input.back() == '"') {
        return input.substr(1, input.size() - 2);
    }
    return input;
}

MongoManager::MongoManager(mongocxx::database database_instance)
{
    _db = database_instance;
}

void MongoManager::createIndexes()
{
    auto users = _db["users"];
    users.create_index(
        make_document(kvp("username", 1)),
        mongocxx::options::index{}.unique(true)
    );

    auto games = _db["games"];
    games.create_index(
        make_document(kvp("title", 1)),
        mongocxx::options::index{}.unique(true)
    );
}

std::optional<bsoncxx::oid> MongoManager::createUser(const Database::User &user)
{
    auto coll = _db["users"];
    auto doc_check = coll.find_one(make_document(kvp("username", cleanInput(user.username))));
        
    try {
        if (!doc_check) {
            bsoncxx::builder::basic::array games_array;
            for (const auto& game_id : user.games) {
                games_array.append(game_id);
            }
            
            auto doc = make_document(
                kvp("username", cleanInput(user.username)),
                kvp("password", cleanInput(user.password)),
                kvp("profile_image", cleanInput(user.profile_image)),
                kvp("money", user.money),
                kvp("games", games_array.view())
            );
            
            auto result = coll.insert_one(doc.view());
            return result ? std::optional<bsoncxx::oid>(result->inserted_id().get_oid().value) : std::nullopt;
        }
        return std::nullopt; 
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error creating user: " << e.what() << std::endl;
        return std::nullopt;
    }
}

Database::User MongoManager::getUserById(const bsoncxx::oid &user_id)
{
    auto coll = _db["users"];
    auto doc = coll.find_one(make_document(kvp("_id", user_id)));
    
    if (!doc) return Database::User{};

    auto view = doc->view();
    Database::User user;
    user.id = view["_id"].get_oid().value;
    user.username = view["username"].get_string().value;
    user.password = view["password"].get_string().value;
    user.profile_image = view["profile_image"].get_string().value;
    user.money = view["money"].get_double().value;
    
    auto games_array = view["games"].get_array().value;
    for (const auto& game : games_array) {
        user.games.push_back(game.get_oid().value);
    }
    
    return user;
}

Database::User MongoManager::getUserByUsername(const std::string &username)
{
    auto coll = _db["users"];
    auto doc = coll.find_one(make_document(kvp("username", username)));
    
    if (!doc) return Database::User{};

    auto view = doc->view();
    Database::User user;
    user.id = view["_id"].get_oid().value;
    user.username = view["username"].get_string().value;
    user.password = view["password"].get_string().value;
    user.profile_image = view["profile_image"].get_string().value;
    user.money = view["money"].get_double().value;
    
    auto games_array = view["games"].get_array().value;
    for (const auto& game : games_array) {
        user.games.push_back(game.get_oid().value);
    }
    
    return user;
}

std::optional<bsoncxx::oid> MongoManager::createGame(const Database::Game &game)
{
    auto coll = _db["games"];
    auto doc_check = coll.find_one(make_document(kvp("title", cleanInput(game.title))));
        
    try {
        if (!doc_check) {
            bsoncxx::builder::basic::array game_long_description_array;
            for (const auto& desc_row : game.long_description) {
                game_long_description_array.append(cleanInput(desc_row));
            }

            bsoncxx::builder::basic::array game_banner_images_array;
            for (const auto& img_path : game.banner_imgs) {
                game_banner_images_array.append(cleanInput(img_path));
            }

            auto doc = make_document(
                kvp("price", game.price),
                kvp("title", cleanInput(game.title)),
                kvp("short_description", cleanInput(game.short_description)),
                kvp("long_description", game_long_description_array),
                kvp("preview_img", cleanInput(game.preview_img)),
                kvp("banner_imgs", game_banner_images_array)
            );
            
            auto result = coll.insert_one(doc.view());
            return result->inserted_id().get_oid().value;
        } else {
            return std::nullopt;
        }
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error creating game: " << e.what() << std::endl;
        return std::nullopt;
    }
}

Database::Game MongoManager::getGameById(const bsoncxx::oid &game_id)
{
    auto coll = _db["games"];
    auto doc = coll.find_one(make_document(kvp("_id", game_id)));
    
    if (!doc) return Database::Game{};

    auto view = doc->view();
    Database::Game game;
    game.id = view["_id"].get_oid().value;
    game.price = view["price"].get_double().value;
    game.title = view["title"].get_string().value;
    game.short_description = view["short_description"].get_string().value;
    
    auto long_desc = view["long_description"].get_array().value;
    for (const auto& item : long_desc) {
        game.long_description.push_back(std::string(item.get_string().value));
    }
    
    game.preview_img = view["preview_img"].get_string().value;
    
    auto banners = view["banner_imgs"].get_array().value;
    for (const auto& banner : banners) {
        game.banner_imgs.push_back(std::string(banner.get_string().value));
    }
    
    return game;
}

Database::Game MongoManager::updateGameById(const bsoncxx::oid &game_id, const Database::Game &game)
{
    auto coll = _db["games"];
    auto doc = coll.find_one(make_document(kvp("_id", game_id)));
    
    if (!doc) return Database::Game{};

    bsoncxx::builder::basic::array game_banner_images_array;
    for (const auto& img_path : game.banner_imgs) {
        game_banner_images_array.append(cleanInput(img_path));
    }

    coll.update_one(
        make_document(kvp("_id", game_id)),
        make_document(
            kvp("$set", make_document(
                kvp("preview_img", cleanInput(game.preview_img)),
                kvp("banner_imgs", game_banner_images_array)
            ))
        )
    );

    return getGameById(game_id);
}

Database::EPurchaseStatus MongoManager::purchaseGame(const bsoncxx::oid &user_id, const bsoncxx::oid &game_id)
{
    try {
        auto user = getUserById(user_id);
        auto game = getGameById(game_id);
        
        if (Database::is_empty<Database::User>::check(user)) return Database::EPurchaseStatus::USER_NOT_FOUND;
        if (Database::is_empty<Database::Game>::check(game)) return Database::EPurchaseStatus::GAME_NOT_FOUND;
        
        if (user.money < game.price) {
            return Database::EPurchaseStatus::NOT_ENOUGH_MONEY;
        }
        
        auto users_coll = _db["users"];
        auto result = users_coll.update_one(
            make_document(kvp("_id", user_id)),
            make_document(
                kvp("$inc", make_document(kvp("money", -game.price))),
                kvp("$push", make_document(kvp("games", game_id)))
            )
        );
        
        return result->modified_count() == 1 
            ? Database::EPurchaseStatus::SUCCESS 
            : Database::EPurchaseStatus::ERROR;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Purchase error: " << e.what() << std::endl;
        return Database::EPurchaseStatus::ERROR;
    }
}

bool MongoManager::compare_creds(std::string a, std::string b)
{
    return a == b;
}
