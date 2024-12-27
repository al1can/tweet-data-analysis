"""
from user import User
from tweet import Tweet
import random
from faker import Faker

user_count = 50
users = []
fake = Faker()

for i in range(user_count):
    name = fake.name().split()
    user = User(name[0], name[0], name[1], "english", "Europe")
    users.append(user)

#print(users)
file_names = []
with open('./data/file_names.txt', 'r') as file:
    for line in file:
        file_names.append(line.strip())
print(file_names)

for file in file_names:
    with open('./data/'+file+'.txt', 'r') as f:
        for line in f:
            tweet = Tweet(line) 
            user = random.choice(users)
            user.tweets.append(tweet)

user = random.choice(users)
#print(user.tweets)
#print(len(users))

for user in users:
    rand_users = random.sample(users, random.randint(1, len(users)))
    rand_users_f = random.sample(users, random.randint(1, len(users)))
    user.followers.append(rand_users)
    user.follows.append(rand_users)
    user.followers.append(rand_users_f)
    #print(user.followers)
    #print(user.follows)
"""

import ctypes

# Load the shared library
user_graph_lib = ctypes.CDLL('./graph.so')

# Define the User structure in Python
class User(ctypes.Structure):
    _fields_ = [('id', ctypes.c_int), ('name', ctypes.c_char * 50)]

# Define the Node structure in Python
class Node(ctypes.Structure):
    pass

Node._fields_ = [('user', ctypes.POINTER(User)), ('next', ctypes.POINTER(Node))]

# Define the Graph structure in Python
class Graph(ctypes.Structure):
    _fields_ = [('numUsers', ctypes.c_int), ('adjacencyList', ctypes.POINTER(ctypes.POINTER(Node)))]

# Create C functions wrappers
createUser = user_graph_lib.createUser
createUser.argtypes = [ctypes.c_int, ctypes.c_char_p]
createUser.restype = ctypes.POINTER(User)

createNode = user_graph_lib.createNode
createNode.argtypes = [ctypes.POINTER(User)]
createNode.restype = ctypes.POINTER(Node)

createGraph = user_graph_lib.createGraph
createGraph.argtypes = [ctypes.c_int]
createGraph.restype = ctypes.POINTER(Graph)

addEdge = user_graph_lib.addEdge
addEdge.argtypes = [ctypes.POINTER(Graph), ctypes.c_int, ctypes.c_int]

printGraph = user_graph_lib.printGraph
printGraph.argtypes = [ctypes.POINTER(Graph)]

freeGraph = user_graph_lib.freeGraph
freeGraph.argtypes = [ctypes.POINTER(Graph)]

# Update addEdge function to handle errors
def addEdge(graph, userId1, userId2):
    try:
        result = user_graph_lib.addEdge(graph, userId1, userId2)
        if result != 0:
            raise RuntimeError(f"Failed to add edge ({userId1}, {userId2})")
    except Exception as e:
        raise RuntimeError(f"Exception in addEdge: {e}")

# Update printGraph function to handle errors
def printGraph(graph):
    try:
        user_graph_lib.printGraph(graph)
    except Exception as e:
        raise RuntimeError(f"Exception in printGraph: {e}")

if __name__ == '__main__':
    try:
        # Create a graph with 5 users
        userGraph = createGraph(5)

        if not userGraph:
            raise RuntimeError("Failed to create graph")

        # Create users
        user0 = createUser(0, b"Alice")
        user1 = createUser(1, b"Bob")
        user2 = createUser(2, b"Charlie")
        user3 = createUser(3, b"David")
        user4 = createUser(4, b"Eve")

        # Add connections between users
        addEdge(userGraph, user0.contents.id, user1.contents.id)
        #addEdge(userGraph, user0.contents.id, user3.contents.id)
        #addEdge(userGraph, user1.contents.id, user2.contents.id)
        #addEdge(userGraph, user2.contents.id, user3.contents.id)
        #addEdge(userGraph, user2.contents.id, user4.contents.id)

        # Print the graph
        #printGraph(userGraph)

    finally:
        # Free the memory
        freeGraph(userGraph)
        print("adas")
