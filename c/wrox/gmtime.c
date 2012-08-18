#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
   struct tm *tm_ptr;/*pointer to time stucture*/
   time_t the_time;
   
   (void) time(&the_time);/*time function stores the value in the_time*/
   tm_ptr = gmtime(&the_time);
   
   printf("Raw time is %ld\n", the_time);
   printf("gmtime gives : \n");
   printf("date : %02d/%02d/%02d\n", tm_ptr->tm_year+1900, 
                        tm_ptr->tm_mon+1, tm_ptr->tm_mday);

   printf("time : %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min, 
                                                      tm_ptr->tm_sec);
   
   exit(0);

}
