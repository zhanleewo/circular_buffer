#include "ourheader.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{  
   int accmode, val;
   
   if(argc != 2)
       err_quit("usage a.out <descriptor no.>");

   if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
       err_sys("fcntl error for fd %d", atoi(argv[1]));
   
   accmode = val & O_ACCMODE;
   if(accmode == O_RDONLY)  printf("read only\n");
   else if(accmode == O_WRONLY) printf("write only\n");
   else if(accmode == O_RDWR) printf("read and write\n");
   else printf("unknown access mode \n");

   if (val & O_APPEND) printf("append mode\n");
   if (val & O_NONBLOCK) printf("non block mode\n");
   #if !defined (_POSIX_SOURCE) && defined(O_SYNC)
       if (val & O_SYNC) printf("synchronous writes\n");
   #endif

   
   return 0;
} 
