ConnectGram - Developed by Mohammad Parsa Golbou

This project is a C++ social media simulation system that models core platform features such as:
   - User authentication and relationships (follow/unfollow)
   - Content(only text) posting and liking
   - Hashtag-based content search
   - Feed generation using ranking algorithms
   - Efficient data retrieval using custom data structures(Trie, Adjacency Matrix, Hash Table, and etc.)

note: This project is for "Data Structure" course at "Isfahan University of Technology".



Core Modules and Design:
1) User Management:
   - Passwords are stored as hashed values for improved security.
   - User relationships are modeled as an adjacency list, effectively forming a directed graph.
   - Followers and followings counts are cached for efficiency, but adjacency list is used most of the time.
   - Vector is used here as a global entity to store all of the Users.
Time Complexity: Hash Password -> O(length of password)      Insert new User -> O(n)      Search Follower and Following -> O(n^2)
Place Complexity: O(n)


2) Post System:
   - Posts automatically extract hashtags on creation and are found later by searching the hashtags through a Hash Table.
   - Each post has a score which is dynamic and based on multiple variables.
   - The text in each post is displayed with a structure(removes the space characters before the text and only 45 character is allowed per line)
   - All the posts are saved in a vector but based on the hashtags they can be found in Hash Table.
Time Complexity: Hashing -> O(length of hashtag)      Insert new Post -> O(n)
Place Complexity: O(n)


3) Hashtag Indexing
   - Uses Hash Table with seperate chaining.
   - Each bucket contains a vector of "Post" and a list of "Entry" which shows which hashtag this "Entry" is related to.
   - A post may has multiple hashtags which can be find by every one of them.
Time Complexity: Hashing -> O(length of key)      Insert -> average case: O(1), worst case: O(n)      Search -> average case: O(1), worst case: O(n)
Place Complexity: O(1) -> uses pointers


4)Feed Ranking
   - Each post has a score.
   - 10 posts with highest score is found by using "Max Heap".
Time Complexity: Insert and Heapify All -> O(nlogn)      Pop Max and Heapify -> O(logn)      Extract Top 10 -> O(nlogn)
Place Complexity: O(1) -> uses pointers


5)Search System
   - This project has two different search system. 1- Prefix search with "Trie"  2- Search using "Hamming Distance"
Time Complexity: Trie -> O(logn)      Hamming Distance -> O(n)
Place Complexity: O(1)

