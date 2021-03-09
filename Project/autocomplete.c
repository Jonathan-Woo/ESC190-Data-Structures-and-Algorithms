#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "autocomplete.h"

void remove_all_spaces(char *line){

    char *temp = (char *)malloc(sizeof(char) * 200);
    char **p_temp = &temp;
    strcpy(temp, line);

    int i = 0;
    while(temp[i] == ' '){
        i++;
    }

    *p_temp += i;
    strcpy(line, temp);
}

void remove_all_tabs(char *line){

    char *temp = (char *)malloc(sizeof(char) * 200);
    char **p_temp = &temp;

    strcpy(temp, line);
    *p_temp += 1;
    strcpy(line, temp);
}

int get_weight_to_cpy(char *line){

    char *temp = (char *)malloc(sizeof(char) * 200);
    char **p_temp = &temp;
    strcpy(temp, line);

    int weight = 0;
    int i = 0;

    while(temp[i] != '\t'){
        weight = (weight * 10) + (temp[i] - '0');
        i ++;
    }

    *p_temp += i;

    strcpy(line, temp);

    return weight;
}

void remove_newline(char *line){

    if(line[strlen(line) -1] != '\n'){
        return;
    }

    char *temp = (char *)malloc(sizeof(char) * 200);
    strcpy(temp, line);

    temp[strlen(temp) - 1] = '\0';
    strcpy(line, temp);
}

int compare_substrings(const char *s1, const char *s2){

    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);

    int max;
    int min;

    if(len_s1 <= len_s2){
        max = len_s2;
        min = len_s1;
    }
    else{
        max = len_s1;
        min = len_s2;
    }

    for(int j = 0; j < min; j++){
        if(s1[j] != s2[j]){
            return 1;
        }
    }

    return 0;
}

int compare_strings(const void* p1, const void* p2){

    struct term *term1 = (struct term *)p1;
    struct term *term2 = (struct term *)p2;

    int comparison = strcmp(term1 -> term, term2 -> term);

    return comparison;
}

int compare_floats(const void* p1, const void* p2){

    struct term *term1 = (struct term *)p1;
    struct term *term2 = (struct term *)p2;

    int comparison = (term2 -> weight) - (term1 ->weight);

    return comparison;
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){

    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);

    *terms = (struct term *)malloc(sizeof(struct term) * (*pnterms));


    for(int i = 0; i < *pnterms; i++){

        fgets(line, sizeof(line), fp);
        remove_all_spaces(line);
        double weight = get_weight_to_cpy(line);
        ((*terms)[i]).weight = weight;

        remove_all_tabs(line);
        remove_newline(line);
        strcpy(((*terms)[i]).term, line);
    }
    fclose(fp);
    qsort(*terms, *pnterms, sizeof(struct term), compare_strings);
}

int lowest_match(struct term *terms, int nterms, char *substr){

    int low = 0;
    int high = nterms - 1;
    int mid;

    while(high - low > 1){

        mid = (high + low) / 2;

        if(compare_substrings((terms[mid]).term, substr) == 0){
            high = mid;
        }
        else if(strcmp((terms[mid]).term, substr) > 0){
            high = mid;
        }
        else if(strcmp((terms[mid]).term, substr) < 0){
            low = mid;
        }
    }

    if(compare_substrings((terms[mid-1]).term, substr) == 0){
        return mid-1;
    }else if(compare_substrings((terms[mid]).term, substr) == 0){
        return mid;
    }
    else if(compare_substrings((terms[mid + 1]).term, substr) == 0){
        return mid + 1;
    }
    else{
        return -1;
    }
}

int highest_match(struct term *terms, int nterms, char *substr){

    int low = 0;
    int high = nterms - 1;
    int mid;

    while(high - low > 1){

        mid = (high + low)/ 2;

        if(compare_substrings((terms[mid]).term, substr) == 0){
            low = mid;
        }
        else if(strcmp((terms[mid]).term, substr) > 0){
            high = mid;
        }
        else if(strcmp((terms[mid]).term, substr) < 0){
            low = mid;
        }
    }

    if(compare_substrings((terms[mid+1]).term, substr) == 0){
        return mid+1;
    }
    else if(compare_substrings((terms[mid]).term, substr) == 0){
        return mid;
    }
    else if(compare_substrings((terms[mid - 1]).term, substr) == 0){
        return mid - 1;
    }
    else{
        return -1;
    }
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){

    int lowest_ind = lowest_match(terms, nterms, substr);
    int highest_ind = highest_match(terms, nterms, substr);

    if(lowest_ind == -1 || highest_ind == -1){
        *n_answer = 0;
    }else{
        *n_answer = highest_ind - lowest_ind;
        *answer = (struct term *)malloc(sizeof(struct term) * (*n_answer));

        for(int i = 0; i < highest_ind - lowest_ind + 1; i++){
            strcpy(((*answer)[i]).term, (terms[i + lowest_ind]).term);
            ((*answer)[i]).weight = (terms[i + lowest_ind]).weight;
        }

    }

    qsort(*answer, *n_answer, sizeof(struct term), compare_floats);
}

void print_terms(struct term *terms, int nterms){
    int i = 0;
    while(i < nterms){
        printf("Number: %d \t Term: %s \t Weight: %f \n", i + 1, (terms[i]).term, (terms[i]).weight);
        i++;
    }
}