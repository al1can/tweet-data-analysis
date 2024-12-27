#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string name;
    std::string surname;
    int followerCount;
    int followsCount;
    std::string language;
    std::string region;

    struct std::hash<User>;

    User() = default;
    User(std::string username, std::string name, std::string surname, std::string language, std::string region);

    bool operator==(const User& other) const;
};

#endif // USER_H

