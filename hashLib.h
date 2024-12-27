#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

template <typename T, typename K>
struct DataItem {
    T* data;
    K key;
};

template <typename T, typename K, int SIZE>
class HashTable {
private:
    DataItem<T, K>* hashArray[SIZE];
    DataItem<T, K>* dummyItem;
    DataItem<T, K>* item;

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            hashArray[i] = nullptr;
        }
        dummyItem = new DataItem<T, K>();
        dummyItem->key = K();
        item = new DataItem<T, K>();
    }

    ~HashTable() {
        delete dummyItem;
        delete item;
    }

    int hashCode(const K& key) {
        return std::hash<K>{}(key) % SIZE;
    }

    void insert(const K& key, T* data) {
        DataItem<T, K>* newItem = new DataItem<T, K>();
        newItem->data = data;
        newItem->key = key;

        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != K()) {
            ++hashIndex;
            hashIndex %= SIZE;
        }

        hashArray[hashIndex] = newItem;
    }

    DataItem<T, K>* search(const K& key) {
        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr) {
            if (hashArray[hashIndex]->key == key) {
                return hashArray[hashIndex];
            }

            ++hashIndex;
            hashIndex %= SIZE;
        }

        return nullptr;
    }

    void display(bool onlyUsers = false) {
        std::ofstream outputFile("output.txt", std::ofstream::app);

        if (!outputFile.is_open()) {
            std::cerr << "Dosya acilamadi." << std::endl;
            return;
        }

        for (int i = 0; i < SIZE; i++) {
            if (hashArray[i] != nullptr) {
                std::cout << " (" << hashArray[i]->key << ")";
                outputFile << " (" << hashArray[i]->key << ")";

                if constexpr (std::is_same<T, User>::value) {
                    std::cout << " User: " << hashArray[i]->data->name << std::endl;
                    outputFile << " User: " << hashArray[i]->data->name << std::endl;
                } else if constexpr (std::is_same<T, Tweet>::value) {
		    if (onlyUsers) {
  		        std::cout << " User: " << hashArray[i]->data->user->name << std::endl;
		        outputFile << " User: " << hashArray[i]->data->user->name << std::endl;
		    } else {
  		        std::cout << " User: " << hashArray[i]->data->user->name << std::endl;
		        outputFile << " User: " << hashArray[i]->data->user->name << std::endl;
                        std::cout << " Tweet: " << hashArray[i]->data->text << std::endl;
                        outputFile << " Tweet: " << hashArray[i]->data->text << std::endl;
		    }
                } else if constexpr (std::is_same<T, std::string>::value) {
                    std::cout << " Hashtag: " << *hashArray[i]->data << std::endl;
                    outputFile << " Hashtag: " << *hashArray[i]->data << std::endl;
                }
            } else {
                std::cout << " ~~ ";
            }
        }

        outputFile.close();
    }
};

