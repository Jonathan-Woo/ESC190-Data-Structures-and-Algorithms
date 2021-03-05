#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
//    print_terms(terms, nterms);

    int sol1 = lowest_match(terms, nterms, "Tor");
    int sol2 = highest_match(terms, nterms, "Tor");

//    printf("Loc 1: %d \t Loc 2:%d \n", sol1, sol2);

    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    print_terms(answer, n_answer);

    free(terms);
    free(answer);

    return 0;
}
