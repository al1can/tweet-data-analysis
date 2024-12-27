#include "user.h"

User::User(std::string username, std::string name, std::string surname, std::string language, std::string region)
    : username(username), name(name), surname(surname), language(language), region(region),
      followerCount(0), followsCount(0) {
}

bool User::operator==(const User& other) const {
    return username == other.username &&
           name == other.name &&
           surname == other.surname &&
           followerCount == other.followerCount &&
           followsCount == other.followsCount &&
           language == other.language &&
           region == other.region;
}

