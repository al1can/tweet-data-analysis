// hashLib.h (header file)
#pragma once

#include <iostream>

template <typename T>
struct DataItem {
    T data;
    int key;

    DataItem() : data(), key() {}
};

template <typename T, int SIZE>
class HashTable {
private:
    DataItem<T>* hashArray[SIZE];
    DataItem<T>* dummyItem;
    DataItem<T>* item;

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            hashArray[i] = nullptr;
        }
        dummyItem = new DataItem<T>();
        dummyItem->key = -1;  // Assuming -1 is not a valid key
        item = new DataItem<T>();
    }

    ~HashTable() {
        delete dummyItem;
        delete item;
    }

    int hashCode(int key) {
        return key % SIZE;
    }

    DataItem<T>* search(int key) {
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

    void insert(int key, T data) {
        DataItem<T>* newItem = new DataItem<T>();
        newItem->data = data;
        newItem->key = key;

        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != -1) {
            ++hashIndex;
            hashIndex %= SIZE;
        }

        hashArray[hashIndex] = newItem;
    }

    DataItem<T>* deleteItem(DataItem<T>* item) {
        int key = item->key;
        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr) {
            if (hashArray[hashIndex]->key == key) {
                DataItem<T>* temp = hashArray[hashIndex];
                hashArray[hashIndex] = dummyItem;
                return temp;
            }

            ++hashIndex;
            hashIndex %= SIZE;
        }

        return nullptr;
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (hashArray[i] != nullptr) {
                std::cout << " (" << hashArray[i]->key << ")";
                std::cout << " " << &hashArray[i] << std::endl;
            } else {
                std::cout << " ~~ ";
            }
        }
    }
};

