#include "user.cpp"

int main() {
    User user1("john_doe", "John", "Doe", "English", "US");
    
    user1.tweets.push_back("Hello, Twitter!");
    user1.tweets.push_back("I'm tweeting!");

}
