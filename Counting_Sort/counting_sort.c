/* Program to perform counting sort 
 *
 * Author: Naga Kandasamy
 * Date created: February 24, 2020
 * 
 * Compile as follows: gcc -o counting_sort counting_sort.c -std=c99 -Wall -O3 -lpthread -lm
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/* Do not change the range value. */
#define MIN_VALUE 0 
#define MAX_VALUE 1023

/* Comment out if you don't need debug info */
// #define DEBUG
// #define DEBUG_MORE_VERBOSE

int compute_gold (int *, int *, int, int);
int rand_int (int, int);
void print_array (int *, int);
void print_min_and_max_in_array (int *, int);
void compute_using_pthreads (int *, int *, int, int, int);
int check_if_sorted (int *, int);
int compare_results (int *, int *, int);
void print_histogram (int *, int, int);

int 
main (int argc, char **argv)
{
    if (argc != 3) {
        printf ("Usage: %s num-elements num-threads\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    int num_elements = atoi (argv[1]);
    int num_threads = atoi (argv[2]);

    int range = MAX_VALUE - MIN_VALUE;
    int *input_array, *sorted_array_reference, *sorted_array_d;

    /* Populate the input array with random integers between [0, RANGE]. */
    printf ("Generating input array with %d elements in the range 0 to %d\n", num_elements, range);
    input_array = (int *) malloc (num_elements * sizeof (int));
    if (input_array == NULL) {
        printf ("Cannot malloc memory for the input array. \n");
        exit (EXIT_FAILURE);
    }
    srand (time (NULL));
    for (int i = 0; i < num_elements; i++)
        input_array[i] = rand_int (MIN_VALUE, MAX_VALUE);

#ifdef DEBUG
    print_array (input_array, num_elements);
    print_min_and_max_in_array (input_array, num_elements);
#endif

    /* Sort the elements in the input array using the reference implementation. 
     * The result is placed in sorted_array_reference. */
    printf ("\nSorting array using serial version\n");
    int status;
    sorted_array_reference = (int *) malloc (num_elements * sizeof (int));
    if (sorted_array_reference == NULL) {
        perror ("Malloc"); 
        exit (EXIT_FAILURE);
    }
    memset (sorted_array_reference, 0, num_elements);
    status = compute_gold (input_array, sorted_array_reference, num_elements, range);
    if (status == 0) {
        exit (EXIT_FAILURE);
    }

    status = check_if_sorted (sorted_array_reference, num_elements);
    if (status == 0) {
        printf ("Error sorting the input array using the reference code\n");
        exit (EXIT_FAILURE);
    }

    printf ("Counting sort was successful using reference version\n");

#ifdef DEBUG
    print_array (sorted_array_reference, num_elements);
#endif

    /* FIXME: Write function to sort the elements in the array in parallel fashion. 
     * The result should be placed in sorted_array_mt. */
    printf ("\nSorting array using pthreads\n");
    sorted_array_d = (int *) malloc (num_elements * sizeof (int));
    if (sorted_array_d == NULL) {
        perror ("Malloc");
        exit (EXIT_FAILURE);
    }
    memset (sorted_array_d, 0, num_elements);
    compute_using_pthreads (input_array, sorted_array_d, num_elements, range, num_threads);

    /* Check the two results for correctness. */
    printf ("\nComparing reference and pthread results\n");
    status = compare_results (sorted_array_reference, sorted_array_d, num_elements);
    if (status == 1)
        printf ("Test passed\n");
    else
        printf ("Test failed\n");

    exit (EXIT_SUCCESS);
}

/* Reference implementation of counting sort. */
int 
compute_gold (int *input_array, int *sorted_array, int num_elements, int range)
{
    /* Compute histogram. Generate bin for each element within 
     * the range. 
     * */
    int i, j;
    int num_bins = range + 1;
    int *bin = (int *) malloc (num_bins * sizeof (int));    
    if (bin == NULL) {
        perror ("Malloc");
        return 0;
    }

    memset(bin, 0, num_bins); /* Initialize histogram bins to zero */ 
    for (i = 0; i < num_elements; i++)
        bin[input_array[i]]++;

#ifdef DEBUG_MORE_VERBOSE
    print_histogram (bin, num_bins, num_elements);
#endif

    /* Generate the sorted array. */
    int idx = 0;
    for (i = 0; i < num_bins; i++) {
        for (j = 0; j < bin[i]; j++) {
            sorted_array[idx++] = i;
        }
    }

    return 1;
}

/* FIXME: Write multi-threaded implementation of counting sort. */
void 
compute_using_pthreads (int *input_array, int *sorted_array, int num_elements, int range, int num_threads)
{
    return;
}

/* Check if the array is sorted. */
int
check_if_sorted (int *array, int num_elements)
{
    int status = 1;
    for (int i = 1; i < num_elements; i++) {
        if (array[i - 1] > array[i]) {
            status = 0;
            break;
        }
    }

    return status;
}

/* Check if the arrays elements are identical. */ 
int 
compare_results (int *array_1, int *array_2, int num_elements)
{
    int status = 1;
    for (int i = 0; i < num_elements; i++) {
        if (array_1[i] != array_2[i]) {
            status = 0;
            break;
        }
    }

    return status;
}


/* Returns a random integer between [min, max]. */ 
int
rand_int (int min, int max)
{
    float r = rand ()/(float) RAND_MAX;
    return (int) floorf (min + (max - min) * r);
}

/* Helper function to print the given array. */
void
print_array (int *this_array, int num_elements)
{
    printf ("Array: ");
    for (int i = 0; i < num_elements; i++)
        printf ("%d ", this_array[i]);
    printf ("\n");
    return;
}

/* Helper function to return the min and max values in the given array. */
void 
print_min_and_max_in_array (int *this_array, int num_elements)
{
    int i;

    int current_min = INT_MAX;
    for (i = 0; i < num_elements; i++)
        if (this_array[i] < current_min)
            current_min = this_array[i];

    int current_max = INT_MIN;
    for (i = 0; i < num_elements; i++)
        if (this_array[i] > current_max)
            current_max = this_array[i];

    printf ("Minimum value in the array = %d\n", current_min);
    printf ("Maximum value in the array = %d\n", current_max);
    return;
}

/* Helper function to print the contents of the histogram. */
void 
print_histogram (int *bin, int num_bins, int num_elements)
{
    int num_histogram_entries = 0;
    int i;

    for (i = 0; i < num_bins; i++) {
        printf ("Bin %d: %d\n", i, bin[i]);
        num_histogram_entries += bin[i];
    }

    printf ("Number of elements in the input array = %d \n", num_elements);
    printf ("Number of histogram elements = %d \n", num_histogram_entries);

    return;
}


