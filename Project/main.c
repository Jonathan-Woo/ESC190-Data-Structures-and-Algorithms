#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "fuck_praxis1.txt");
    print_terms(terms, nterms);

    int pos1 = lowest_match(terms, nterms, "Tor");
    int pos2 = highest_match(terms, nterms, "Tor");

    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "insinuated");
    print_terms(answer, n_answer);
    //free allocated blocks here -- not required for the project, but good practice

    return 0;
}

