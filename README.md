username – name of the user who posted  
 caption – text content of the post  
 comments – list of comments on the post 
Functions
 createComment(char* username, char* content) -> Creates and returns a new Comment object
 createReply(char* username, char* content) -> Creates and returns a new Reply object.
 createPlatform()-> Initializes and returns a Platform instance. 
 addPost(username, caption) -> Adds a new post to the platform. 
 deletePost(n) -> Deletes the n-th most recent post. 
 viewPost(n) -> Displays the n-th most recent post. 
 currPost() -> Returns the last viewed post. 
 nextPost() -> Moves to and returns the previous post in order of posting. 
 previousPost() -> Moves to and returns the next post in order of posting. 
 addComment(username, content) -> Adds a comment to the last viewed post. 
 deleteComment(n) -> Deletes the n-th most recent comment from the last viewed post. 
 viewComments() -> Displays all comments (and replies, if any) on the last viewed post. 
 addReply(username, content, n) ->  Adds a reply to the n-th recent comment. 
 deleteReply(n, m) ->  Deletes the m-th reply from the n-th comment.
