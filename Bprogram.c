#include<stdio.h>
#include<stdlib.h>

#define INIT_CAPACITY 1

typedef struct 
{
    int *elems;
    int length;
    int capacity;
} DynArray;


void my_error_exit(){
    fprintf(stderr,"Error: Cannot allocate memory!");
    exit(1);
}

DynArray * da_create(){
    DynArray *result = malloc(sizeof(DynArray));
    if (result == NULL)
    {
        my_error_exit();    
    }
    
    
    result->elems = malloc(INIT_CAPACITY * sizeof(int));
    result->capacity = INIT_CAPACITY;
    result->length = 0;

    return result;
}

void da_append(DynArray *self, int data){
    if (self->capacity == self->length)
    {
        int new_capacity = 2 * self->capacity;
        self->elems = realloc(self->elems, new_capacity * sizeof(int));
        if (self->elems == NULL)
        {
            my_error_exit();
        }
        self->capacity = new_capacity;
    }

    self->elems[self->length] = data;
    self->length  += 1;
    

}
void da_destroy(DynArray *self){
    free(self->elems);
    free(self);
}
int read_from_file(FILE *f, DynArray *list){
    int num, sum = 0;
    for (int i = 0; i < 100; i++)
    {
        fscanf(f,"%d",&num);
        sum += num;
        da_append(list,num);
    }
    //printf("%d\n",sum);
    return sum;
}

int main()
{
    FILE *f = fopen("numbers.txt","rt");
    if (f == NULL)
    {
        perror("Nope");
        exit(1);
    }

    DynArray *list = da_create();
    
    int summa = read_from_file(f,list);
    printf("%.2lf",(float)summa/100);
    
    
    fclose(f);
    da_destroy(list);


    
    return 0;
}
