#include <iostream>

#define SIZE 20

struct HashItem {
    int data;
    int key;
};

HashItem* hashTable[SIZE];
HashItem* tempItem;
HashItem* item;

int hashCode(int key) {
    return key % SIZE;
}

HashItem* insert(int key, int data) {
    HashItem* item = new HashItem();
    item->data = data;
    item->key = key;

    int i = hashCode(key);
    for (; hashTable[i] != nullptr && hashTable[i]->key != -1; i = (i + 1) % SIZE) {
        i = i % SIZE;
    }

    hashTable[i] = item;
    return item;
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] == nullptr) {
            std::cout << " empty ";
        } else {
            std::cout << hashTable[i]->key << " " << hashTable[i]->data;
        }
    }
    std::cout << std::endl;
}

HashItem* search(int key) {
    for (int i = hashCode(key); hashTable[i] != nullptr; i = (i + 1) % SIZE) {
        if (key == hashTable[i]->key) {
            return hashTable[i];
        }
        i = i % SIZE;
    }
    return nullptr;
}

HashItem* remove(int key) {
    for (int i = hashCode(key); hashTable[i] != nullptr; i = (i + 1) % SIZE) {
        if (key == hashTable[i]->key) {
            HashItem* temp = hashTable[i];
            hashTable[i] = tempItem;
            return temp;
        }
        i = i % SIZE;
    }
    return nullptr;
}

int main() {
    tempItem = new HashItem();
    tempItem->data = -1;
    tempItem->key = -1;

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);
    insert(12, 44);
    insert(14, 32);
    insert(17, 11);
    insert(13, 78);
    insert(37, 97);

    display();
    item = search(37);

    if (item != nullptr) {
        std::cout << "Element found: " << item->data << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    remove(37);
    item = search(37);

    if (item != nullptr) {
        std::cout << "Element found: " << item->data << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}

