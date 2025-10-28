// comment.h - Defines the structure for a Comment, which holds a list of Replies.

#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h" // We need the Reply structure to hold a list of replies
#include <stdbool.h>

// This is the structure for a single Comment.
typedef struct Comment {
    char username[MAX_USERNAME_LEN]; // Who wrote the comment
    char content[MAX_CONTENT_LEN];   // The text of the comment

    // The HEAD of a linked list of Replies.
    Reply* replies;

    // The link to the NEXT comment on the post.
    struct Comment* next;
} Comment;

// Function to create a new Comment.
Comment* createComment(const char* username, const char* content);

// Function to add a reply to the Nth recent comment.
bool addReply(Comment* head, const char* username, const char* content, int n);

// Function to delete the Mth recent reply from the Nth recent comment.
bool deleteReply(Comment* head, int n, int m);

// Function to free the memory used by a single Comment and its list of replies/chain.
void destroyComment(Comment* comment);

#endif // COMMENT_H
