#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "platform.h"
Platform socialMediaPlatform;
void read_input(char* buffer, int size) 
{
      if (fgets(buffer, size, stdin) != NULL) 
      {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') 
            {
                  buffer[len - 1] = '\0';
            }
      }
}
void displayPost(Post* post)
{
      if (post != NULL) 
      {
            printf("Post Details:\n");
            printf("   Username: %s\n", post->username);
            printf("   Caption: %s\n", post->caption);
      } else 
      {
            printf("Error: Post is NULL.\n");
      }
}
int main() 
{
      createPlatform(&socialMediaPlatform);
      char command[100];
      char arg1[256] = "";
      char arg2[256] = "";
      int n = 0;
      int m = 0;
      printf("Welcome to the Social Media Platform CLI.\n");
      printf("Enter commands (e.g., add post user1 caption1, view post 1, current post, exit):\n");
      printf("--- Valid Commands ---\n");
      printf("create platform\n");
      printf("add post <user> <caption_text>\n");
      printf("delete post <n>\n");
      printf("view post <n>\n");
      printf("current post\n");
      printf("next post\n");
      printf("previous post\n");
      printf("add comment <user> <content_text>\n");
      printf("delete comment <n>\n");
      printf("view all comments\n");
      printf("add reply <user> <content_text> <n_comment>\n");
      printf("delete reply <n_comment> <m_reply>\n");
      printf("exit\n");
      while (1) 
      {
            printf("\n> ");
            read_input(command, sizeof(command));
            if (sscanf(command, "add post %s %s", arg1, arg2) >= 2) 
            {
                  printf("--- Post added ---\n");
                  addPost(&socialMediaPlatform, arg1, arg2);
            } 
            else if (sscanf(command, "delete post %d", &n) == 1) 
            {
                  deletePost(&socialMediaPlatform, n);
            } 
            else if (sscanf(command, "view post %d", &n) == 1) 
            {
                  Post* p = viewPost(&socialMediaPlatform, n);
                  displayPost(p);
            } 
            else if (sscanf(command, "add comment %s %s", arg1, arg2) >= 2) 
            {
                  if (addPlatformComment(&socialMediaPlatform, arg1, arg2)) 
                  {
                        printf("Comment added to last viewed post.\n");
                  }
            } 
            else if (sscanf(command, "delete comment %d", &n) == 1) 
            {
                  deletePlatformComment(&socialMediaPlatform, n);
            } 
            else if (sscanf(command, "add reply %s %s %d", arg1, arg2, &n) == 3) 
            {
                    if (addPlatformReply(&socialMediaPlatform, arg1, arg2, n)) 
                    {
                        printf("Reply added to comment %d.\n", n);
                  }
            }
            else if (sscanf(command, "delete reply %d %d", &n, &m) == 2) 
            {
                  deletePlatformReply(&socialMediaPlatform, n, m);
            }
            // --- 2. COMMANDS WITH NO ARGUMENTS (Using strncmp) ---
            
            else if (strncmp(command, "create platform", 15) == 0) 
            {
                  createPlatform(&socialMediaPlatform);
            } 
            else if (strncmp(command, "current post", 12) == 0) 
            {
                  Post* p = currPost(&socialMediaPlatform);
                  displayPost(p);
            } 
            else if (strncmp(command, "next post", 9) == 0) 
            {
                  Post* p = nextPost(&socialMediaPlatform);
                  displayPost(p);
            } 
            else if (strncmp(command, "previous post", 13) == 0) 
            {
                  Post* p = previousPost(&socialMediaPlatform);
                  displayPost(p);
            } 
            else if (strncmp(command, "view all comments", 17) == 0) 
            {
                  viewAllComments(&socialMediaPlatform);
            } 
            else if (strncmp(command, "exit", 4) == 0) 
            {
                  printf("Exiting program. Cleaning up memory...\n");
                  destroyPlatform(&socialMediaPlatform);
                  break;
            } 
            else 
            {
                  if (strlen(command) > 0) 
                  {
                        printf("Unknown command: %s. Please try again.\n", command);
                  }
            }
        }
      return 0;
}
