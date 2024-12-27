#include <iostream>
#include <string>

template <typename T>
struct Node {
    T* data;
    Node* next;
};

template <typename T>
class Graph {
public:
    Graph(int maxVertices);
    ~Graph();
    void addVertex(T* vertex);
    void addEdge(T* vertex1, T* vertex2);
    void printGraph();
    void DFS(T* startVertex, HashTable<Tweet, int, 1000>& tweetHashTable, std::string keyString);
    void BFS(T* startVertex, std::string method);
    void printSameInterest(T* user1, T* user2, HashTable<Tweet, int, 1000>& tweetHashTable, std::string keyString);
private:
    int maxVertices;
    int numVertices;
    T** vertices;
    Node<T>** adjacencyList;

    int getIndex(T* vertex);
};

template <typename T>
Graph<T>::Graph(int maxVertices) : maxVertices(maxVertices), numVertices(0), vertices(new T*[maxVertices]), adjacencyList(new Node<T>*[maxVertices]()) {}

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
void Graph<T>::addVertex(T* vertex) {
    if (numVertices < maxVertices) {
        vertices[numVertices++] = vertex;

        adjacencyList[numVertices - 1] = nullptr;
    } else {
        std::cerr << "Graph doldu. Daha fazla deger eklenemez" << std::endl;
    }
}

template <typename T>
void Graph<T>::addEdge(T* vertex1, T* vertex2) {
    int index1 = getIndex(vertex1);
    int index2 = getIndex(vertex2);

    if (index1 == -1 || index2 == -1) {
        std::cerr << "Dugumler grafta bulunamadi." << index1 << index2 << std::endl;
        return;
    }

    Node<T>* newNode1 = new Node<T>{vertex2, adjacencyList[index1]};
    adjacencyList[index1] = newNode1;

    Node<T>* newNode2 = new Node<T>{vertex1, adjacencyList[index2]};
    adjacencyList[index2] = newNode2;
}

template <typename T>
int Graph<T>::getIndex(T* vertex) {
    for (int i = 0; i < numVertices; ++i) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Graph<T>::printGraph() {
	std::ofstream outputFile("output.txt", std::ofstream::app);

        if (!outputFile.is_open()) {
            std::cerr << "Dosya acilamadi." << std::endl;
            return;
        }

    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Follower list for vertex " << vertices[i]->name << ": ";
        outputFile << "Follower list for vertex " << vertices[i]->name << ": ";
        Node<T>* current = adjacencyList[i];
        while (current != nullptr) {
            std::cout << current->data->name << " ";
            outputFile << current->data->name << " ";
            current = current->next;
        }
        std::cout << std::endl;
        outputFile << std::endl;
    }
}

template <typename T>
void Graph<T>::printSameInterest(T* user1, T* user2, HashTable<Tweet, int, 1000>& tweetHashTable, std::string keyString) {
        std::ofstream outputFile("output.txt", std::ofstream::app);

        if (!outputFile.is_open()) {
            std::cerr << "Dosya acilamadi." << std::endl;
            return;
        }

        int index1 = getIndex(user1);
        int index2 = getIndex(user2);

        if (index1 == -1 || index2 == -1) {
            std::cerr << "One or both users not found in the graph." << std::endl;
            return;
        }

        Node<T>* current1 = adjacencyList[index1];
        while (current1 != nullptr) {
            Node<T>* current2 = adjacencyList[index2];
	    if (current1->data != current2->data) {
            while (current2 != nullptr) {
                
                    for (int i = 0; i < 1000; i++) {
                        Tweet* tweet1 = tweetHashTable.search(i)->data;
                        if (tweet1->user == current1->data) {
                            for (int j = 0; j < 1000; j++) {
                                Tweet* tweet2 = tweetHashTable.search(j)->data;
                                if (tweet2->user == current2->data) {
                                    if (tweet1->text.find(keyString) != std::string::npos && tweet2->text.find(keyString) != std::string::npos) {
                                        std::cout << current1->data->name << " ve " << current2->data->name << " " << keyString << " alanina ilgi duyuyor."  << std::endl;
                                        outputFile << current1->data->name << " ve " << current2->data->name << " " << keyString << " alanina ilgi duyuyor."  << std::endl;
                                    }

                                }
                            }

			}
                    }
		current2 = current2->next;
            }
            current1 = current1->next;
	    }
        }
    }

