#include <iostream>

// Structure to represent a user
struct User {
    int id;
    std::string name;
};

// Structure to represent a node in the graph
struct Node {
    User user;
    Node* next;
};

// Structure to represent the graph
class Graph {
public:
    Graph(int numUsers);
    ~Graph();
    void addEdge(int userId1, int userId2);
    void printGraph();
    void BFS(int startVertex);
    void DFS(int startVertex);

private:
    int numUsers;
    Node** adjacencyList;

    void DFSUtil(int vertex, bool* visited);
};

Graph::Graph(int numUsers) : numUsers(numUsers), adjacencyList(new Node*[numUsers]()) {}

Graph::~Graph() {
    for (int i = 0; i < numUsers; ++i) {
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
}

void Graph::addEdge(int userId1, int userId2) {
    // Assuming userId1 and userId2 are valid indices
    Node* newNode1 = new Node{User{userId2, "User " + std::to_string(userId2)}, adjacencyList[userId1]};
    adjacencyList[userId1] = newNode1;

    Node* newNode2 = new Node{User{userId1, "User " + std::to_string(userId1)}, adjacencyList[userId2]};
    adjacencyList[userId2] = newNode2;
}

void Graph::printGraph() {
    for (int i = 0; i < numUsers; ++i) {
        std::cout << "Connections for User " << i << " (" << "User " << i << "):\n";
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            std::cout << " -> User " << current->user.id << " (" << current->user.name << ")\n";
            current = current->next;
        }
        std::cout << "\n";
    }
}

void Graph::BFS(int startVertex) {
    bool* visited = new bool[numUsers]{false};

    visited[startVertex] = true;
    std::cout << startVertex << " ";

    for (int i = 0; i < numUsers; ++i) {
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            int adjacentVertex = current->user.id;
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                std::cout << adjacentVertex << " ";
            }
            current = current->next;
        }
    }

    delete[] visited;
}

void Graph::DFS(int startVertex) {
    bool* visited = new bool[numUsers]{false};
    DFSUtil(startVertex, visited);
    delete[] visited;
}

void Graph::DFSUtil(int vertex, bool* visited) {
    visited[vertex] = true;
    std::cout << vertex << " ";

    Node* current = adjacencyList[vertex];
    while (current != nullptr) {
        int adjacentVertex = current->user.id;
        if (!visited[adjacentVertex]) {
            DFSUtil(adjacentVertex, visited);
        }
        current = current->next;
    }
}

int main() {
    // Create a graph with 5 users
    Graph userGraph(5);

    // Add connections between users
    userGraph.addEdge(0, 1);
    userGraph.addEdge(0, 3);
    userGraph.addEdge(1, 2);
    userGraph.addEdge(2, 3);
    userGraph.addEdge(2, 4);

    // Print the graph
    userGraph.printGraph();

    // Perform BFS starting from vertex 0
    std::cout << "BFS starting from vertex 0:\n";
    userGraph.BFS(0);
    std::cout << "\n";

    // Perform DFS starting from vertex 0
    std::cout << "DFS starting from vertex 0:\n";
    userGraph.DFS(0);
    std::cout << "\n";

    return 0;
}

