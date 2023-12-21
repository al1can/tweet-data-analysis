#include "user.h"

// Implement member functions here
User::User(std::string username, std::string name, std::string surname, std::string language, std::string region)
    : username(username), name(name), surname(surname), language(language), region(region),
      follower_count(0), follows_count(0) {
    // Initialize other members as needed
}

bool User::operator==(const User& other) const {
    return username == other.username &&
           name == other.name &&
           surname == other.surname &&
           follower_count == other.follower_count &&
           follows_count == other.follows_count &&
           language == other.language &&
           region == other.region;
}

