#include "post.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Post* createPost(const char* username, const char* caption) 
{
    Post* newPost = (Post*)malloc(sizeof(Post));
    if (newPost == NULL) 
    {
        printf("Error: Could not allocate memory for new post.\n");
        return NULL;
    }
    strncpy(newPost->username, username, MAX_USERNAME_LEN - 1);
    newPost->username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(newPost->caption, caption, MAX_CONTENT_LEN * 2 - 1);
    newPost->caption[MAX_CONTENT_LEN * 2 - 1] = '\0';
    newPost->comments = NULL;
    newPost->next = NULL;
    return newPost;
}
bool addComment(Post* post, const char* username, const char* content) {
    if (post == NULL) 
    {
        printf("Error: Cannot add comment. Post is NULL (no post viewed).\n");
        return false;
    }
    Comment* newComment = createComment(username, content);
    if (newComment == NULL) {
        return false;
    }
    newComment->next = post->comments;
    post->comments = newComment;
    return true;
}
bool deleteComment(Post* post, int n) 
{
    if (post == NULL) 
    {
        printf("Error: Cannot delete comment. Post is NULL (no post viewed).\n");
        return false;
    }
    if (n <= 0) {
        printf("Error: Comment index must be 1 or greater.\n");
        return false;
    }
    Comment* currentComment = post->comments;
    Comment* previousComment = NULL;
    int count = 1;
    while (currentComment != NULL && count < n) 
    {
        previousComment = currentComment;
        currentComment = currentComment->next;
        count++;
    }
    if (currentComment == NULL) 
    {
        printf("Error: Comment %d does not exist on this post.\n", n);
        return false;
    }
    if (previousComment == NULL) 
    {
        post->comments = currentComment->next;
    } else 
    {
        previousComment->next = currentComment->next;
    }
    destroyComment(currentComment);
    printf("Comment %d deleted successfully.\n", n);
    return true;
}
void destroyPost(Post* head) 
{
    Post* current = head;
    Post* next_post;
    while (current != NULL) 
    {
        next_post = current->next;
        destroyComment(current->comments);
        free(current);
        current = next_post;
    }
}
