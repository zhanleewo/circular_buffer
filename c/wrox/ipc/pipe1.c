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
   
   memset(buffer, '\0', sizeof(buffer));
   
   if(pipe(file_pipes) == 0) {
       data_processed = write(file_pipes[1], some_data, strlen(some_data));
       printf("wrote %d bytes\n", data_processed);
       data_processed = read(file_pipes[0], buffer, BUFSIZ);
       printf("Read %d bytes: %s\n", data_processed, buffer);
       exit(EXIT_SUCCESS);
   }   
   exit(EXIT_FAILURE);
}
