#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "autocomplete.h"

void remove_spaces(char* term) {
    /*
     * removes leading spaces from a string term
     */
    //duplicate the string
    char temp[200];
    strcpy(temp, term);

    //modify the temporary string
    int i = 0;
    while (temp[i] == ' ') {
        i++;
    }

    //copy the modified string back to the original location
    strcpy(term, temp + i);
}

int get_weight(char* term) {
    /*
     * removes adjacent integers in front of string term
     * returns integer
     */
    //duplicate the string
    char temp[200];
    strcpy(temp, term);

    //initialize total sum
    int weight = 0;

    //modify the temporary string
    int i = 0;
    while (temp[i] != '\t') {
        //char - '0' is a trick to convert a char to an int
        //recall that atoi/atof is for strings
        weight = (weight * 10) + (temp[i] - '0');
        i++;
    }

    //copy the modified string back to the original location
    strcpy(term, temp + i);

    return weight;
}

void remove_tab(char* term) {
    /*
     * removes tab from the beginning of a string **term
     * advance the string by one byte to skip the tab
     */

    //duplicate the string
    char temp[200];
    strcpy(temp, term);

    //modify the temporary string
    //copy the modified string back to the original location
    strcpy(term, temp + 1);
}

void remove_newline(char* term) {
    /*
     * removes newline (\n) from the end of a string *term
     * At the end of each line, we're not sure if the line break is \r\n
     * or just \n. So we check for both.
     */
    if (term[strlen(term) - 1] != '\n') {
        return;
    }

    //duplicate the string
    char temp[200];
    strcpy(temp, term);

    //modify the temporary string
    if (temp[strlen(temp) - 2] == '\r') {
        temp[strlen(temp) - 2] = '\0';
    }
    else if(temp[strlen(temp) - 1] == '\n') {
        temp[strlen(temp) - 1] = '\0';
    }

    //copy the modified string to the original location
    strcpy(term, temp);
}

int compare_term(const void* p1, const void* p2) {
    /*
     * compare function for qsort.
     * Compares using strcmp to determine ASCII value and
     * qsort will swap each struct term if ASCII difference is positive
     */
    struct term* termA = (struct term*)p1;
    struct term* termB = (struct term*)p2;

    //strcmp is positive if first term has a higher ASCII value
    //negative if second term has higher ASCII value
    //therefore sorting by ascending ascii value
    return(strcmp(termA->term, termB->term));
}

void read_in_terms(struct term** terms, int* pnterms, char* filename) {
    //open the file
    FILE* fp = fopen(filename, "r");

    //set the line size
    char line[200];

    //get the number of lines
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);

    //allocate memory for the number of struct terms
    *terms = (struct term*)malloc(sizeof(struct term) * (*pnterms));

    //go through each line
    //read each line into the term property of each struct term
    int i;
    for (i = 0; i < *pnterms; i++) {
        fgets(line, sizeof(line), fp);
        strcpy(((*terms)[i]).term, line);
    }

    //breakup and manipulate the read in terms
    /*
     * 1. remove leading spaces
     * 2. get weights
     * 3. remove tabs
     * 4. remove newline characters
     */
    for (i = 0; i < *pnterms; i++) {
        remove_spaces(((*terms)[i]).term);
        ((*terms)[i]).weight = get_weight(((*terms)[i]).term);
        remove_tab(((*terms)[i]).term);
        remove_newline(((*terms)[i]).term);
    }

    /*
     * Now sort lexicographically. qsort takes an array so we pass in
     * the array of struct terms. We sort using compare function above
     */

    fclose(fp);
    qsort(*terms, *pnterms, sizeof(struct term), compare_term);
}

int check_substring(char* word, char* substring) {
    /*
     * checks if a substring substring is in a string string
     * returns 1 for true, 0 for false
     */
    int i = 0;
    while (substring[i] != '\0' && word[i] != '\0' && word[i] == substring[i]){
        i++;
    }
    if (substring[i] == '\0') {
        return 1;
    }
    else{
        return 0;
    }
}

