#ifndef CSVLIB_H_INCLUDED
#define CSVLIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


#define DIGIT_BIT 0x01
#define ALPHA_BIT 0x02
#define DOT_BIT 0x04

struct CSV_obj{
    char ***table;
    int **classificationTable;
    int rows;
    int cols;
};

enum TokenDataType{
    INTEGER, FLOAT, STRING
};

FILE *loadCSVFile(const char* file);
void countRowCols(FILE* arq, struct CSV_obj *csvobj);
void createTable(struct CSV_obj *csv_counter, FILE* arq);
void createClassificationTable(struct CSV_obj *csvobj);
void printDataTable(struct CSV_obj *csvobj);
void printClassificationTable(struct CSV_obj *csvobj);
struct CSV_obj constructCSVTable(const char* filename);
enum TokenDataType classifyToken(char *token);



#endif // CSVLIB_H_INCLUDED
