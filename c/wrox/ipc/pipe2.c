/**************************************************************************/
/* this one demonstrate the use of pipe  through lowlevel pipe call    ****/
/**************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
   int data_processed;
   int file_pipes[2];
   const char some_data[] = "123";
   char buffer[BUFSIZ + 1];
   pid_t fork_result; 
   
   memset(buffer, '\0', sizeof(buffer));
   
   if(pipe(file_pipes) == 0) { 
       fork_result = fork();
       if(fork_result == -1) {
           fprintf(stderr, "fork failure");
           exit(EXIT_FAILURE);
       }
       if(fork_result == 0) {
           data_processed = read(file_pipes[0], buffer, BUFSIZ);
           printf("read %d bytes: %s \n", data_processed, buffer);
           exit(EXIT_SUCCESS);
       }
       else  {
           data_processed = write(file_pipes[1], some_data, 
                                                           strlen(some_data));
           printf("wrote %d bytes\n", data_processed);
       }    
   }   
   exit(EXIT_SUCCESS);
}
