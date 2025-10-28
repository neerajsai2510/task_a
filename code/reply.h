#ifndef REPLY_H
#define REPLY_H
#define MAX_USERNAME_LEN 50
#define MAX_CONTENT_LEN 256
typedef struct Reply 
{
    char username[MAX_USERNAME_LEN];
    char content[MAX_CONTENT_LEN];

    struct Reply* next;
} Reply;
Reply* createReply(const char* username, const char* content);
void destroyReply(Reply* reply);
#endif
