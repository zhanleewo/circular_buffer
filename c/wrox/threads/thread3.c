/* +-----------------------------------------+ */
/* |                                         | */   
/* |                                         | */   
/* this uses semaphores to create new threads */
/* |                                         | */   
/* |                                         | */   
/* +-----------------------------------------+ */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h> /* | INCLUDE SEMAPHORE LIBRARY | */

#define WORK_SIZE 1024

void *thread_function(void *arg);

sem_t bin_sem;
char work_area[WORK_SIZE];


int main(void)
{
   int res;
   pthread_t a_thread;
   void *thread_result;
   
   res = sem_init(&bin_sem, 0, 0);
   if(res != 0)  {
       perror("Semaphore initialization failed");
       exit(EXIT_FAILURE);
   }

   res = pthread_create(&a_thread, NULL, thread_function, NULL);
   if(res != 0)  {
       perror("Thread creation failed");
       exit(EXIT_FAILURE);
   }

   printf("Input some text here and enter 'end ' to finish\n");
   while(strncmp("end", work_area, 3) != 0)  {
       fgets(work_area, WORK_SIZE, stdin);
       sem_post(&bin_sem);
   }

   printf(" waiting for thread to finish......\n");
   res = pthread_join(a_thread, &thread_result);
   if(res != 0)  {
       perror("thread joining failed");
       exit(EXIT_FAILURE);
   }

   printf("Thread joined, it returned \n"); 
   sem_destroy(&bin_sem); 
   exit(EXIT_SUCCESS);

}

void *thread_function(void *arg) 
{
   sem_wait(&bin_sem);
   
   while(strncmp("end", work_area, 3) != 0)  {
       printf("You input %d character\n", strlen(work_area) - 1);
       sem_wait(&bin_sem);
    }
   pthread_exit(NULL);
} 
