import matplotlib.pyplot as plt

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
    plt.figure(figsize=(8, 6))

    # Draw nodes
    for user in graph:
        plt.scatter(user.user_id, 0, s=300, color='skyblue')
        plt.text(user.user_id, 0, user.name, ha='center', va='center', fontsize=8)

    # Draw edges
    for user in graph:
        for follower in user.followers:
            plt.plot([follower.user_id, user.user_id], [0, 0], color='gray', linestyle='-', linewidth=1)

    plt.axis('off')
    plt.show()

if __name__ == "__main__":
    graph = create_sample_graph()
    visualize_graph(graph)

