/* FILE main.c
 *    Test the functionality of the avl_bag implementation.
 * Author: Francois Pitt, March 2012.
 */

/******************************************************************************
 *  Types and Constants.                                                      *
 ******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bag.h"

/******************************************************************************
 *  Function declarations.                                                    *
 ******************************************************************************/

/* FUNCTION bag_print -- "hidden" function in avl_bag.c for debugging. */
extern // not strictly necessary -- it's the default for function
void bag_print(const bag_t *bag, int indent, void (*print)(bag_elem_t));

/******************************************************************************
 *  Function definitions.                                                     *
 ******************************************************************************/

/* FUNCTION float_cmp
 *    Compare two (void *) values that point to floats and return -1, 0, or +1
 *    as to the first value is less than, equal to, or greater than the second.
 * Parameters and preconditions:
 *    a != NULL: pointer to the first float to compare
 *    b != NULL: pointer to the second float to compare
 * Return value:
 *    -1 if *a < *b; 1 if *a > *b; 0 if *a == *b
 * Side-effects:  none
 */
static
int float_cmp(bag_elem_t a, bag_elem_t b)
{
    return *(float *) a < *(float *) b ? -1
         : *(float *) a > *(float *) b; /* ? 1 : 0 would be redundant */
}

/* FUNCTION float_print
 *    Print a single float (passed in as a bag_elem_t) with a space in front.
 * Parameters and preconditions:
 *    e != NULL: pointer to a float
 * Return value:  none
 * Side-effects:
 *    the floating-point value of e is printed to stdout, preceded by a space
 */
static
void float_print(bag_elem_t e)
{
    printf(" %g", *(float *) e);
}

/* FUNCTION main
 *    Run some tests of the functionality of the bst_bag implementation.
 * Parameters and preconditions:  none
 * Return value:  exit status
 * Side-effects:  the main program is executed
 */
int main(void)
{
    size_t i;
    float elts[] = {3.2, 3.1, 3, 10, 11, 4, 1, 0, 0.2, 5, 0.4, 2};

    /* Create a new bag. */
    bag_t *b1 = bag_create(float_cmp);

    /* Check that we can insert values into it. */
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_insert(b1, &elts[i]));
        assert(bag_contains(b1, &elts[i]));
        assert(bag_size(b1) == i + 1);
    }

    bag_print(b1, 8, float_print);

    printf("Is this an AVL tree? %d\n", is_avl_tree(b1));

    float elts2[] = {1000.0, 1001.0};
    assert(bag_insert_norot(b1, &elts2[0]));

    bag_print(b1, 8, float_print);
    printf("Is this an AVL tree? %d\n", is_avl_tree(b1));

    assert(bag_insert_norot(b1, &elts2[1]));
    bag_print(b1, 8, float_print);
    printf("Is this an AVL tree? %d\n", is_avl_tree(b1));

//    assert(bag_insert_norot(b1, &elts2[1]));
//    bag_print(b1, 8, float_print);
//    printf("Is this an AVL tree? %d\n", is_avl_tree(b1));


//    size_t i;
//    float elts[] = {3.2, 3.1, 3, 10, 11, 4, 1, 0, 0.2, 5, 0.4, 2};
//    float bad_elts[] = {56, 0.001, 0.2000001, 75, 50, -1, 0.1};
//
//    /* Create a new bag. */
//    bag_t *b1 = bag_create(float_cmp);
//
//    /* Try to remove something from an empty bag. */
//    assert(! bag_remove(b1, &elts[0]));
//
//    /* Check that the bag is really empty. */
//    printf("Empty bag: size = %lu\nelems:", bag_size(b1));
//    bag_traverse(b1, float_print);
//    printf("\nAs a tree:\n");
//    bag_print(b1, 8, float_print);
//    printf("An empty bag %s contain %g.\n",
//           bag_contains(b1, &elts[0]) ? "does" : "does not", elts[0]);
//
//    /* Check that we can insert values into it. */
//    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
//        assert(bag_insert(b1, &elts[i]));
//        printf("After inserting %g: size = %lu\nelems:", elts[i], bag_size(b1));
//        bag_traverse(b1, float_print);
//        printf("\nAs a tree:\n");
//        bag_print(b1, 8, float_print);
//        assert(bag_contains(b1, &elts[i]));
//        assert(bag_size(b1) == i + 1);
//    }
//
//    /* See if anything got lost. */
//    printf("Lost any element?  ");
//    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
//        assert(bag_contains(b1, &elts[i]));
//    }
//    printf("No!\n");
//
//    /* See if the bag contains anything it's not supposed to. */
//    printf("Any extra elements in there?  ");
//    for (i = 0; i < sizeof(bad_elts) / sizeof(bad_elts[0]); ++i)
//    {
//        assert(! bag_contains(b1, &bad_elts[i]));
//    }
//    printf("No!\n");
//
//    /* Try to insert things twice. */
//    printf("Can we insert elements twice?  ");
//    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
//        assert(bag_insert(b1, &elts[i]));
//        assert(bag_size(b1) == i + 1 + sizeof(elts) / sizeof(elts[0]));
//    }
//    printf("Yes: size = %lu\nelems:", bag_size(b1));
//    bag_traverse(b1, float_print);
//    printf("\nAs a tree:\n");
//    bag_print(b1, 8, float_print);
//
//    /* Try to remove non-existent elements: should have no effect. */
//    printf("Can we remove non-existent elements?  ");
//    for (i = 0; i < sizeof(bad_elts) / sizeof(elts[0]); ++i) {
//        assert(! bag_remove(b1, &bad_elts[i]));
//        assert(bag_size(b1) == 2 * sizeof(elts) / sizeof(elts[0]));
//    }
//    printf("No!\n");
//
//    /* Make sure duplicate elements can be removed. */
//    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
//        assert(bag_remove(b1, &elts[i]));
//        printf("After removing %g: size = %lu\nelems:", elts[i], bag_size(b1));
//        bag_traverse(b1, float_print);
//        printf("\nAs a tree:\n");
//        bag_print(b1, 8, float_print);
//        assert(bag_contains(b1, &elts[i]));
//        assert(bag_size(b1) == 2 * sizeof(elts) / sizeof(elts[0]) - i - 1);
//    }
//
//    /* Make sure elements can be removed. */
//    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
//        assert(bag_remove(b1, &elts[i]));
//        printf("After removing %g: size = %lu\nelems:", elts[i], bag_size(b1));
//        bag_traverse(b1, float_print);
//        printf("\nAs a tree:\n");
//        bag_print(b1, 8, float_print);
//        assert(! bag_contains(b1, &elts[i]));
//        assert(bag_size(b1) == sizeof(elts) / sizeof(elts[0]) - i - 1);
//    }
//
//    /* Clean up... */
//    bag_destroy(b1);
//
//    return EXIT_SUCCESS;
}
