#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

typedef struct Szo {
    char magyar[50+1];
    char angol[50+1];
} Szo;

typedef struct Szotar {
    Szo szavak[3000];
    int db;
} Szotar;

void ekezetesBetuk(){
    setlocale(LC_ALL, "hu_HU.ISO88592");
    #if defined(WIN32) || defined(_WIN32)
    SetConsoleCP(1250); SetConsoleOutputCP(1250);
    #endif
}

char *filename = {"dictionary.txt"};
void shema(char word[51]){
    for(int i = 0; i < (sizeof(word)/sizeof(char)); i++){
        if(isupper(word[i])){
            word[i] = tolower(word[i]);
        }
    }

}

bool load(char *filename, Szotar *dic){
    FILE *f = fopen(filename, "r");
    if(f == NULL){
        perror("Error during loading dictionary!");
        return false;
    }
    Szo word;
    while(fscanf(f," %[^\t] %[^\n]", word.magyar, word.angol) == 2){
        dic->szavak[dic->db] = word;
        dic->db++;
    }
    fclose(f);
    return true;
}

int alreadyHas(Szotar *dic, char *word){
        for(int i = 0; i < dic->db; i++){
            if((strcmp(dic->szavak[i].angol,word) == 0) || (strcmp(dic->szavak[i].magyar,word) == 0)){

                return i;
            }
        }
        return -211;
}
bool getNewRecord(Szotar *dic, char *filename){
    puts("Szeretné felvenni a szótárba?(y/n)");
    char magyar[51],angol[51];

    char valasz;
    scanf(" %c",&valasz);
    if(valasz == 121){
        puts("Kérem a magyar és angol szót. (magyar angol)");
        scanf("%s %s",magyar,angol);
        shema(magyar);
        shema(angol);
        strcpy(dic->szavak[dic->db].magyar,magyar);
        strcpy(dic->szavak[dic->db].angol,angol);
        dic->db++;

        FILE *f = fopen(filename,"a");
        if(f == NULL){
            perror("Can't save the dictionary!");
            return false;
        }
        fprintf(f,"%s\t%s\n",magyar,angol);

        fclose(f);
        puts("Sikeres mentés!");
        return true;

    }
    return false;
}


void wordSearch(Szotar *dic, char *word){

    int index = alreadyHas(dic, word);

    if(index != -211){
        printf("%s\t%s\n",dic->szavak[index].magyar,dic->szavak[index].angol);
    }else{
        puts("NINCS BENNE ");
        getNewRecord(dic,filename);
    }
}


/**************************** MAIN ********************************************************/
int main()
{
    ekezetesBetuk(); // �kezet miatt

    Szotar dic;
    dic.db = 0;
    char *filename = {"dictionary.txt"};
    if(load(filename,&dic)){
        puts("---- Load dictionary ----");
    }
    else{
        puts("---- Error during load dictionary ----");
    }

    char word[51];
    do{

        puts("Kérem írjon be egy szót! ('q' - kilépés )");
        scanf("%s",word);
        shema(word);
        if(strcmp("q",word) == 0){
            break;
        }
        wordSearch(&dic,word);

    }while(1);

    return 0;

}
