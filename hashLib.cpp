// hashLib.cpp
#include "hashLib.h"

template <typename T, int SIZE>
HashTable<T, SIZE>::HashTable() {
    for (int i = 0; i < SIZE; i++) {
        hashArray[i] = nullptr;
    }
    dummyItem = new DataItem<T>();
    dummyItem->key = -1;  // Assuming -1 is not a valid key
    item = new DataItem<T>();
}

template <typename T, int SIZE>
HashTable<T, SIZE>::~HashTable() {
    delete dummyItem;
    delete item;
}

template <typename T, int SIZE>
int HashTable<T, SIZE>::hashCode(int key) {
    return key % SIZE;
}

template <typename T, int SIZE>
DataItem<T>* HashTable<T, SIZE>::search(int key) {
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

template <typename T, int SIZE>
void HashTable<T, SIZE>::insert(int key, T data) {
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

template <typename T, int SIZE>
DataItem<T>* HashTable<T, SIZE>::deleteItem(DataItem<T>* item) {
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

template <typename T, int SIZE>
void HashTable<T, SIZE>::display() {
    for (int i = 0; i < SIZE; i++) {
        if (hashArray[i] != nullptr) {
            std::cout << " (" << hashArray[i]->key << ")";
            std::cout << " " << hashArray[i]->data << std::endl;
        } else {
            std::cout << " ~~ ";
        }
    }
}

