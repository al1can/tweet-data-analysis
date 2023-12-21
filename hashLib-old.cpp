#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashLib.h"
#include "user.h"
#include "tweet.h"

int userHashCode(struct DataItem* hashArray[], int key) {
   return key % USERCOUNT;
}

int tweetHashCode(struct DataItem* hashArray[], int key) {
   return key % TWEETCOUNT;
}

int hashCode(struct DataItem* hashArray[], int key) {
    // Choose the appropriate hash function based on array type
    if (hashArray == userArray) {
        return userHashCode(key);
    } else if (hashArray == tweetArray) {
        return tweetHashCode(key);
    }
}

struct DataItem *search(struct DataItem* hashArray[], int key) {
   //get the hash 
   int hashIndex = hashCode(hashArray, key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex = hashCode(hashArray, hashIndex);
   }        
	
   return NULL;        
}

void insert(struct DataItem* hashArray[], int key, User* data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hashCode(hashArray, key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      //hashIndex %= SIZE;
      hashIndex = hashCode(hashArray, hashIndex);

   }

   hashArray[hashIndex] = item;
}

void insert(struct DataItem* hashArray[], int key, Tweet* data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hashCode(hashArray, key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      //hashIndex %= SIZE;
      hashIndex = hashCode(hashArray, hashIndex);

   }

   hashArray[hashIndex] = item;
}

struct DataItem* deleteItem(struct DataItem* hashArray[], struct DataItem* item) {
   int key = item->key;

   //get the hash
   int hashIndex = hashCode(hashArray, key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key) {
         struct DataItem* temp = hashArray[hashIndex];

         //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem;
         return temp;
      }

      //go to next cell
      ++hashIndex;

      //wrap around the table
      //hashIndex %= SIZE;
      hashIndex = hashCode(hashArray, hashIndex);

   }

   return NULL;
}

void display(struct DataItem* hashArray[]) {
   int i = 0;
   int size = 0;
   if (hashArray == userArray) {
	   size = USERCOUNT;
   } else if (hashArray == tweetArray) {
	   size = TWEETCOUNT;
   }
   for(i = 0; i<size; i++) {

      if(hashArray[i] != NULL) {
	       printf(" (%d)",hashArray[i]->key);
               std::cout << hashArray[i]->data->name << std::endl;
      }
      else
         printf(" ~~ ");
   }

   printf("\n");
}
/*
   dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   dummyItem->data = -1;
   dummyItem->key = -1;

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

*/
