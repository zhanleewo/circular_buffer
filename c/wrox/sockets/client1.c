/* +--------------------------------------------------------------------+ */
/* |              This is a client program                              | */
/* +--------------------------------------------------------------------+ */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

int main(void)
{
   int sockfd, len, result;
   char ch = 'A';
   struct sockaddr_un address;
  
   sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   address.sun_family = AF_UNIX;
   strcpy(address.sun_path, "server_socket");
   len = sizeof(address);

   result = connect(sockfd, (struct sockaddr *)&address, len);
   if(result == -1)  {
       perror("oops: client1");
       exit(EXIT_FAILURE);
   }
   
   write(sockfd, &ch, 1);
   read(sockfd, &ch, 1);
   printf("char from server = %c\n", ch);
   close(sockfd);

   exit(EXIT_SUCCESS);
   
} /* end main */
 
