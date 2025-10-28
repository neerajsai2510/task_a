#include "reply.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Reply* createReply(const char* username, const char* content) 
{
    Reply* newReply = (Reply*)malloc(sizeof(Reply));
    if (newReply == NULL) 
    {
        printf("Error: Could not allocate memory for new reply.\n");
        return NULL;
    }
    strncpy(newReply->username, username, MAX_USERNAME_LEN - 1);
    newReply->username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(newReply->content, content, MAX_CONTENT_LEN - 1);
    newReply->content[MAX_CONTENT_LEN - 1] = '\0';
    newReply->next = NULL;
    return newReply;
}
void destroyReply(Reply* head) 
{
    Reply* current = head;
    Reply* next_reply;
    while (current != NULL) 
    {
        next_reply = current->next;
        free(current);
        current = next_reply;
    }
}
