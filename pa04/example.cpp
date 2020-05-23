#include <stdio.h>
#include <sys/time.h>
#include <ctime>

long long int toddiff(struct timeval *tod1, struct timeval *tod2)
{
    long long t1, t2;
    t1 = tod1->tv_sec * 1000000 + tod1->tv_usec;
    t2 = tod2->tv_sec * 1000000 + tod2->tv_usec;
    return t1 - t2;
}
 
int main()
{
   struct timeval tod1, tod2;
   clock_t t1, t2;
 
    t1 = clock();
   // Slurp CPU for 1 second. 
   gettimeofday(&tod1, NULL);
   do
   {
      gettimeofday(&tod2, NULL);
   } while(toddiff(&tod2, &tod1) < 1000000);
 
   printf("Hit enter...");
   (void)getchar();
    
   t2 = clock();
   gettimeofday(&tod2, NULL);
   printf("timeofday %5.2f seconds, clock %5.2f seconds\n", toddiff(&tod2, &tod1) / 1000000.0, (t2-t1)/(double)CLOCKS_PER_SEC);
 
   return 0;
}
