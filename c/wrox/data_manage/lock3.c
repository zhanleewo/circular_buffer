/* ---------------------------------------------------------------------- */
/*  This shows use of fcntl function and see how file lock work           */
/* ********************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

const char *test_file = "/tmp/lock_test";

int main(void)
{
   int file_desc;
   int byte_count, res;
   char *byte_to_write = "A";
   struct flock region_1;
   struct flock region_2;
   
   file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
   if(!file_desc)  {
       fprintf(stderr, "unable to open test file %s", test_file);
       exit(EXIT_FAILURE);
   }
       
   for(byte_count = 0; byte_count < 100; byte_count++)
       (void)write(file_desc, byte_to_write, 1);
   
   region_1.l_type = F_RDLCK;
   region_1.l_whence = SEEK_SET;
   region_1.l_start = 10;
   region_1.l_len = 20; 
  
   region_2.l_type = F_WRLCK;
   region_2.l_whence = SEEK_SET;
   region_2.l_start = 40;
   region_2.l_len = 10; 
   
   printf("process %d locking file\n", getpid());
   res = fcntl(file_desc, F_SETLK, &region_1); /* set lock to first region*/
   if(res == -1) fprintf(stderr, "failed to lock region 1\n");
   res = fcntl(file_desc, F_SETLK, &region_2); /* set lock to second region*/
   if(res == -1) fprintf(stderr, "failed to lock region 2\n");
   sleep(60);
   
   printf("process %d closing file\n", getpid());
   close(file_desc);
   exit(EXIT_SUCCESS);
}