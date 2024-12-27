#include <stdio.h>
#include <stdlib.h>

// Structure to represent a user
struct User {
    int id;
    char name[50];
};

// Structure to represent a node in the graph
struct Node {
    struct User* user;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int numUsers;
    struct Node** adjacencyList;
};

// Function to create a new user
struct User* createUser(int id, const char* name) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    newUser->id = id;
    snprintf(newUser->name, sizeof(newUser->name), "%s", name);
    return newUser;
}

// Function to create a new node
struct Node* createNode(struct User* user) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->user = user;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of users
struct Graph* createGraph(int numUsers) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numUsers = numUsers;

    // Allocate memory for adjacency list
    graph->adjacencyList = (struct Node**)malloc(numUsers * sizeof(struct Node*));

    // Initialize each adjacency list as empty by setting them to NULL
    for (int i = 0; i < numUsers; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Function to add an edge between two users
void addEdge(struct Graph* graph, int userId1, int userId2) {
    printf("Entering addEdge function\n");  // Add this line

    if (graph == NULL) {
        printf("Graph is NULL\n");
        return;
    }

    // Find the indices of users in the adjacency list
    int index1 = userId1;
    int index2 = userId2;

    printf("Indices: %d, %d\n", index1, index2);  // Add this line

    // Check if indices are within bounds
    if (index1 < 0 || index1 >= graph->numUsers || index2 < 0 || index2 >= graph->numUsers) {
        printf("Invalid user indices\n");
        return;
    }

    printf("Checking adjacency lists\n");  // Add this line

    // Check if adjacencyList is NULL for either user
    if (graph->adjacencyList[index1] == NULL || graph->adjacencyList[index2] == NULL) {
        printf("Adjacency list is NULL for User %d or User %d\n", userId1, userId2);
        return;
    }

    printf("Creating newNode1\n");  // Add this line

    // Create nodes for both users and add edges
    struct Node* newNode1 = createNode(graph->adjacencyList[index2]->user);
    if (newNode1 == NULL) {
        printf("Failed to allocate memory for newNode1\n");
        return;
    }
    newNode1->next = graph->adjacencyList[index1];
    graph->adjacencyList[index1] = newNode1;

    printf("Creating newNode2\n");  // Add this line

    struct Node* newNode2 = createNode(graph->adjacencyList[index1]->user);
    if (newNode2 == NULL) {
        printf("Failed to allocate memory for newNode2\n");
        return;
    }
    newNode2->next = graph->adjacencyList[index2];
    graph->adjacencyList[index2] = newNode2;

    printf("Edge added between User %d and User %d\n", userId1, userId2);
    printf("Exiting addEdge function\n");  // Add this line
}

// Function to print the graph
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numUsers; ++i) {
        printf("Connections for User %d (%s):\n", i, graph->adjacencyList[i]->user->name);
        struct Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            printf(" -> User %d (%s)\n", current->user->id, current->user->name);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to free the memory allocated for the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numUsers; ++i) {
        struct Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjacencyList);
    free(graph);
}

int main() {
    // Create a graph with 5 users
    struct Graph* userGraph = createGraph(5);

    // Create users
    struct User* user0 = createUser(0, "Alice");
    struct User* user1 = createUser(1, "Bob");
    struct User* user2 = createUser(2, "Charlie");
    struct User* user3 = createUser(3, "David");
    struct User* user4 = createUser(4, "Eve");

    // Add connections between users
    addEdge(userGraph, user0->id, user1->id);
    addEdge(userGraph, user0->id, user3->id);
    addEdge(userGraph, user1->id, user2->id);
    addEdge(userGraph, user2->id, user3->id);
    addEdge(userGraph, user2->id, user4->id);

    // Print the graph
    printGraph(userGraph);

    // Free the memory
    freeGraph(userGraph);

    return 0;
}

