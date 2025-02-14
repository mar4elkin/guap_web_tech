#include "crow.h"
#include <vector>
#include <string>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(8080).multithreaded().run();
}