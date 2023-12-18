#include <iostream>
#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string name;
    std::string surname;
    int follower_count;
    int follows_count;
    std::string language;
    std::string region;
    std::vector<std::string> tweets;
    std::vector<User*> followers;
    std::vector<User*> follows;

    User(std::string username, std::string name, std::string surname, std::string language, std::string region)
        : username(username), name(name), surname(surname), language(language), region(region),
          follower_count(0), follows_count(0) {}

};
