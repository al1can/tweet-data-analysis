#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct HashItem {
	int data;
	int key;
};

struct HashItem* hashTable[SIZE];
struct HashItem* tempItem;
struct HashItem* item;

int hashCode(int key) {
	return key % SIZE;
}

struct HashItem* insert(int key, int data) {
	struct HashItem* item = (struct HashItem*) malloc(sizeof(struct HashItem));
	item->data = data;
	item->key = key;

	int i = hashCode(key);
	for (;hashTable[i] != NULL && hashTable[i]->key != -1; i++) {
		i = i%SIZE;
	}

	hashTable[i] = item;

}

void display() {
	for (int i = 0; i < SIZE; i++) {
		if (hashTable[i] == NULL) { 
			printf(" empty ");
		}
		else {
			printf("%d %d", hashTable[i]->key, hashTable[i]->data);	
		}
	}
}

struct HashItem* search(int key) {
	for (int i = hashCode(key); hashTable[i] != NULL; i++) {
		if (key == hashTable[i]->key) return hashTable[i];
		i = i%SIZE;
	}
	return NULL;
}

struct HashItem* delete(struct HashItem* item) {	
	for (int i = hashCode(item->key); hashTable[i] != NULL; i++) {
		if (item->key == hashTable[i]->key) {
			struct HashItem* temp = hashTable[i];
			hashTable[i] = tempItem;
			return temp;
		}
		i = i%SIZE;
	}
	return NULL;
}

int main() {
   tempItem = (struct HashItem*) malloc(sizeof(struct HashItem));
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

   if(item != NULL) {
      printf("Element found: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }

   delete(item);
   item = search(37);

   if(item != NULL) {
      printf("Element found: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }
}

