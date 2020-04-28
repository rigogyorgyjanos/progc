#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


typedef struct{
    char ido[15];
    int szamok[5];
} LOTTO;

typedef struct{
    LOTTO adatbazis[1000];
    int hossz;
} LottoDB;

int rendez(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
}
void readFromCSV(LottoDB *db){
    FILE *f = fopen("otosrovid.csv","r");
    if (f == NULL)
    {
        perror("Nem jó");
        exit(1);
    }
    LOTTO record;
    char sor[100];
    while(fscanf(f,"%s",sor) == 1)
    {
        char *token = strtok(sor,";");
        strcpy(record.ido, token);
        //puts(token);
        int i = 0;
        while (token != NULL)
        {
            token = strtok(NULL,"; \n");
            record.szamok[i] = atoi(token);
            i++;
        }
        
        //qsort(record.szamok,5,sizeof(int),rendez);
        
        db->adatbazis[db->hossz] = record;
        db->hossz++;
    }
    
    fclose(f);

}
void listing(LottoDB *db){
    for (int i = 0; i < db->hossz; i++)
    {
        printf("%s: %d, %d, %d, %d, %d\n",db->adatbazis[i].ido, db->adatbazis[i].szamok[0]
                                                            , db->adatbazis[i].szamok[1], db->adatbazis[i].szamok[2]
                                                            , db->adatbazis[i].szamok[3], db->adatbazis[i].szamok[4]);
    }
    
}

void win(LottoDB *db, int inputNums[] ){
    int k = 0,h = 0,n = 0, o = 0;
    /*for (int i = 0; i < 5; i++)
    {
        printf("%d ",inputNums[i]);
    }*/
    for (int i = 0; i < db->hossz; i++)
    {
        int match = 0;
        for (int j = 0; j < 5; j++)
        {
            if (db->adatbazis[i].szamok[j] == inputNums[j])
            {
                match++;
            }
            
        }
        
        switch (match)
        {
        case 2:
            printf("KETTES: %s\n",db->adatbazis[i].ido);
            k++;
            break;
        case 3:
            printf("HARMAS: %s\n",db->adatbazis[i].ido);
            h++;
            break;
        case 4:
            printf("NEGYES: %s\n",db->adatbazis[i].ido);
            n++;
            break;
        case 5:
            printf("OTOS: %s\n",db->adatbazis[i].ido);
            o++;
            break;

        default:
            break;
        }
    }
        printf("KETTES: %d.\nHARMAS: %d.\nNEGYES: %d.\nOTOS: %d.\n",k,h,n,o);
        
}

int main()
{
    LottoDB db;
    db.hossz = 0;
    
    readFromCSV(&db);
    //printf("%d\n",db.hossz);
    //listing(&db);
    puts("Write your numbers");
    int inputNums[5];
    for (int i = 0; i < 5; i++)
    {
        scanf(" %d",&inputNums[i]);
    }
    
    
    qsort(inputNums,5,sizeof(int),rendez);
    
    win(&db,inputNums);
    
    

    
    return 0;
}
