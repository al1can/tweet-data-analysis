#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <regex>
#include "user.h"
#include "tweet.h"
#include "hashLib.h"
#include "graphLib.h"
#include "faker-cxx/Person.h"
#include "faker-cxx/Location.h"

#define USERCOUNT 100
#define TWEETCOUNT 1000
	
struct HashTable<User, int, USERCOUNT> userHashTable;
struct HashTable<Tweet, int, TWEETCOUNT> tweetHashTable;
struct HashTable<Tweet, int, 200> astronomyTweets;
struct HashTable<Tweet, int, 200> gamingTweets;
struct HashTable<Tweet, int, 200> movieTweets;
struct HashTable<Tweet, int, 200> programmingTweets;
struct HashTable<Tweet, int, 200> readingTweets;
struct HashTable<Tweet, int, 200> artTweets;
struct HashTable<Tweet, int, 200> racingTweets;
struct HashTable<Tweet, int, 200> fashionTweets;
struct HashTable<Tweet, int, 200> vacationTweets;
struct HashTable<Tweet, int, 200> scienceTweets;
struct HashTable<std::string, std::string, 2100> hashTagTable;
Graph<User> userGraph(2000); 

std::ofstream outputFile("output.txt", std::ofstream::app);

std::string strip(const std::string& str) {
    size_t firstNonSpace = str.find_first_not_of(" \t\r\n");
    size_t lastNonSpace = str.find_last_not_of(" \t\r\n");

    if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
        return str.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    }

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
		std::string region = faker::Location::country();
	        //std::string region = "Europe";
   	        User* user = new User(firstName, firstName, lastName, language, region);
		userHashTable.insert(i, user);
		userGraph.addVertex(user);
        }

	std::ifstream inputFile("../data/file_names.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Dosya acilamadi." << std::endl;
        return 1;
    }

    int tweetIndex = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::ifstream inputFile1("../data/" + line);

        if (!inputFile1.is_open()) {
            std::cerr << "Dosya acilamadi." << std::endl;
            return 1;
        }

        std::string line1;
        while (std::getline(inputFile1, line1)) {
            std::string nonEmptyPart = strip(line1);

            if (!nonEmptyPart.empty()) {
		int randomUserIndex = getRandomNumber(0, USERCOUNT);
		User* randomUser = userHashTable.search(randomUserIndex)->data;
                //std::cout << tweetIndex << nonEmptyPart << std::endl;
                Tweet* tweet = new Tweet(nonEmptyPart, randomUser);
                tweetHashTable.insert(tweetIndex, tweet);
                tweetIndex++;
                //std::cout << tweetIndex << "\n";
            }
        }
        inputFile1.close();
        
    }

    for (int i=0; i<USERCOUNT; i++) {
       int randomNumber = getRandomNumber(0, USERCOUNT);
       for (int j=0; j<randomNumber; j++) {
           int randomUserIndex = getRandomNumber(0, USERCOUNT);
	   userGraph.addEdge(userHashTable.search(i)->data, userHashTable.search(randomUserIndex)->data);
	   userHashTable.search(i)->data->followsCount++;
	   userHashTable.search(randomUserIndex)->data->followerCount++;
       }
    }

    int astronomyIndex = 0, gamingIndex = 0, movieIndex = 0, programmingIndex = 0, readingIndex = 0, artIndex = 0, fashionIndex = 0, scienceIndex = 0, racingIndex = 0, vacationIndex = 0;

    for (int i=0; i<TWEETCOUNT; i++) {
	    std::string text = tweetHashTable.search(i)->data->text;
	    //std::cout << i << std::endl;
	    if (text.find("astronomy") != std::string::npos || text.find("Astronomy") != std::string::npos || text.find("cosmic") != std::string::npos) {
 		    astronomyTweets.insert(astronomyIndex, tweetHashTable.search(i)->data);
		    astronomyIndex++;
	    } else if (text.find("gaming") != std::string::npos || text.find("Gaming") != std::string::npos) {
 		    gamingTweets.insert(gamingIndex, tweetHashTable.search(i)->data);
		    gamingIndex++;
	    } else if (text.find("movie") != std::string::npos || text.find("cinematic") != std::string::npos) {
		    movieTweets.insert(movieIndex, tweetHashTable.search(i)->data);
		    movieIndex++;
	    } else if (text.find("programming") != std::string::npos || text.find("Programming") != std::string::npos || text.find("cod") != std::string::npos || text.find("coding") != std::string::npos) {
 		    programmingTweets.insert(programmingIndex, tweetHashTable.search(i)->data);
		    programmingIndex++;
	    } else if (text.find("reading") != std::string::npos || text.find("book") != std::string::npos) {
 		    readingTweets.insert(readingIndex, tweetHashTable.search(i)->data);
		    readingIndex++;
	    } else if (text.find("art") != std::string::npos || text.find("Art") != std::string::npos || text.find("Canvas") != std::string::npos) {
 		    artTweets.insert(astronomyIndex, tweetHashTable.search(i)->data);
		    artIndex++;
	    } else if (text.find("fashion") != std::string::npos || text.find("Fashion") != std::string::npos || text.find("Style") != std::string::npos) {
 		    fashionTweets.insert(gamingIndex, tweetHashTable.search(i)->data);
		    fashionIndex++;
	    } else if (text.find("racing") != std::string::npos || text.find("Racing") != std::string::npos) {
		    racingTweets.insert(movieIndex, tweetHashTable.search(i)->data);
		    racingIndex++;
	    } else if (text.find("science") != std::string::npos || text.find("Science") != std::string::npos || text.find("explore") != std::string::npos || text.find("Explore") != std::string::npos) {
 		    scienceTweets.insert(programmingIndex, tweetHashTable.search(i)->data);
		    scienceIndex++;
	    } else if (text.find("vacation") != std::string::npos || text.find("Vacation") != std::string::npos) {
 		    vacationTweets.insert(readingIndex, tweetHashTable.search(i)->data);
		    vacationIndex++;
	    }

	    std::regex hashtagRegex(R"(\#\w+)");
	    std::smatch match;
	    while (std::regex_search(text, match, hashtagRegex)) {
		    //std::cout << match.str() << std::endl;
	            std::string* hashtag = new std::string(match.str());
          	    hashTagTable.insert(tweetHashTable.search(i)->data->user->region, hashtag);
		    text = match.suffix();
	    }
    }

    //userGraph.printGraph();

    DataItem<User, int>* userDataItem = userHashTable.search(0);
    if (userDataItem) {
        User* startUser = userDataItem->data;
	std::cout << "-----Same follower count-----" << std::endl;
	outputFile << "-----Same follower count-----" << std::endl;
	userGraph.BFS(startUser, "followerCount");
        //userGraph.BFS(startUser, "all");
	std::cout << "-----DFS ile icerisinde kelime olan tweetler-----" << std::endl;
	outputFile << "-----DFS ile icerisinde kelime olan tweetler-----" << std::endl;
	userGraph.DFS(startUser, tweetHashTable, "Movie");
    } else {
        std::cerr << "Istenilen kullanici hash tablosunda bulunamadi." << std::endl;
    }

    inputFile.close();
    std::cout << std::endl << "-----UserHashTable-----" << std::endl;
    outputFile << std::endl << "-----UserHashTable-----" << std::endl;	
    userHashTable.display();
    std::cout << std::endl << "-----Ayni ilgi alani icin paylasim yapan kullanicilar-----" << std::endl;
    outputFile << std::endl << "-----Ayni ilgi alani icin paylasim yapan kullanicilar-----" << std::endl;
    tweetHashTable.display(false);
    std::cout << std::endl << "-----TweetHashTable-----" << std::endl;
    outputFile << std::endl << "-----TweetHashTable-----" << std::endl;
    tweetHashTable.display();
    std::cout << std::endl << "-----UserGrap-----" << std::endl;
    outputFile << std::endl << "-----UserGrap-----" << std::endl;
    userGraph.printGraph();
    std::cout << std::endl << "-----AstronomyTweets-----" << std::endl;
    outputFile << std::endl << "-----AstronomyTweets-----" << std::endl;
    astronomyTweets.display(); 
    std::cout << std::endl << "-----GamingTweets-----" << std::endl;
    outputFile << std::endl << "-----GamingTweets-----" << std::endl;
    gamingTweets.display();
    std::cout << std::endl << "-----MovieTweets-----" << std::endl;
    outputFile << std::endl << "-----MovieTweets-----" << std::endl;
    movieTweets.display();
    std::cout << std::endl << "-----ProgrammingTweets-----" << std::endl; 
    outputFile << std::endl << "-----ProgrammingTweets-----" << std::endl; 
    programmingTweets.display();
    std::cout << std::endl << "-----ReadingTweets-----" << std::endl;
    outputFile << std::endl << "-----ReadingTweets-----" << std::endl;
    readingTweets.display();
    std::cout << std::endl << "-----ArtTweets-----" << std::endl;
    outputFile << std::endl << "-----ArtTweets-----" << std::endl;
    artTweets.display(); 
    std::cout << std::endl << "-----RacingTweets-----" << std::endl;
    outputFile << std::endl << "-----RacingTweets-----" << std::endl;
    racingTweets.display();
    std::cout << std::endl << "-----FashionTweets-----" << std::endl;
    outputFile << std::endl << "-----FashionTweets-----" << std::endl;
    fashionTweets.display();
    std::cout << std::endl << "-----VacationTweets-----" << std::endl; 
    outputFile << std::endl << "-----VacationTweets-----" << std::endl; 
    vacationTweets.display();
    std::cout << std::endl << "-----ScienceTweets-----" << std::endl;
    outputFile << std::endl << "-----ScienceTweets-----" << std::endl;
    scienceTweets.display();
    std::cout << std::endl << "-----HashTagTable-----" <<std::endl;
    outputFile << std::endl << "-----HashTagTable-----" <<std::endl;
    hashTagTable.display();
    userGraph.printSameInterest(userHashTable.search(0)->data, userHashTable.search(1)->data, tweetHashTable, "Code");

    outputFile.close();
}
