#include <stdlib.h>
#include <stdio.h>
#include "autocomplete.h"

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    /*
     * reads in all the lines of filename *filename and associates the number of items
     * with *pnterms
     *
     * allocates memory for all the terms in the file and stores a pointer to the block in
     * *terms.
     */

    //first, we must read the file in
    FILE *fp = fopen(*filename, "r");

    char line_1[1];

    //get the number of lines
    fgets(line_1, sizeof(line_1), fp);

    //determine the number of lines
    int number_of_lines = atoi(line_1);

    //with the number of lines, we can now define the size of the
    //char array
    char line[number_of_lines];

    for(int i = 0; i < N; i++){
        fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters
        //(including '\0') into line.
    }
}
