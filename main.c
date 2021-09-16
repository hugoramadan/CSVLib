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

    overwriteItem(&c,1,0, "Outro Nome Qualquer Que Seja");

    printDataTable(&c);

    exportCSV(&c, "novocsv.csv");

    free(c.table);

    return 0;
}

