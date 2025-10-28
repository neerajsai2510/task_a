#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void createPlatform(Platform* platform) 
{
    if (platform != NULL) 
    {
        platform->posts = NULL;
        platform->lastViewedPost = NULL;
        printf("Platform created successfully.\n");
    }
}

bool addPost(Platform* platform, const char* username, const char* caption) 
{
    Post* newPost = createPost(username, caption);
    if (newPost == NULL) 
    {
        return false;
    }
    newPost->next = platform->posts;
    platform->posts = newPost;
    if (platform->lastViewedPost == NULL) 
    {
        platform->lastViewedPost = newPost;
    }
    return true;
}
bool deletePost(Platform* platform, int n) 
{
    if (platform->posts == NULL) 
    {
        printf("Error: No posts exist to delete.\n");
        return false;
    }
    if (n <= 0) 
    {
        printf("Error: Post index must be 1 or greater.\n");
        return false;
    }
    Post* current = platform->posts;
    Post* previous = NULL;
    int count = 1;
    while (current != NULL && count < n) 
    {
        previous = current;
        current = current->next;
        count++;
    }
    if (current == NULL) 
    {
        printf("Error: Post %d does not exist.\n", n);
        return false;
    }
    if (previous == NULL) 
    {
        platform->posts = current->next;
    } else {
        previous->next = current->next;
    }
    if (platform->lastViewedPost == current) 
    {
        platform->lastViewedPost = platform->posts;
    }
    current->next = NULL;
    destroyPost(current);
    printf("Post %d deleted successfully.\n", n);
    return true;
}

Post* viewPost(Platform* platform, int n) 
{
    Post* current = platform->posts;
    int count = 1;
    while (current != NULL && count < n)
    {
        current = current->next;
        count++;
    }
    if (current != NULL) 
    {
        platform->lastViewedPost = current;
        return current;
    }
    printf("Error: Post %d does not exist.\n", n);
    return NULL;
}

Post* currPost(Platform* platform) 
{
    if (platform->lastViewedPost == NULL) 
    {
        platform->lastViewedPost = platform->posts;
    }
    return platform->lastViewedPost;
}

Post* nextPost(Platform* platform) 
{
    Post* current = currPost(platform);

    if (current == NULL) 
    {
        printf("Next post does not exist (no posts).\n");
        return NULL;
    }
    if (current->next != NULL) 
    {
        platform->lastViewedPost = current->next;
        return platform->lastViewedPost;
    } else 
    {
        printf("Already at the oldest post. Staying here.\n");
        return current;
    }
}
Post* previousPost(Platform* platform) 
{
    Post* current = currPost(platform);
    if (current == NULL) 
    {
        printf("Previous post does not exist (no posts).\n");
        return NULL;
    }
    if (current == platform->posts) 
    {
        printf("Already at the most recent post. Staying here.\n");
        return current;
    }
    Post* search = platform->posts;
    while (search != NULL && search->next != current) 
    {
        search = search->next;
    }
    if (search != NULL) 
    {
        platform->lastViewedPost = search;
        return platform->lastViewedPost;
    }
    printf("Error in list structure while finding previous post.\n");
    return NULL;
}
bool addPlatformComment(Platform* platform, const char* username, const char* content) 
{
    Post* current = currPost(platform);
    if (current == NULL) 
    {
        printf("Error: Cannot add comment. No post has been viewed or exists.\n");
        return false;
    }
    return addComment(current, username, content);
}
bool deletePlatformComment(Platform* platform, int n) 
{
    Post* current = currPost(platform);
    if (current == NULL) 
    {
        printf("Error: Cannot delete comment. No post has been viewed or exists.\n");
        return false;
    }
    return deleteComment(current, n);
}

bool addPlatformReply(Platform* platform, const char* username, const char* content, int n) 
{
    Post* currentPost = currPost(platform);
    if (currentPost == NULL) 
    {
        printf("Error: Cannot add reply. No post has been viewed or exists.\n");
        return false;
    }
    return addReply(currentPost->comments, username, content, n);
}
bool deletePlatformReply(Platform* platform, int n, int m) 
{
    Post* currentPost = currPost(platform);
    if (currentPost == NULL) 
    {
        printf("Error: Cannot delete reply. No post has been viewed or exists.\n");
        return false;
    }
    return deleteReply(currentPost->comments, n, m);
}

void viewAllComments(Platform* platform) 
{
    Post* currentPost = currPost(platform);
    if (currentPost == NULL) 
    {
        printf("No post viewed or exists to show comments.\n");
        return;
    }
    printf("Comments on Post by %s\n", currentPost->username);
    Comment* comment = currentPost->comments;
    int commentCount = 1;
    if (comment == NULL) 
    {
        printf("(No comments yet.)\n");
    }
    while (comment != NULL) 
    {
        printf("\n[%d] %s: %s\n", commentCount, comment->username, comment->content);
        Reply* reply = comment->replies;
        int replyCount = 1;
        while (reply != NULL) 
        {
            printf("  -> [%d] %s: %s\n", replyCount, reply->username, reply->content);
            reply = reply->next;
            replyCount++;
        }
        comment = comment->next;
        commentCount++;
    }
}
void destroyPlatform(Platform* platform) 
{
    destroyPost(platform->posts);
    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    printf("Platform memory cleaned up.\n");
}
