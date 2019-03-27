# friendrecommender

This is a friend recommender application that recommends a user friends based on the users movie genre preferences. 
This application uses a B-Plus Tree to keep track of the users and thheir information
and then it uses a graph stored as a adjacency list to see which users are friends with one another.

The functionality of this application is as follows by running ./tree:

1) Insert TextFile
2) Insert User
3) Find User 
4) Find User Details
5) Recommend Friends
6) Exit 

Insert TextFile takes a .txt file as input which contains a users information in the format of: id/perm; name; movie-genre1; 
movie-genre2; friend1ID; friend2ID; friend3ID;....;friendNID
      There are two files included that can be used to test the application: friends.txt and users_friends.txt

Insert Users allows you to insert individual users, their favorite genres, and their friend list IDs

Find user allows you to find a user with their ID

Find user details allows you to pull out the specifics of a user with their ID

Recommend Friends takes a user ID and runs a DFS to check the friends of friends which contain at least one favorite movie genre 
in common with the user that you want to recommend friends to. It returns a list of recommended users. 
