#include "Database.h"

void Database::createIndexes()
{
    auto users = db["users"];
    users.create_index(
        make_document(kvp("username", 1)),
        mongocxx::options::index{}.unique(true)
    );

    auto games = db["games"];
    games.create_index(
        make_document(kvp("title", 1)),
        mongocxx::options::index{}.unique(true)
    );
}

std::optional<bsoncxx::oid> Database::createUser(const User &user)
{
    auto coll = db["users"];
        
    try {
        bsoncxx::builder::basic::array games_array;
        for (const auto& game_id : user.games) {
            games_array.append(game_id);
        }
        
        auto doc = make_document(
            kvp("username", user.username),
            kvp("password", user.password),
            kvp("profile_image", user.profile_image),
            kvp("money", user.money),
            kvp("games", games_array.view())
        );
        
        auto result = coll.insert_one(doc.view());
        return result ? std::optional<bsoncxx::oid>(result->inserted_id().get_oid().value) : std::nullopt;

    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error creating user: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<User> Database::getUserById(const bsoncxx::oid &user_id)
{
    auto coll = db["users"];
    auto doc = coll.find_one(make_document(kvp("_id", user_id)));
    
    if (!doc) return std::nullopt;

    auto view = doc->view();
    User user;
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

std::optional<bsoncxx::oid> Database::createGame(const Game &game)
{
    auto coll = db["games"];
        
    try {
        bsoncxx::builder::basic::array game_long_description_array;
        for (const auto& desc_row : game.long_description) {
            game_long_description_array.append(desc_row);
        }

        bsoncxx::builder::basic::array game_banner_images_array;
        for (const auto& img_path : game.banner_imgs) {
            game_banner_images_array.append(img_path);
        }

        auto doc = make_document(
            kvp("price", game.price),
            kvp("title", game.title),
            kvp("short_description", game.short_description),
            kvp("long_description", game_long_description_array),
            kvp("preview_img", game.preview_img),
            kvp("banner_imgs", game_banner_images_array)
        );
        
        auto result = coll.insert_one(doc.view());
        return result->inserted_id().get_oid().value;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error creating game: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<Game> Database::getGameById(const bsoncxx::oid &game_id)
{
    auto coll = db["games"];
    auto doc = coll.find_one(make_document(kvp("_id", game_id)));
    
    if (!doc) return std::nullopt;

    auto view = doc->view();
    Game game;
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

EPurchaseStatus Database::purchaseGame(const bsoncxx::oid &user_id, const bsoncxx::oid &game_id)
{
    try {
        auto user = getUserById(user_id);
        auto game = getGameById(game_id);
        
        if (!user) return EPurchaseStatus::USER_NOT_FOUND;
        if (!game) return EPurchaseStatus::GAME_NOT_FOUND;
        
        if (user->money < game->price) {
            return EPurchaseStatus::NOT_ENOUGH_MONEY;
        }
        
        auto users_coll = db["users"];
        auto result = users_coll.update_one(
            make_document(kvp("_id", user_id)),
            make_document(
                kvp("$inc", make_document(kvp("money", -game->price))),
                kvp("$push", make_document(kvp("games", game_id)))
            )
        );
        
        return result->modified_count() == 1 
            ? EPurchaseStatus::SUCCESS 
            : EPurchaseStatus::ERROR;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Purchase error: " << e.what() << std::endl;
        return EPurchaseStatus::ERROR;
    }
}
