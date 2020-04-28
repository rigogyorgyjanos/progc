#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int main(int argc, char const *argv[])
{
    /* code */
    srand(time(0)); 
    FILE *f = fopen("numbers.txt","wt");
    if (f == NULL)
    {
        perror("Somting went wrong!");
        exit(1);
    }
    
    for (int i = 0; i < 100; i++)
    {
        /* code */
        int r  = rand() % 90 + 10;
        fprintf(f,"%d\n",r);

    }
    
    return 0;
}
