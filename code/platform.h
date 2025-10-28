#ifndef PLATFORM_H
#define PLATFORM_H
#include "post.h"
#include <stdbool.h>
typedef struct Platform 
{
    Post* posts;
    Post* lastViewedPost;
} Platform;
void createPlatform(Platform* platform);
bool addPost(Platform* platform, const char* username, const char* caption);
bool deletePost(Platform* platform, int n);
Post* viewPost(Platform* platform, int n);
Post* currPost(Platform* platform);
Post* nextPost(Platform* platform);
Post* previousPost(Platform* platform);
bool addPlatformComment(Platform* platform, const char* username, const char* content);
bool deletePlatformComment(Platform* platform, int n);
bool addPlatformReply(Platform* platform, const char* username, const char* content, int n);
bool deletePlatformReply(Platform* platform, int n, int m);
void viewAllComments(Platform* platform);
void destroyPlatform(Platform* platform);
#endif
