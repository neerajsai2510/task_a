#ifndef POST_H
#define POST_H
#include "comment.h"
#include <stdbool.h>
typedef struct Post 
{
    char username[MAX_USERNAME_LEN];
    char caption[MAX_CONTENT_LEN * 2];
    Comment* comments;
    struct Post* next;
} Post;
Post* createPost(const char* username, const char* caption);
bool addComment(Post* post, const char* username, const char* content);
bool deleteComment(Post* post, int n);
void destroyPost(Post* post);
#endif
