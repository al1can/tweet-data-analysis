#include <iostream>
#include <string>

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class Graph {
public:
    Graph(int maxVertices);
    ~Graph();
    void addVertex(T& vertex);
    void addEdge(T& vertex1, T& vertex2);
    void printGraph();

private:
    int maxVertices;
    int numVertices;
    T* vertices;
    Node<T>** adjacencyList;

    int getIndex(T& vertex);
    void DFSUtil(int index, bool* visited);
};

template <typename T>
Graph<T>::Graph(int maxVertices) : maxVertices(maxVertices), numVertices(0), vertices(new T[maxVertices]), adjacencyList(new Node<T>*[maxVertices]()) {}

template <typename T>
Graph<T>::~Graph() {
    delete[] vertices;

    for (int i = 0; i < numVertices; ++i) {
        Node<T>* current = adjacencyList[i];
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
}

template <typename T>
void Graph<T>::addVertex(T& vertex) {
    if (numVertices < maxVertices) {
        vertices[numVertices++] = vertex;

        // Initialize the corresponding entry in the adjacencyList
        adjacencyList[numVertices - 1] = nullptr;
    } else {
        std::cerr << "Graph is full. Cannot add more vertices." << std::endl;
    }
}

template <typename T>
void Graph<T>::addEdge(T& vertex1, T& vertex2) {
    int index1 = getIndex(vertex1);
    int index2 = getIndex(vertex2);

    if (index1 == -1 || index2 == -1) {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
        return;
    }

    Node<T>* newNode1 = new Node<T>{vertex2, adjacencyList[index1]};
    adjacencyList[index1] = newNode1;

    Node<T>* newNode2 = new Node<T>{vertex1, adjacencyList[index2]};
    adjacencyList[index2] = newNode2;
}

template <typename T>
int Graph<T>::getIndex(T& vertex) {
    for (int i = 0; i < numVertices; ++i) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1; // Vertex not found
}

template <typename T>
void Graph<T>::printGraph() {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Adjacency list for vertex " << vertices[i].name << ": ";
        Node<T>* current = adjacencyList[i];
        while (current != nullptr) {
            std::cout << current->data.name << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

/*
int main() {
    Graph<User> userGraph(5);

    User user1("John", "John Doe");
    User user2("Jane", "Jane Doe");

    userGraph.addVertex(user1);
    userGraph.addVertex(user2);

    userGraph.addEdge(user1, user2);

    // ... other graph operations ...

    userGraph.printGraph();

    return 0;
}
*/
