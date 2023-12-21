#ifndef HASH_LIB_H
#define HASH_LIB_H

#include "user.h"
#include "tweet.h"

#define USERCOUNT 50
#define TWEETCOUNT 500

struct UserItem {
    User *data;
    int key;
};

struct TweetItem {
    Tweet *data;
    int key;
};

extern struct UserItem *userArray[USERCOUNT];
extern struct TweetItem *tweetArray[TWEETCOUNT];
extern struct UserItem *dummyItem;
extern struct UserItem *item;

int userHashCode(int key);
int tweetHashCode(int key);
int hashCode(struct DataItem* hashArray[], int key);
struct DataItem *search(struct DataItem* hashArray[], int key);
void insert(struct DataItem* hashArray[], int key, User *data);
void insert(struct DataItem* hashArray[], int key, Tweet *data);
struct DataItem *deleteItem(struct DataItem* hashArray[], struct DataItem *item);
void display(struct DataItem* hashArray[]);

#endif // HASH_LIB_H

