#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "fuck_praxis1.txt");
    print_terms(terms, nterms);

    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    //free allocated blocks here -- not required for the project, but good practice

    return 0;
}

