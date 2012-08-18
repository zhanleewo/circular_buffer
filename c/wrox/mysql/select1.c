#include <stdlib.h>
#include <stdio.h>

#include <mysql/mysql.h> /* mysql API */

int main( int argc, char *argv[])
{
   MYSQL my_connection;
   MYSQL_RES *res_ptr;
   MYSQL_ROW sqlrow;
   int res;
 
   mysql_init(&my_connection);
  
   if(mysql_real_connect(&my_connection, "localhost", NULL, NULL, "foo", 
                                  0, NULL, 0))  {
       printf("Connection successful\n");

       res = mysql_query(&my_connection, 
                   "SELECT childno, fname, age FROM children WHERE age > 5");
       if(res) 
           printf("SELECT error: %s\n", mysql_error(&my_connection));    
       else  {
           res_ptr = mysql_store_result(&my_connection);
           if(res_ptr)  {
               printf("Retreived %lu rows\n", 
                (unsigned long)mysql_num_rows(res_ptr));
               while((sqlrow = mysql_fetch_row(res_ptr)))  
                   printf("Fetched data......\n");
               if(mysql_errno(&my_connection))
                   fprintf(stderr,"Retrieve error:%s\n",
                       mysql_error(&my_connection));
           }
           mysql_free_result(res_ptr);
       }           
       mysql_close(&my_connection);
   }
   else  {
       fprintf(stderr,"Connection failed\n");
       if(mysql_errno(&my_connection)) 
           fprintf(stderr, "Connection error %d: %s\n", 
           mysql_errno(&my_connection), mysql_error(&my_connection));
   }     
   
   return EXIT_SUCCESS;
}

