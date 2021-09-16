#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "CSVLib.h"

int main(){

    setlocale(LC_ALL, "");

    struct CSV_obj c;

    c = constructCSVTable("dados.csv");

    printDataTable(&c);

    printClassificationTable(&c);

    free(c.table);

    return 0;
}

