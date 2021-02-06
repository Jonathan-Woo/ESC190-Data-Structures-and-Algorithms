#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int my_strlen(char *s1){
    /*
     * returns the size of a string starting at s1
     */
    int length = 0;
    while(*s1 != '\0'){
        length++;
        s1++;
    }
    return length;
}

void my_strcomb_skip1(char *s1, char *s2){
    /*
     * appends s2 to s1 whilst skipping the first character
     * of s2. Assuming s1 is of sufficient size and empty
     */
    int i;

    for(i = 1; i < my_strlen(s2); i++){
        s1[i - 1] = s2[i];
    }
}

int my_str_cmp_rec(char *str1, char *str2){
    /*
     * Finds the difference in ASCII code between str1
     * and str2 for the first character different
     */
    //base case
    //if either string null, we return their difference
    //if len(str1) < len(str2), in lexicographic order,
    //str1 comes before str2 and that results in 0 - some_positive_int
    //therefore negative.
    if(str1[0] == '\0' || str2[0] == '\0'){
        return str1[0] - str2[0];
    }

    if(str1[0] == str2[0]){
        //We're going to be passing strings into the recursive function
        //so we must make new strings each iteration.
        //Here, we are making new strings of length 1 size less than
        //the original since we are chopping off the first character

        //These cases are necessary because when the strings are len = 1
        //we can't create new strings of len = 0
        if(my_strlen(str1) == 1 && my_strlen(str2) == 1){
            return 0;
        }else if(my_strlen(str1) == 1){
            return -str2[1];
        }else if(my_strlen(str2) == 1){
            return str1[1];
        }

        //Here we create new strings to pass on
        char new_str1[my_strlen(str1) - 1];
        char new_str2[my_strlen(str2) - 1];
        my_strcomb_skip1(new_str1, str1);
        my_strcomb_skip1(new_str2, str2);

        //recursive call
        my_str_cmp_rec(new_str1, new_str2);
    }else{
        //if the characters are different, we have a solution
        return str1[0] - str2[0];
    }
    return 0;
}

char *my_strcat(char *dest, char *src){
    char new_string[my_strlen(dest) + my_strlen(src) + 1];

    int i;
    for(i = 0; i < my_strlen(dest); i++){
        new_string[i] = dest[i];
    }

    for(i = 0; i < my_strlen(src); i++){
        new_string[my_strlen(dest) + i] = src[i];
    }
    return new_string;
}

int my_atoi_btf(char *str){
    /*
     * Converts a string into an integer
     */
    //we must loop through the entire string
    int i;
    int total = 0;
    for(i = my_strlen(str) - 1; i >= 0; i--){
        if(isdigit(str[i])){
            total += (str[i]-'0') * pow(10, my_strlen(str) - 1 - i);
        }
    }
    return total;
}

int my_atoi_ftb(char *str){
    /*
     * Converts a string into an integer
     */
    //we must loop through the entire string
    int i;
    int total = 0;
    for(i = 0; i < my_strlen(str); i++){
        if(isdigit(str[i])){
            total += ((str[i])-'0') * pow(10, my_strlen(str) - 1 - i);
        }
    }
    return total;
}

struct node{
    int val;
    struct node *next;
};

void floyd(struct node *tort, struct node *hare, int *lam, int *mu){
    /*
     * Floyd's algorithm
     */
    struct node *head = tort;

    tort = tort->next;
    hare = (hare->next)->next;

    while(tort->val != hare->val){
        tort = tort->next;
        hare = (hare->next)->next;
    }

    *mu = 0;
    tort = head;

    while (tort->val != hare->val){
        tort = tort->next;
        hare = hare->next;
        *mu += 1;
    }

    *lam = 1;

    hare = hare->next;
    while(tort->val != hare->val){
        hare = hare->next;
        *lam += 1;
    }
}

int main() {
    char a[6] = "hello";
    char b[6] = "world";

    char *new_str = my_strcat(a, b);

    printf("Length of appended string %d\n", my_strlen(new_str));
    printf("Appended string is: %s\n", new_str);

    char c[5] = "test";
    char d[5] = "test";

    printf("ASCII test: %d\n", my_str_cmp_rec(c, d));

    char e[6] = "12345";

    int atoi_sol_ftb = my_atoi_ftb(e);
    int atoi_sol_btf = my_atoi_btf(e);

    printf("Front to back: %d\n", atoi_sol_ftb);
    printf("Back to front %d\n", atoi_sol_btf);

    return 0;
}
