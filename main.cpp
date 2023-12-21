#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "user.h"
#include "tweet.h"
#include "hashLib.h"
#include "graphLib.h"
#include "faker-cxx/Person.h"

#define USERCOUNT 50
#define TWEETCOUNT 500

struct HashTable<User, USERCOUNT> userHashTable;
struct HashTable<Tweet, TWEETCOUNT> tweetHashTable;
Graph<User> userGraph(1000); 

std::string strip(const std::string& str) {
    size_t firstNonSpace = str.find_first_not_of(" \t");
    size_t lastNonSpace = str.find_last_not_of(" \t");

    if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
        return str.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    }

    // If the string is empty or consists of whitespaces only, return an empty string
    return "";
}

int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max - 1);

    return distribution(gen);
}

int main() {
        for(int i = 0; i < USERCOUNT; i++) {
	        std::string firstName = faker::Person::firstName();
	        std::string lastName = faker::Person::lastName();
	        std::string language = "english";
	        std::string region = "Europe";
   	        User user = User(firstName, firstName, lastName, language, region);
		userHashTable.insert(i, user);
		userGraph.addVertex(user);
        }
	
	std::ifstream inputFile("../data/file_names.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    int tweetIndex = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::ifstream inputFile1("../data/" + line);

        if (!inputFile1.is_open()) {
            std::cerr << "Error opening the file." << std::endl;
            return 1;
        }

        std::string line1;
        while (std::getline(inputFile1, line1)) {
            // Use the strip function to get the non-empty part of the line
            std::string nonEmptyPart = strip(line1);

            // Check if the line is not empty
            if (!nonEmptyPart.empty()) {
                // Print the non-empty part
                //std::cout << tweetIndex << nonEmptyPart << std::endl;

                // Uncomment the following lines when needed
                Tweet tweet = Tweet(nonEmptyPart);
                tweetHashTable.insert(tweetIndex, tweet);
                // std::cout << tweetIndex << "\n";
                tweetIndex++;
            }
        }

        inputFile1.close();
    }

    int allah = 0;
    for (int i=0; i<USERCOUNT; i++) {
       int randomNumber = getRandomNumber(0, USERCOUNT);
       for (int j=0; j<randomNumber; j++) {
           int randomUserIndex = getRandomNumber(0, USERCOUNT);
	   //userHashTable.search(i)->followers.push_back(userHashTable.search(randomUserIndex));
	   std::cout << randomUserIndex << std::endl;
           std::cout << userHashTable.search(i)->data.name << std::endl;
           std::cout << userHashTable.search(randomUserIndex)->data.name << std::endl;
	   std::cout << "-----end-----" << std::endl;
	   userGraph.addEdge(userHashTable.search(i)->data, userHashTable.search(randomUserIndex)->data);
	   allah++;
       }
       //randomNumber = getRandomNumber(0, USERCOUNT);
       //for (int j=0; j<randomNumber; j++) {
           //int randomUserIndex = getRandomNumber(0, USERCOUNT);
           //userHashTable.search(i)->follows.push_back(userHashTable.search(randomUserIndex));i
	   //userGraph.addEdge(userHashTable.search(i)->data, userHashTable.search(randomUserIndex)->data);
       //}

    }

    inputFile.close();
    std::cout << "-----UserHashTable-----" << std::endl;	
    userHashTable.display();
    std::cout << "-----TweetHashTable-----" << std::endl;
    tweetHashTable.display();
    std::cout << "-----UserGrap-----" << std::endl;
    userGraph.printGraph();
}
