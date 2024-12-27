#ifndef TWEET_H
#define TWEET_H

#include <string>
#include "user.h"

class Tweet {
public:
    std::string text;
    User* user;

    struct std::hash<Tweet>;

    Tweet() {}
    Tweet(std::string text, User* user);

};

#endif // TWEET_H