int lowest_match(struct term* terms, int nterms, char* substr) {
    /*
     * finds the lowest index of a string substr in array terms
     * with nterms
     */
    int head = 0;
    int tail = nterms - 1;
    int mid = 0;

    while (head <= tail) {
        //find the middle of the list
        mid = (head + tail) / 2;

        //keep track of the head and tail of the list
        //solution when they converge

        if (check_substring((terms[mid]).term, substr) == 1) {
            //if the middle term contains the substring, we make our way advance
            //to the left of the string until we get the leftmost element
            //that is the solution
            while (mid >= head && check_substring(terms[mid].term, substr) == 1){
                mid--;
            }
            return mid + 1;
        }
        else if(strcmp((terms[mid]).term, substr) > 0) {
            //strcmp is positive if left term has higher ASCII value
            //since terms are in ascending order, a positive strcmp
            //means that substr is on the left of mid
            tail = mid - 1;
        }
        else if(strcmp((terms[mid]).term, substr) < 0) {
            //we exclude the situation where strcmp() = 0 because that would be caught by
            //check_substring()
            head = mid + 1;
        }
    }
    return -1;
}

int highest_match(struct term* terms, int nterms, char* substr) {
    /*
     * finds the highest index of a string substr in an array terms
     * with nterms
     */
    int head = 0;
    int tail = nterms - 1;
    int mid = 0;

    while (head <= tail) {
        //find the middle of the list
        mid = (head + tail) / 2;

        //keep track of the head and tail of the list
        //solution when they converge

        if (check_substring((terms[mid]).term, substr) == 1) {
            //if the middle term contains the substring, we make our way advance
            //to the right of the string until we get the rightmost element
            //that is the solution
            while(mid <= tail && check_substring(terms[mid].term, substr)){
                mid++;
            }
            return mid - 1;
        }
        else if (strcmp((terms[mid]).term, substr) > 0) {
            //strcmp is positive if left term has higher ASCII value
            //since terms are in ascending order, a positive strcmp
            //means that substr is on the left of mid
            tail = mid - 1;
        }
        else if (strcmp((terms[mid]).term, substr) < 0) {
            //we exclude the situation where strcmp() = 0 because that would be caught by
            //check_substring()
            head = mid + 1;
        }
    }
    return -1;
}

int compare_weight(const void* p1, const void* p2) {
    /*
     * compare function for qsort.
     * compares weight difference between terms such that
     * the final list is sorted descending order
     */
    struct term* termA = (struct term*)p1;
    struct term* termB = (struct term*)p2;

    //strcmp is positive if first term has a higher ASCII value
    //negative if second term has higher ASCII value
    //therefore sorting by ascending ascii value
    return(int)(termB->weight - termA->weight);
}

void autocomplete(struct term** answer, int* n_answer, struct term* terms, int nterms, char* substr) {
    /*
     * sets all terms in terms to array of struct *answer such that they
     * are possible solutions to the string query substr
     */
    //with q2, we can find the first and last index of which substr is a substring
    int head = lowest_match(terms, nterms, substr);
    int tail = highest_match(terms, nterms, substr);

    if (head == -1 && tail == -1) {
        *n_answer = 0;
    }
    else {
        //now that we have the first and last index, we can copy the terms with substr
        //to the answer array
        *n_answer = tail - head + 1;
        *answer = (struct term*)malloc(sizeof(struct term) * (*n_answer));

        int i;
        for (i = 0; i < *n_answer; i++) {
            strcpy(((*answer)[i]).term, (terms[head + i]).term);
            ((*answer)[i]).weight = (terms[head + i]).weight;
        }

        //with the new array, we must now sort by weight
        qsort(*answer, *n_answer, sizeof(struct term), compare_weight);
    }
}