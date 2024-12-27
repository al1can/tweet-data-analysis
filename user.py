class User:
    username = ""
    name = ""
    surname = ""
    follower_count = 0
    follows_count = 0
    language = ""
    region = ""
    tweets = []
    followers = []
    follows = []

    def __init__(self, username, name, surname, language, region):
        self.username = username
        self.name = name
        self.surname = surname
        self.language = language
        self.region = region