template <typename T>
void Graph<T>::BFS(T* startVertex, std::string method) {
    int startIndex = getIndex(startVertex);

    if (startIndex == -1) {
        std::cerr << "Baslangic dugumu bulunamadi." << std::endl;
        return;
    }

    std::ofstream outputFile("output.txt", std::ofstream::app);

        if (!outputFile.is_open()) {
            std::cerr << "Dosya açılamadı." << std::endl;
            return;
        }


    bool* visited = new bool[numVertices]{false};

    int* bfsQueue = new int[numVertices];
    int front = 0;
    int rear = 0; 

    visited[startIndex] = true;

    std::cout << "BFS starting from vertex " << vertices[startIndex]->name << ": ";
    outputFile << "BFS starting from vertex " << vertices[startIndex]->name << ": ";

    bfsQueue[rear++] = startIndex;

    while (front < rear) {
        int currentIndex = bfsQueue[front++];
	
	if (method.compare("followerCount") == 0) {
   	    if (vertices[currentIndex]->followerCount == startVertex->followerCount) {
	        std::cout << vertices[currentIndex]->name << " ";
	        outputFile << vertices[currentIndex]->name << " ";
	        //std::cout << vertices[currentIndex].followerCount << std::endl;
		//std::cout << startVertex.followerCount;
	    }
	} else if (method.compare("followsCount") == 0) {
            if (vertices[currentIndex]->followerCount == startVertex->followerCount) {
		std::cout << vertices[currentIndex]->name << " ";
		outputFile << vertices[currentIndex]->name << " ";
	    }
	} else if (method.compare("all") == 0) {
		std::cout << vertices[currentIndex]->name << " ";
		outputFile << vertices[currentIndex]->name << " ";
	}
        
        Node<T>* current = adjacencyList[currentIndex];
        while (current != nullptr) {
            int adjacentIndex = getIndex(current->data);

            if (!visited[adjacentIndex]) {
                visited[adjacentIndex] = true;
                bfsQueue[rear++] = adjacentIndex;
            }

            current = current->next;
        }
    }

    std::cout << std::endl;
    outputFile << std::endl;

    delete[] visited;
    delete[] bfsQueue;
}

template <typename T>
void Graph<T>::DFS(T* startVertex, HashTable<Tweet, int, 1000>& tweetHashTable, std::string keyString) {
    int startIndex = getIndex(startVertex);

    if (startIndex == -1) {
        std::cerr << "Dugum bulunamadi." << std::endl;
        return;
    }

    std::ofstream outputFile("output.txt", std::ofstream::app);

        if (!outputFile.is_open()) {
            std::cerr << "Dosya acilamadi" << std::endl;
            return;
        }


    bool* visited = new bool[numVertices]{false};
    
    std::cout << "kelime: " << keyString << std::endl;
    outputFile << "kelime: " << keyString << std::endl;

    std::cout << "DFS starting from vertex " << vertices[startIndex]->name << ": ";
    outputFile << "DFS starting from vertex " << vertices[startIndex]->name << ": ";

    std::function<void(int)> recursiveDFS = [&](int currentIndex) {
        if (!visited[currentIndex]) {
            visited[currentIndex] = true;
            if constexpr (std::is_same<T, User>::value) {
                std::cout << "Tweets by " << vertices[currentIndex]->name << ":" << std::endl;
                outputFile << "Tweets by " << vertices[currentIndex]->name << ":" << std::endl;
                    for (int i = 0; i < 1000; i++) {
                        Tweet* tweet = tweetHashTable.search(i)->data;
                        if (tweet->user == vertices[currentIndex]) {
                            if (tweet->text.find(keyString) != std::string::npos) {
                                std::cout << tweet->text << std::endl;
                                outputFile << tweet->text << std::endl;
                            }
                        }
                    }


                 //std::cout << vertices[currentIndex]->name << " ";
                 //vertices[currentIndex]->listTweetsByUser(tweetHashTable, keyString);

	    }

            Node<T>* current = adjacencyList[currentIndex];
            while (current != nullptr) {
                int adjacentIndex = getIndex(current->data);
                if (adjacentIndex != -1 && !visited[adjacentIndex]) {
                    recursiveDFS(adjacentIndex);
                }
                current = current->next;
            }
        }
    };

    recursiveDFS(startIndex);

    std::cout << std::endl;
    outputFile << std::endl;

    delete[] visited;
}

