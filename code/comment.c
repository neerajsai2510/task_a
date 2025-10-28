#include "comment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Creates a new Comment
Comment* createComment(const char* username, const char* content) {
    Comment* newComment = (Comment*)malloc(sizeof(Comment));
    if (newComment == NULL) 
        {
            printf("Error: Could not allocate memory for new comment.\n");
            return NULL;
        }
    strncpy(newComment->username, username, MAX_USERNAME_LEN - 1);
    newComment->username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(newComment->content, content, MAX_CONTENT_LEN - 1);
    newComment->content[MAX_CONTENT_LEN - 1] = '\0';
    newComment->replies = NULL;
    newComment->next = NULL;
    return newComment;
}
// Function to add a reply to the Nth recent comment
bool addReply(Comment* head, const char* username, const char* content, int n) 
    {
        Comment* targetComment = head;
        int count = 1;
        // Loop until we find the Nth comment
        while (targetComment != NULL && count < n) 
            {
                targetComment = targetComment->next;
                count++;
            }
        if (targetComment == NULL) 
            {
                printf("Error: Comment %d does not exist.\n", n);
                return false;
            }
        Reply* newReply = createReply(username, content);
        if (newReply == NULL) 
            {
                return false;
            }
        newReply->next = targetComment->replies;
        targetComment->replies = newReply;
        return true;
    }
// Function to delete the Mth recent reply from the Nth recent comment.
bool deleteReply(Comment* head, int n, int m) 
    {
        Comment* targetComment = head;
        int count = 1;
        while (targetComment != NULL && count < n) 
        {
            targetComment = targetComment->next;
            count++;
        }
        if (targetComment == NULL) 
        {
            printf("Error: Comment %d does not exist.\n", n);
            return false;
        }
        Reply* currentReply = targetComment->replies;
        Reply* previousReply = NULL;
        count = 1;
        //Loop to find the Mth reply.
        while (currentReply != NULL && count < m) 
        {
            previousReply = currentReply;
            currentReply = currentReply->next;
            count++;
        }
        if (currentReply == NULL) 
        {
            printf("Error: Reply %d for comment %d does not exist.\n", m, n);
            return false;
        }
        if (previousReply == NULL) 
        {
            targetComment->replies = currentReply->next;
        } else 
        {
            previousReply->next = currentReply->next;
        }
        free(currentReply);
        return true;
    }
void destroyComment(Comment* head) 
    {
        Comment* current = head;
        Comment* next_comment;
        while (current != NULL) 
        {
            next_comment = current->next;
            destroyReply(current->replies);
            free(current);
            current = next_comment;
        }
    }
