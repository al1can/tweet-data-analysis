#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
//#include "tweet.h"

class User {
public:
    std::string username;
    std::string name;
    std::string surname;
    int follower_count;
    int follows_count;
    std::string language;
    std::string region;
    //std::vector<Tweet> tweets;
    std::vector<User> followers;
    std::vector<User> follows;

    User() = default;
    User(std::string username, std::string name, std::string surname, std::string language, std::string region);

    bool operator==(const User& other) const;
    /*
    bool operator==(const User& other) const {
    return username == other.username &&
           name == other.name &&
           surname == other.surname &&
           follower_count == other.follower_count &&
           follows_count == other.follows_count &&
           language == other.language &&
           region == other.region;*/
};

#endif // USER_H

