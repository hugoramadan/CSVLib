#include "CSVLib.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

FILE* loadCSVFile(const char* file){

    FILE *arq;

    if(!(arq = fopen(file, "r"))){
        printf("Cannot open file: %s\n", file);
        /*exit(1)*/;
    }

    return arq;
}

void countRowCols(FILE* arq, struct CSV_obj *csvobj){
    rewind(arq);

    csvobj->cols = 1;
    csvobj->rows = 1;

    char ch;

    int endColsCount = 0;
    ch = getc(arq);
    while(ch != EOF){
        if (ch == ',' && !endColsCount){
            printf("Comma found");
            csvobj->cols++;
        }
        if (ch == '\n'){
            //printf("CRLF found");
            csvobj->rows++;
            endColsCount = 1;
        }
        ch = getc(arq);
    }
}

void createTable(struct CSV_obj *csvobj, FILE *file){

    csvobj->table = (char***)malloc(csvobj->rows*sizeof(char**));

    for (int i = 0; i < csvobj->rows; ++i){
        csvobj->table[i] = (char**)malloc(csvobj->cols*sizeof(char*));
    }

    char line[100];

    rewind(file);

    //printf("Rows = %d\n", csvobj->rows);
    //printf("Cols = %d\n", csvobj->cols);

    for (int i=0; i < csvobj->rows; i++){

        fgets(line, 100, file);
        char* token;
        char* crlf;
        token = strtok(line,",");
        if((crlf = strchr(token,'\n'))){
            *crlf = '\0';
        }

        csvobj->table[i][0] = (char*)malloc(strlen(token));
        strcpy(csvobj->table[i][0], token);

        for (int j=1; j < csvobj->cols; j++){

            token = strtok(NULL,",");
            if((crlf = strchr(token,'\n'))){
            *crlf = '\0';
            }
            csvobj->table[i][j] = (char*)malloc(strlen(token));
            strcpy(csvobj->table[i][j], token);
        }
    }
}

void printDataTable(struct CSV_obj *csvobj){

    //printf("printTable\n");
    for (int i=0; i < csvobj->rows; i++){
        for (int j=0; j < csvobj->cols; j++){
            printf("%s ",(csvobj->table[i][j]));
        }
        printf("\n");
    }

}

struct CSV_obj constructCSVTable(const char* filename){

    FILE *arq;
    struct CSV_obj c;

    arq = loadCSVFile(filename);

    countRowCols(arq, &c);

    createTable(&c,arq);

    createClassificationTable(&c);

    fclose(arq);

    return c;
}

enum TokenDataType classifyToken(char *token){
    char control = 0;

    while(*token) {
        if (isdigit(*token)) control |= DIGIT_BIT;
        else if (isalpha(*token)) control |= ALPHA_BIT;
        else if (*token == '.') control |= DOT_BIT;
        token++;
    }

    if (control == DIGIT_BIT) return INTEGER;
    else if (control == (DIGIT_BIT | DOT_BIT)) return FLOAT;
    else return STRING;


};

void createClassificationTable(struct CSV_obj *csvobj){
    csvobj->classificationTable = (int**)malloc(csvobj->rows*sizeof(int*));

    for (int i = 0; i < csvobj->rows; ++i){
        csvobj->classificationTable[i] = (int*)malloc(csvobj->cols*sizeof(int));
    }

    for (int i = 0; i < csvobj->rows; i++){
        for(int j = 0; j < csvobj->cols; j++){
            csvobj->classificationTable[i][j] = classifyToken(csvobj->table[i][j]);
        }
    }
}

void printClassificationTable(struct CSV_obj *csvobj){

    for (int i=0; i < csvobj->rows; i++){
        for (int j=0; j < csvobj->cols; j++){
            printf("%d ",(csvobj->classificationTable[i][j]));
        }
        printf("\n");
    }
}
