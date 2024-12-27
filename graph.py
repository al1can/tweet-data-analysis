import matplotlib.pyplot as plt
import networkx as nx

# Sample User class for demonstration
class User:
    def __init__(self, user_id, name):
        self.user_id = user_id
        self.name = name
        self.followers = []
        self.following = []

# Function to create a sample graph
def create_sample_graph():
    user1 = User(1, "Alice")
    user2 = User(2, "Bob")
    user3 = User(3, "Charlie")

    user1.following.append(user2)
    user2.followers.append(user1)

    user2.following.append(user3)
    user3.followers.append(user2)

    return [user1, user2, user3]

# Function to visualize the graph using matplotlib
def visualize_graph(graph):
    G = nx.DiGraph()

    # Add nodes
    for user in graph:
        G.add_node(user.user_id, label=user.name)

    # Add edges
    for user in graph:
        for follower in user.followers:
            G.add_edge(follower.user_id, user.user_id)

    # Draw the graph
    pos = nx.spring_layout(G)
    labels = nx.get_edge_attributes(G, 'label')
    nx.draw(G, pos, with_labels=True, labels=nx.get_node_attributes(G, 'label'), node_size=700, node_color='skyblue', font_size=8)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

    plt.show()

if __name__ == "__main__":
    graph = create_sample_graph()
    visualize_graph(graph)

